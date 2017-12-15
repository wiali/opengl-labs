window.onload = function() {
  var width = window.innerWidth;
  var height = window.innerHeight;
  var canvas = document.getElementById('canvas');

  canvas.setAttribute('width', width);
  canvas.setAttribute('height', height);

  var ball = {
    rotationX: 0,
    rotationY: 0,
    rotationZ: 0,
    positionX: 0,
    positionY: 0,
    positionZ: 0,
  };
  //
  // var gui = new dat.GUI();
  // gui.add(light, 'intensity').min(1).max(10).lister;
  var gui = new dat.GUI();
  gui.add(ball, 'positionX').min(-5).max(5).step(0.1);
  gui.add(ball, 'positionY').min(-5).max(5).step(0.1);
  gui.add(ball, 'positionZ').min(-5).max(5).step(0.1);
  gui.add(ball, 'rotationX').min(-0.2).max(0.2).step(0.001);
  gui.add(ball, 'rotationY').min(-0.2).max(0.2).step(0.001);
  gui.add(ball, 'rotationZ').min(-0.2).max(0.2).step(0.001);


  var renderer = new THREE.WebGLRenderer({canvas: canvas});
  renderer.setClearColor(0x000000);

  var scene = new THREE.Scene();

  var camera = new THREE.PerspectiveCamera(45, width / height, 0.1, 5000);
  camera.position.set(0, 0, 1000);

  // var light = new THREE.AmbientLight(0xffffff);
  // scene.add(light);

  var geometry = new THREE.SphereGeometry(100, 12, 12);
  // var material = new THREE.MeshBasicMaterial({color: 0x00ff00, wireframe: true});
  var material = new THREE.MeshBasicMaterial({color: 0xffffff, vertexColors: THREE.FaceColors});
  // var material = new THREE.MeshNormalMaterial({color: 0xffffff, vertexColors: THREE.FaceColors});
  var mesh = new THREE.Mesh(geometry, material);
  scene.add(mesh);

  for (var i = 0; i < geometry.faces.length; i++) {
    geometry.faces[i].color.setRGB(Math.random(), Math.random(), Math.random());
  }


  //browser ready loop
  function loop() {
    // mesh.position.x += Math.PI / 1000;
    mesh.position.x += ball.positionX;
    mesh.position.y += ball.positionY;
    mesh.position.z += ball.positionZ;
    mesh.rotation.x += ball.rotationX;
    mesh.rotation.y += ball.rotationY;
    mesh.rotation.z += ball.rotationZ;
    // scene.rotation.y += ball.rotationY;

    renderer.render(scene, camera);
    requestAnimationFrame(function(){loop();});
  }

  loop();
}

// function f1() {
//   var width = window.innerWidth;
//   var height = window.innerHeight;
//   var canvas = document.getElementById('canvas');
//
//   canvas.setAttribute('width', width);
//   canvas.setAttribute('height', height);
//
//   var renderer = new THREE.WebGLRenderer({canvas: canvas});
//   renderer.setClearColor(0x000000);
//
//   var scene = new THREE.Scene();
//
//   var camera = new THREE.PerspectiveCamera(45, width / height, 0.1, 5000);
//   camera.position.set(0, 0, 1000);
//
//   // var light = new THREE.AmbientLight(0xffffff);
//   // scene.add(light);
//
//   var geometry = new THREE.SphereGeometry(100, 12, 12);
//   var material = new THREE.MeshBasicMaterial({color: 0x00ff00, wireframe: true});
//   var mesh = new THREE.Mesh(geometry, material);
//   scene.add(mesh);
//
//   renderer.render(scene, camera);
// }
