/************************************************************
 * Author: Weichen Xu
 * Date: 12/08/2015
 * 1. shadow, using shadow matrix
 * 2. turn on/off depth test when drawing shadow
 * 3. ambient light and directional light
 * 4. shading with point/spot light
/**************************************************************/
#include "Angel-yjc.h"
#include "sphere.h"
#include "floor.h"
#include "light.h"
#include <iostream>
#include <fstream>
#include <string>
typedef Angel::vec3  color3;
typedef Angel::vec3  point3;
typedef Angel::vec4  point4;
WCX_sphere sphere;
WCX_floor myFloor;
GLuint Angel::InitShader(const char* vShaderFile, const char* fShaderFile);

GLuint programs[2];       /* shader program object id */
GLuint myFloor_buffer;  /* vertex buffer object id for myFloor */
GLuint sphere_buffer;	/*vertex buffer object id for sphere */

// Projection transformation parameters
GLfloat  fovy = 55.0;  // Field-of-view in Y direction angle (in degrees)
GLfloat  aspect;       // Viewport aspect ratio
GLfloat  zNear = 0.5, zFar = 50.0;
GLfloat  sphereScale = 1.0;

// Attributes
GLint frame = 0;
GLint max_frames;
GLint rollingSeg = 0;
vec4 init_eye(7.0, 3.0, -10.0, 1.0); // initial viewer position
vec4 eye = init_eye;               // current viewer position
color4 sphere_color(1.0, 0.84, 0.0, 1.0);

// Control flag
int beginRolling = 0; // 1: started, 0: not started
int animationFlag = 1; // 1: animation; 0: non-animation. Toggled by key 'a' or 'A'

// Rolling segs
point4 rollingSegs[3] = {
	point4(-4,1,4,1.0),
	point4(-1,1,-4,1.0),
	point4(3,1,5,1.0)
};

// Shadow
mat4 shadowMatrix;
point4 shadowLight = point4(-14.0, 12.0, -3.0, 1.0);
color4 shadow_color(0.25, 0.25, 0.25, 0.65);
vec4 plane = vec4(0.0, 1.0, 0.0, 0.0);
void getShadowMatrix(mat4 &shadowM, point4 lightSource, vec4 plane);

// Light

WCX_light myLight;
void initLightSource();

//----------------------------------------------------------------------------
// sphere initialization
void initSphere(){
	// init & set sphere
	sphere.loadSphereFromFile();
	sphere.setFlatNormals();
	sphere.fill_flag = false;
	sphere.lighting_flag = false;
	sphere.shadow = true;
	sphere.setColor(sphere_color);
	sphere.setShadowColor(shadow_color);
	sphere.setMaterial();
	sphere.setRadius(sphereScale);
}
//----------------------------------------------------------------------------
// floor initialization
void initFloor(){
	// init & set myFloor
	myFloor.setFloor(vec4(5.0,0.0,8.0,1.0),vec4(-5.0,0.0,-4.0, 1.0));
	myFloor.fill_flag = true;
	myFloor.lighting_flag = false;
	color4 myFloor_color(0.0,1.0,0.0, 1.0);
	myFloor.setColor(myFloor_color);
	myFloor.setMaterial();
	myFloor.generateAxis();
}
//----------------------------------------------------------------------------
// OpenGL initialization
void init()
{
	
    initSphere();
	// Create and initialize a vertex buffer object for sphere, to be used in display()
	glGenBuffers(1, &sphere.sphere_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, sphere.sphere_buffer);
#if 1
	glBufferData(GL_ARRAY_BUFFER, sizeof(point4) * sphere.vertex_size + sizeof(color4) * sphere.vertex_size + sizeof(point3) * sphere.vertex_size,
		 NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point4) * sphere.vertex_size, sphere.sphere_points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * sphere.vertex_size, sizeof(color4) * sphere.vertex_size,
		sphere.sphere_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * sphere.vertex_size + sizeof(color4) * sphere.vertex_size, sizeof(point3) * sphere.vertex_size,
		sphere.sphere_normals);
