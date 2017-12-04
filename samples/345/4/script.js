window.onload = function() {
	var width = window.innerWidth;
	var height = window.innerHeight;
	var canvas = document.getElementById('canvas');
	var phase = 0, lastTime = null;
	var light;
	var renderer, controls, camera;
	var meshFloor;
	var dot;
	var R = 500;
	var r = 20;
	var level = 50;

	var angleX = -90;
	//var angleX = 0;
	var angleY = 0;

	var oct_h = 100;
	var h = 0.0;
	var speed = 0.05;
	
	//var help = 1/Math.sqrt(5/12)+0.001;
	var help = 1.001;
	var helpmore = true;

	var oct_angle = 0.0;
	var flag = false;

	var axis = new THREE.Vector3(0,0,1);
	var axis1 = new THREE.Vector3(0,1,0);

	var rotWorldMatrix;
	// Rotate an object around an arbitrary axis in world space       
	function rotateAroundWorldAxis(object, axis, radians) {
		rotWorldMatrix = new THREE.Matrix4();
		rotWorldMatrix.makeRotationAxis(axis.normalize(), radians);

		// old code for Three.JS pre r54:
		//  rotWorldMatrix.multiply(object.matrix);
		// new code for Three.JS r55+:
		rotWorldMatrix.multiply(object.matrix);                // pre-multiply

		object.matrix = rotWorldMatrix;

		// old code for Three.js pre r49:
		// object.rotation.getRotationFromMatrix(object.matrix, object.scale);
		// old code for Three.js pre r59:
		// object.rotation.setEulerFromRotationMatrix(object.matrix);
		// code for r59+:
		object.rotation.setFromRotationMatrix(object.matrix);
	}


	document.addEventListener("keydown", function (event) {
		switch (event.keyCode) {
			case 87:
				/*if (light.position.y < 50) {
					light.position.y += 5;
				}*/
		camera.position.z -= 5;
				break;
			case 83:
				/*if (light.position.y > -50) {
					light.position.y -= 5;
				}*/
		camera.position.z += 5;
				break;
		}
	});

	canvas.setAttribute('width', width);
	canvas.setAttribute('height', height);

	var renderer = new THREE.WebGLRenderer({canvas:canvas, antialias: true});
	renderer.setClearColor(0x000000);
	renderer.shadowMap.enabled = true;
	
	camera = new THREE.PerspectiveCamera(45,width/height,0.1,10000);
	camera.position.set(100,0,2500);

	var scene = new THREE.Scene();

	var textureLoader = new THREE.TextureLoader();
	var createTexture = new textureLoader.load("plane_texture.jpg");

    // Creating ambient light
    var ambientLight = new THREE.AmbientLight(0x404040);
    scene.add(ambientLight);

	// Creating point light
	var light = new THREE.DirectionalLight();
    //var light = new THREE.PointLight(0xffffff, 1, 3000);
	//light.add(new THREE.Mesh(new THREE.SphereGeometry(10, 16, 8), new THREE.MeshBasicMaterial({ color: 0xffffff })));
	//light.position.set(0, 1200, 0);
	//light.position.set(-R-oct_h/2+7,R+level+oct_h,0);
    light.castShadow = true;
	scene.add(light);
	
	var oct = new THREE.Mesh(
		new THREE.OctahedronGeometry(oct_h, 0),
		new THREE.MeshPhongMaterial({color: 0x00ff00, map: createTexture}));
	oct.position.set(1000, 100, 0);
	oct.castShadow = true;
	rotateAroundWorldAxis(oct, axis1, Math.PI/4);
	scene.add(oct);

	var sph = new THREE.Mesh(
		new THREE.SphereGeometry(R, 32, 32),
		new THREE.MeshPhongMaterial({color: 0x0000ff, map: createTexture}));
	sph.receiveShadow = true;
	sph.castShadow = true;
	sph.position.set(0, level, 0);
	scene.add(sph);

	var meshFloor = new THREE.Mesh(
		new THREE.PlaneGeometry(4096, 4096),
		new THREE.MeshPhongMaterial({color: 0xffffff, map: createTexture}));
	meshFloor.receiveShadow = true;
	meshFloor.rotation.x = -Math.PI / 2;
	meshFloor.position.set(0, -R, 0);
	scene.add(meshFloor);

	controls = new THREE.OrbitControls( camera, renderer.domElement );
	controls.update();

    function render() {
		renderer.render(scene, camera);
	}

	function loop() {
		if (helpmore) {		
			angleX +=0.035;
			speed = -0.1;
			oct_angle -= speed;
		} else {
			angleX -=0.035;
			speed = 0.1;
			oct_angle += speed;
		}
		/*if(angleX*57 > 45) h -= oct_h/2;
		if(angleX*57 > 90) h += oct_h/2;
		if(angleX*57 > 135) h -= oct_h/2;
		if(angleX*57 >= 180){h += oct_h/2; angleX = 0;}*/

		
		/*if(oct_angle*57 < 45 && help >= 0.01) help -= speed/45;
		if(oct_angle*57 > 45 && help <= 1) help += speed/45;
		if(oct_angle*57 >= 90 || help > 1){ oct_angle = 0; help = 0.01; }*/

		/*if(oct_angle*57 < 45 && help >= 1) help -= speed/4;
		if(oct_angle*57 > 45 && help <= 1/Math.sqrt(5/12)) help += speed/4;
		if(oct_angle*57 > 90) oct_angle = 0;*/

		if(help >1 && help < 1/Math.sqrt(5/12) && !flag){help -= Math.sqrt(5/12)*speed; rotateAroundWorldAxis(oct, axis, speed*2);}
		else if(help > 1/Math.sqrt(5/12) && !flag){help += Math.sqrt(5/12)*speed;flag = true;}		//help = 1/Math.sqrt(5/12)*speed/100-0.001;
		else if(help > 1 && help < 1/Math.sqrt(5/12) && flag){help += Math.sqrt(5/12)*speed/100; rotateAroundWorldAxis(oct, axis, speed*2);}
		else if(help < 1 && flag) {flag = false; help -= Math.sqrt(5/12)*speed;}						//help = 1.001;

		//if(help >= 1 && !flag) {help = 1;}
		//if(help <= 1/Math.sqrt(5/12) && flag) help += speed;
		//if(help < 1 && !flag) {flag = true; help += speed/6; }
		//if(help > 1/Math.sqrt(5/12) && flag){ flag = false; help-=speed/6;}

		//dot.position.set(0 + Math.sin(angleX)*R, level + Math.cos(angleX)*R, 0);

		/*meshFloor.position.set(0 + Math.sin(angleX)*R, level + Math.cos(angleX)*R, 0);
		meshFloor.rotateY(-0.01);*/

		//oct.position.set(0 + Math.sin(angleX)*(R+oct_h*(Math.sqrt(5/12)*help)), level + Math.cos(angleX)*(R+oct_h*(Math.sqrt(5/12)*help)), 0);
		//oct.rotateZ(speed/3);
		//oct.rotateOnAxis(axis,speed/3);

			//oct.position.set(0 + Math.sin(angleX)*(R+oct_h*(Math.sqrt(5/12)*help)), level + Math.cos(angleX)*(R+oct_h*(Math.sqrt(5/12)*help)), 0);
		
		oct.position.set(0 + Math.sin(angleX)*(R+(oct_h-oct_h/4)*(Math.sqrt(5/12)*help)), level + Math.cos(angleX)*(R+(oct_h-oct_h/4)*(Math.sqrt(5/12)*help)), 0);
		rotateAroundWorldAxis(oct, axis, speed/2);
		
		if(oct.position.y < -R+level+oct_h){ helpmore = !helpmore;}
		
		//renderer.render(scene, camera);
		render();
		requestAnimationFrame(function(){loop();});
	}

	loop();
}


