window.onload = function() {
  var width = window.innerWidth;
  var height = window.innerHeight;
  var canvas = document.getElementById('canvas');

  canvas.setAttribute('width', width);
  canvas.setAttribute('height', height);

  var renderer = new THREE.WebGLRenderer({canvas: canvas});
  renderer.setClearColor(0x000000);

  var scene = new THREE.Scene();

  var camera = new THREE.PerspectiveCamera(45, width / height, 0.1, 5000);
  camera.position.set(0, 0, 1000);

  // var light = new THREE.AmbientLight(0xffffff);
  // scene.add(light);

  var geometry = new THREE.SphereGeometry(100, 12, 12);
  var material = new THREE.MeshBasicMaterial({color: 0x00ff00, wireframe: true});
  var mesh = new THREE.Mesh(geometry, material);
  scene.add(mesh);

  //browser ready loop
  function loop() {
    // mesh.position.x += 1;
    // mesh.rotation.z += Math.PI / 1000;

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