#endif

	// Create and initialize a vertex buffer object for sphere shadow
	glGenBuffers(1, &sphere.shadow_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, sphere.shadow_buffer);
#if 1
	glBufferData(GL_ARRAY_BUFFER, sizeof(point4) * sphere.vertex_size + sizeof(color4) * sphere.vertex_size,
		 NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point4) * sphere.vertex_size, sphere.sphere_points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * sphere.vertex_size, sizeof(color4) * sphere.vertex_size,
		sphere.shadow_colors);
#endif
	initFloor();
 // Create and initialize a vertex buffer for myFloor
	glGenBuffers(1, &myFloor.floor_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, myFloor.floor_buffer);
#if 1
	glBufferData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.vertex_size + sizeof(color4) * myFloor.vertex_size + sizeof(point3) * myFloor.vertex_size,
		 NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point4) * myFloor.vertex_size, myFloor.floor_points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.vertex_size, sizeof(color4) * myFloor.vertex_size,
		myFloor.floor_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.vertex_size + sizeof(color4) * myFloor.vertex_size, sizeof(point3) * myFloor.vertex_size,
		myFloor.floor_normals);
#endif
	// Create and initialize a vertex buffer object for axis
	glGenBuffers(1, &myFloor.axis_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, myFloor.axis_buffer);
#if 1
	glBufferData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.axis_vertex_size + sizeof(color4) * myFloor.axis_vertex_size,
		 NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point4) * myFloor.axis_vertex_size, myFloor.axis_points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.axis_vertex_size, sizeof(color4) * myFloor.axis_vertex_size,
		myFloor.axis_colors);
#endif

	// init & set up light source
	initLightSource();
 // Load shaders and create a shader program (to be used in display())
    programs[0] = InitShader("vshader42.glsl", "fshader42.glsl");
    programs[1] = InitShader("vshader43.glsl", "fshader42.glsl");
    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); 
    // initialize shadow matrix
	getShadowMatrix(shadowMatrix, shadowLight, plane);
}
//----------------------------------------------------------------------------
// initialize light souce
void initLightSource(){
	myLight.global_ambient = color4(1.0, 1.0, 1.0, 1.0);
	myLight.light_ambient = color4(0.0, 0.0, 0.0, 1.0);
	myLight.light_diffuse = color4(0.8, 0.8, 0.8, 1.0);
	myLight.light_specular = color4(0.2, 0.2, 0.2, 1.0);
	myLight.light_direction = point4(0.1, 0.0, -1.0, 0.0);
	myLight.getProduct(sphere.lp);
	myLight.getProduct(myFloor.lp);
	myLight.light_ambient2 = color4(0.0, 0.0, 0.0, 1.0);
	myLight.light_diffuse2 = color4(1.0, 1.0, 1.0, 1.0);
	myLight.light_specular2 = color4(1.0, 1.0, 1.0, 1.0);
	myLight.light_position2 = point4(-14, 12, -3, 1);
	myLight.const_att2 = 2.0;
	myLight.linear_att2 = 0.01;
	myLight.quad_att2 = 0.001;
	myLight.light_direction2 = point4(8, -12, -1.5, 0.0);
	myLight.light_exp2 = 15.0;
	myLight.light_range2 = (20.0)/180*PI;
	myLight.getProduct2(sphere.lp);
	myLight.getProduct2(myFloor.lp);
	myLight.smooth = 0;
	myLight.point = 1;
}
//----------------------------------------------------------------------
// SetUp_Lighting_Uniform_Vars(mat4 mv):
// Set up lighting parameters that are uniform variables in shader.
//
// Note: "LightPosition" in shader must be in the Eye Frame.
//       So we use parameter "mv", the model-view matrix, to transform
//       light_position to the Eye Frame.
//----------------------------------------------------------------------
void SetUp_Lighting_Uniform_Vars(mat4 mv, GLuint program, WCX_light_products &lp)
{
	
    glUniform4fv( glGetUniformLocation(program, "AmbientProduct"),
		  1, lp.ambient_product );
    glUniform4fv( glGetUniformLocation(program, "DiffuseProduct"),
		  1, lp.diffuse_product );
    glUniform4fv( glGetUniformLocation(program, "SpecularProduct"),
		  1, lp.specular_product );
	glUniform4fv( glGetUniformLocation(program, "distant_light_dir"),
		1, myLight.light_direction );
	glUniform4fv( glGetUniformLocation(program, "pointAmbientProduct"),
		  1, lp.ambient_product2 );
    glUniform4fv( glGetUniformLocation(program, "pointDiffuseProduct"),
		  1, lp.diffuse_product2 );
    glUniform4fv( glGetUniformLocation(program, "pointSpecularProduct"),
		  1, lp.specular_product2 );
	mat3 normal_matrix = NormalMatrix(mv, 1);
	mat4 nm = mat4WithUpperLeftMat3(normal_matrix);
	glUniform4fv( glGetUniformLocation(program, "pointLightDir"),
		1, nm*myLight.light_direction2);

	point4 light_position_eye_frame = mv * myLight.light_position2;
	glUniform4fv( glGetUniformLocation(program, "pointLightPosition"),
		1, light_position_eye_frame);
	glUniform1i( glGetUniformLocation(program, "smooth_shading"), myLight.smooth);
	glUniform1i( glGetUniformLocation(program, "point_light"), myLight.point);

    glUniform1f(glGetUniformLocation(program, "Shininess"),
		        lp.material_shininess );
	glUniform1f(glGetUniformLocation(program, "pointLightAng"),
		myLight.light_range2 );
	glUniform1f(glGetUniformLocation(program, "pointLightExp"),
		myLight.light_exp2);
	glUniform1f(glGetUniformLocation(program, "ConstAtt"),
		myLight.const_att2 );
	glUniform1f(glGetUniformLocation(program, "LinearAtt"),
		myLight.linear_att2 );
	glUniform1f(glGetUniformLocation(program, "QuadAtt"),
		myLight.quad_att2 );
}
//----------------------------------------------------------------------------
// Rolling sphere
void rolling(){
	// start rolling
	if(rollingSeg == 0){
		max_frames = sphere.rollingFromAToB(rollingSegs[0],rollingSegs[1],mat4());
		rollingSeg = 1;
		return;
	}
	// iteration between A-B, B-C, C-A
	// Count the frame, when it arrives endpoint
	// Start new rolling seg, and store last rolling rotation matrix
	if(frame <= max_frames)	return;
	else{
		max_frames = sphere.rollingFromAToB(rollingSegs[rollingSeg%3],rollingSegs[(rollingSeg+1)%3], sphere.rollingFrameRotate(max_frames));
		rollingSeg = rollingSeg%3+1;
		frame = 0;
	}
	
}

//----------------------------------------------------------------------------
// drawObj(buffer, num_vertices):
// modify drawMode to draw lines in shader
// for X,Y,Z axises
void drawObj(GLuint buffer, int num_vertices, GLuint drawMode, GLuint program)
{
    //--- Activate the vertex buffer object to be drawn ---//
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
	GLuint vPosition, vColor, vNormal;
    /*----- Set up vertex attribute arrays for each vertex attribute -----*/
    vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
			  BUFFER_OFFSET(0) );
	if(program == programs[0]){
		vColor = glGetAttribLocation(program, "vColor"); 
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * sphere.vertex_size, sizeof(color4) * sphere.vertex_size,
		//sphere.sphere_colors);
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(sizeof(point4) * num_vertices) ); 
	}
	else if(program == programs[1]){
		vNormal = glGetAttribLocation(program, "vNormal"); 
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * sphere.vertex_size, sizeof(color4) * sphere.vertex_size,
		//sphere.sphere_colors);
		glEnableVertexAttribArray(vNormal);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(sizeof(point4) * num_vertices + sizeof(point4) * num_vertices) ); 
	}
      // the offset is the (total) size of the previous vertex attribute array(s)

    /* Draw a sequence of geometric objs (triangles) from the vertex buffer
       (using the attributes specified in each enabled vertex attribute array) */
	glDrawArrays(drawMode, 0, num_vertices);

    /*--- Disable each vertex attribute array being enabled ---*/
    glDisableVertexAttribArray(vPosition);
    if(program == programs[0])	glDisableVertexAttribArray(vColor);
	else if(program == programs[1])	glDisableVertexAttribArray(vNormal);
}
//----------------------------------------------------------------------------
// draw sphere
void drawSphere(mat4 mv, mat4 p){
	GLuint  model_view;  // model-view matrix uniform shader variable location
	GLuint  projection;  // projection matrix uniform shader variable location
	GLuint  program;
	if(sphere.lighting_flag)	program = programs[1];
	else	program = programs[0];
	glUseProgram(program); // Use the shader program
	model_view = glGetUniformLocation(program, "model_view" );
    projection = glGetUniformLocation(program, "projection" );
	glUniformMatrix4fv(projection, 1, GL_TRUE, p); // GL_TRUE: matrix is row-major
	if(sphere.lighting_flag)	SetUp_Lighting_Uniform_Vars(mv, program, sphere.lp);
	if(beginRolling)	mv =  mv * sphere.rollingFramePosition(frame)*sphere.rollingFrameRotate(frame);
	else
	{
		mv = mv * Translate(-4.0, 1.0, 4.0);
	}
    glUniformMatrix4fv(model_view, 1, GL_TRUE, mv); // GL_TRUE: matrix is row-major
	mat3 normal_matrix = NormalMatrix(mv, 1);
    glUniformMatrix3fv(glGetUniformLocation(program, "Normal_Matrix"), 
		       1, GL_TRUE, normal_matrix );
	if (sphere.fill_flag == 1) // Filled cube
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else              // Wireframe cube
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0);
	drawObj(sphere.sphere_buffer, sphere.vertex_size,GL_TRIANGLES, program);  // draw the sphere
}
//----------------------------------------------------------------------------
// draw floor
void drawFloor(mat4 mv, mat4 p){
	GLuint  model_view;  // model-view matrix uniform shader variable location
	GLuint  projection;  // projection matrix uniform shader variable location
	GLuint  program;
	if(myFloor.lighting_flag)	program = programs[1];
	else	program = programs[0];
	glUseProgram(program); // Use the shader program
	model_view = glGetUniformLocation(program, "model_view" );
    projection = glGetUniformLocation(program, "projection" );
	glUniformMatrix4fv(projection, 1, GL_TRUE, p); // GL_TRUE: matrix is row-major
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv); // GL_TRUE: matrix is row-major
	if(sphere.lighting_flag)	SetUp_Lighting_Uniform_Vars(mv, program, myFloor.lp);
	glUniform1i( glGetUniformLocation(program, "smooth_shading"), 0);
	mat3 normal_matrix = NormalMatrix(mv, 1);
    glUniformMatrix3fv(glGetUniformLocation(program, "Normal_Matrix"), 
		       1, GL_TRUE, normal_matrix );
	if (myFloor.fill_flag == 1) // Filled floor
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else              // Wireframe floor
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawObj(myFloor.floor_buffer, myFloor.vertex_size,GL_TRIANGLES, program);  // draw the cube
}
//----------------------------------------------------------------------------
void display( void )
{
  GLuint  model_view;  // model-view matrix uniform shader variable location
  GLuint  projection;  // projection matrix uniform shader variable location
  GLuint  program;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor(0.529,0.807,0.92,1.0);
	

    /*---  Set up and pass on Projection matrix to the shader ---*/
    mat4  p = Perspective(fovy, aspect, zNear, zFar);
    
    /*---  Set up and pass on Model-View matrix to the shader ---*/
    // eye is a global variable of vec4 set to init_eye and updated by keyboard()
    vec4    at(-7.0, -3.0, 10.0, 1.0);
	at = normalize(at);
    vec4    up(0.0, 1.0, 0.0, 0.0);
    mat4  mv = LookAt(eye, at, up);
	// whether rolling begin
	// Draw sphere
	drawSphere(mv, p);

	// Draw myFloor first time: only to z-buffer
	mv = LookAt(eye, at, up);
	glDepthMask(GL_FALSE);
	drawFloor(mv, p);  // draw the cube
	//glLineWidth(2.0);

	// Draw shadow by draw sphere*shadow_projection again
	// z-buffer & color buffer
	// No shadow when eye is below the plane
	
	if(sphere.shadow && eye[1] > 0){
		program = programs[0];
		glUseProgram(program); // Use the shader program
		model_view = glGetUniformLocation(program, "model_view" );
		projection = glGetUniformLocation(program, "projection" );
		glUniformMatrix4fv(projection, 1, GL_TRUE, p); // GL_TRUE: matrix is row-major
		mv = LookAt(eye, at, up);
		if(beginRolling)	mv =  mv * shadowMatrix * sphere.rollingFramePosition(frame)*sphere.rollingFrameRotate(frame);
		else
		{
			mv = mv * shadowMatrix * Translate(-4.0, 1.0, 4.0);
		}
		glUniformMatrix4fv(model_view, 1, GL_TRUE, mv); // GL_TRUE: matrix is row-major
		if (sphere.fill_flag == 1) // Filled cube
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else              // Wireframe cube
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(1.0);
		glDepthMask(GL_TRUE);
		drawObj(sphere.shadow_buffer, sphere.vertex_size,GL_TRIANGLES, program);  // draw the sphere shadow
	}

	// Draw myFloor: only to color buffer
	// Restore default when finished
	mv = LookAt(eye, at, up);
	glDepthMask(GL_TRUE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	drawFloor(mv, p);  // draw the cube
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	

	// Draw axises
	program = programs[0];
    glUseProgram(program); // Use the shader program
    model_view = glGetUniformLocation(program, "model_view" );
    projection = glGetUniformLocation(program, "projection" );
	glUniformMatrix4fv(projection, 1, GL_TRUE, p); // GL_TRUE: matrix is row-major
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv); // GL_TRUE: matrix is row-major
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0);
	drawObj(myFloor.axis_buffer, myFloor.axis_vertex_size,GL_LINES, program);  // draw the cube
	
    glutSwapBuffers();
}

//---------------------------------------------------------------------------
//generate shadow matrix
void getShadowMatrix(mat4 &shadowMatrix, point4 lightSource, vec4 plane){
	float d = dot(lightSource,plane);
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(i == j)	shadowMatrix[i][j] = d - lightSource[i]*plane[j];
			else shadowMatrix[i][j] = 0.0 - lightSource[i]*plane[j];
		}
	}
	return;
}
//---------------------------------------------------------------------------
void idle (void)
{
	if(beginRolling)	{
	  rolling();
	  frame ++;
  }
  // angle += 1.0;    //YJC: change this value to adjust the cube rotation speed.
  glutPostRedisplay();
}
//----------------------------------------------------------------------------
void myMouseFunc(int button, int state, int x, int y){
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		if(beginRolling){
			animationFlag = 1 -  animationFlag;
            if (animationFlag == 1) glutIdleFunc(idle);
            else                    glutIdleFunc(NULL);
		}	
	}
}
//----------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
	case 033: // Escape Key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
	case 'B':
	case 'b':
		beginRolling = 1;
		break;
    case 'X': eye[0] += 1.0; break;
	case 'x': eye[0] -= 1.0; break;
    case 'Y': eye[1] += 1.0; break;
	case 'y': eye[1] -= 1.0; break;
    case 'Z': eye[2] += 1.0; break;
	case 'z': eye[2] -= 1.0; break;
    }
	
    glutPostRedisplay();
}
//----------------------------------------------------------------------------
void myMenu(int id){
	switch(id){
	case 1:
		eye = init_eye; 
		animationFlag = 1;
		glutIdleFunc(idle);
		break;
	case 2:
		exit( EXIT_SUCCESS );
		break;
	case 3:
		break;
	}
	
	glutPostRedisplay();
}
//
void shadowMenu(int id){
	switch(id){
	case 1:
		sphere.shadow =false;
		sphere.lighting_flag = false;
		myFloor.lighting_flag = false;
		break;
	case 2:
		sphere.shadow = true;
		break;
	}
}
//
void lightMenu(int id){
	sphere.fill_flag = true;
	switch(id){
	case 1:
		sphere.lighting_flag = false;
		myFloor.lighting_flag = false;
		break;
	case 2:
		sphere.lighting_flag = true;
		myFloor.lighting_flag = true;
		break;
	}
}
//
void wfMenu(int id){
	switch(id){
	case 1:
		sphere.fill_flag = true;
		break;
	case 2:
		sphere.fill_flag = false;
		break;
	}
}
//
void shadingMenu(int id){
	sphere.fill_flag = true;
	switch(id){
	case 1:
		myLight.smooth = 0;
		break;
	case 2:
		myLight.smooth = 1;
		break;
	}
}
//
void lightSourceMenu(int id){
	switch(id){
	case 1:
		myLight.point = 0;
		break;
	case 2:
		myLight.point = 1;
		break;
	}
}
//----------------------------------------------------------------------------
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    aspect = (GLfloat) width  / (GLfloat) height;
    glutPostRedisplay();
}
//----------------------------------------------------------------------------
// create menu & mouse & keyboard
void addControl(){
	// Add Keyboard & Mouse & Menu
    glutKeyboardFunc(keyboard);
	glutMouseFunc(myMouseFunc);
	GLuint subShadowMenu = glutCreateMenu(shadowMenu);
	glutAddMenuEntry("No",1);
	glutAddMenuEntry("Yes",2);
	GLuint subLightMenu = glutCreateMenu(lightMenu);
	glutAddMenuEntry("No",1);
	glutAddMenuEntry("Yes",2);
	GLuint subWFMenu = glutCreateMenu(wfMenu);
	glutAddMenuEntry("No",1);
	glutAddMenuEntry("Yes",2);
	GLuint subShadingMenu = glutCreateMenu(shadingMenu);
	glutAddMenuEntry("Flat shading",1);
	glutAddMenuEntry("Smooth shading",2);
	GLuint subLSMenu = glutCreateMenu(lightSourceMenu);
	glutAddMenuEntry("Spot Light",1);
	glutAddMenuEntry("Point Source",2);
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Default View Port",1);
	glutAddMenuEntry("Quit",2);
	glutAddSubMenu("Shadow", subShadowMenu);
	glutAddSubMenu("Enable Lighting", subLightMenu);
	glutAddSubMenu("Wire Frame Sphere", subWFMenu);
	glutAddSubMenu("Shading", subShadingMenu);
	glutAddSubMenu("Light Source", subLSMenu);
	//glutAddSubMenu("Shadow", );
	glutAttachMenu(GLUT_LEFT_BUTTON);
}
//----------------------------------------------------------------------------
int main(int argc, char **argv)
{ int err;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    // glutInitContextVersion(3, 2);
    // glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Sphere Rotation");

  /* Call glewInit() and error checking */
  err = glewInit();
  if (GLEW_OK != err)
  { printf("Error: glewInit failed: %s\n", (char*) glewGetErrorString(err)); 
    exit(1);
  }
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
	addControl();
    init();
    glutMainLoop();
    return 0;
}
