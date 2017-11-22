/************************************************************
 * Author: Weichen Xu
 * Date: 12/16/2015
 * 1. fog, 3 types
 * 2. blending shadow
 * 3. texture mapping: 
		Ground texture tiling
		sphere texture 1D/2D slanted/vertical obj/eye frame
 * 4. lattice
 * 
/**************************************************************/
#include "Angel-yjc.h"
#include "sphere.h"
#include "floor.h"
#include "light.h"
#include "firework.h"
#include <iostream>
#include <fstream>
#include <string>
typedef Angel::vec3  color3;
typedef Angel::vec3  point3;
typedef Angel::vec4  point4;
WCX_sphere sphere;
WCX_floor myFloor;
GLuint Angel::InitShader(const char* vShaderFile, const char* fShaderFile);

GLuint programs[3];       /* shader program object id */
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
bool blending_shadow = false;

// Light
WCX_light myLight;
void initLightSource();

// fog
// 0: no fog; 1: linear; 2: expotional; 3: exp square
// init with no fog: 0
GLuint fog_mode = 0;

// firework
WCX_firework firework;

/* global definitions for constants and global image arrays */
static GLuint tex[2];
#define ImageWidth  32
#define ImageHeight 32
GLubyte Image[ImageHeight][ImageWidth][4];

#define	stripeImageWidth 32
GLubyte stripeImage[4*stripeImageWidth];
//----------------------------------------------------------------------------
void image_set_up(void)
{
 int i, j, c; 
 
 /* --- Generate checkerboard image to the image array ---*/
  for (i = 0; i < ImageHeight; i++)
    for (j = 0; j < ImageWidth; j++)
      {
       c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0));

       if (c == 1) /* white */
	{
         c = 255;  
	 Image[i][j][0] = (GLubyte) c;
         Image[i][j][1] = (GLubyte) c;
         Image[i][j][2] = (GLubyte) c;
	}
       else  /* green */
	{
         Image[i][j][0] = (GLubyte) 0;
         Image[i][j][1] = (GLubyte) 150;
         Image[i][j][2] = (GLubyte) 0;
	}

       Image[i][j][3] = (GLubyte) 255;
      }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

/*--- Generate 1D stripe image to array stripeImage[] ---*/
  for (j = 0; j < stripeImageWidth; j++) {
     /* When j <= 4, the color is (255, 0, 0),   i.e., red stripe/line.
        When j > 4,  the color is (255, 255, 0), i.e., yellow remaining texture
      */
    stripeImage[4*j] = (GLubyte)    255;
    stripeImage[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
    stripeImage[4*j+2] = (GLubyte) 0; 
    stripeImage[4*j+3] = (GLubyte) 255;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
/*----------- End 1D stripe image ----------------*/

/*--- texture mapping set-up is to be done in 
      init() (set up texture objects),
      display() (activate the texture object to be used, etc.)
      and in shaders.
 ---*/

} /* end function */
//----------------------------------------------------------------------------
// sphere initialization
void initSphere(){
	// init & set sphere
	sphere.loadSphereFromFile();
	sphere.setFlatNormals();
	sphere.fill_flag = true;
	sphere.lighting_flag = true;
	sphere.shadow = true;
	sphere.textureFlag = true;
	sphere.lattice_flag = false;
	sphere.lattice_mode = _UPRIGHT_LATTICE;
	sphere.textureCoordDir = _VER_TEX_COORD;
	sphere.textureCoordFrame = _TEX_IN_WORLD;
	sphere.texture2D = 0;
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
	myFloor.lighting_flag = true;
	myFloor.texture_mapped_ground = 1;
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
	image_set_up();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	/*--- Create and Initialize a texture object ---*/
	glGenTextures(1, &tex[0]);      // Generate texture obj name(s)

	glActiveTexture( GL_TEXTURE0 );  // Set the active texture unit to be 0 
	glBindTexture(GL_TEXTURE_2D, tex[0]); // Bind the texture to this texture unit

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImageWidth, ImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, Image);
	/*--- Create and Initialize a texture for strip ---*/
	glGenTextures(1, &tex[1]);      // Generate texture obj name(s)

	glActiveTexture( GL_TEXTURE1 );  // Set the active texture unit to be 1 
	glBindTexture(GL_TEXTURE_1D, tex[1]); // Bind the texture to this texture unit

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth,
                0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.vertex_size + sizeof(color4) * myFloor.vertex_size + sizeof(point3) * myFloor.vertex_size +sizeof(vec2) * myFloor.vertex_size,
		 NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point4) * myFloor.vertex_size, myFloor.floor_points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.vertex_size, sizeof(color4) * myFloor.vertex_size,
		myFloor.floor_colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.vertex_size + sizeof(color4) * myFloor.vertex_size, sizeof(point3) * myFloor.vertex_size,
		myFloor.floor_normals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point4) * myFloor.vertex_size + sizeof(color4) * myFloor.vertex_size + sizeof(point3) * myFloor.vertex_size, sizeof(vec2) * myFloor.vertex_size,
		myFloor.floor_texture_cord);
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

	// Create and initialize a vertex buffer for firework
	firework.setFirework();
	glGenBuffers(1, &firework.firework_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, firework.firework_buffer);
#if 1
	glBufferData(GL_ARRAY_BUFFER, sizeof(point3) * firework.vertex_size + sizeof(color3) * firework.vertex_size,
		 NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point3) * firework.vertex_size, firework.particle_velocity);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point3) * firework.vertex_size, sizeof(color3) * firework.vertex_size, firework.particle_color);
#endif

	// init & set up light source
	initLightSource();
 // Load shaders and create a shader program (to be used in display())
    programs[0] = InitShader("vshader42.glsl", "fshader42.glsl");
    programs[1] = InitShader("vshader43.glsl", "fshader42.glsl");
	programs[2] = InitShader("vshader_firework.glsl", "fshader_firework.glsl");
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
void drawObj(GLuint buffer, int num_vertices, GLuint drawMode, GLuint program, bool texCoord)
{
    //--- Activate the vertex buffer object to be drawn ---//
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
	GLuint vPosition, vColor, vNormal, vTexCoord;
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
	// whether texture coord should be buffered
	if	(texCoord){
		vTexCoord = glGetAttribLocation(program, "vTexCoord");
		glEnableVertexAttribArray(vTexCoord);
		glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
				BUFFER_OFFSET(sizeof(point4) * num_vertices + sizeof(point4) * num_vertices + sizeof(color3) * num_vertices) ); 
	}
      // the offset is the (total) size of the previous vertex attribute array(s)

    /* Draw a sequence of geometric objs (triangles) from the vertex buffer
       (using the attributes specified in each enabled vertex attribute array) */
	glDrawArrays(drawMode, 0, num_vertices);

    /*--- Disable each vertex attribute array being enabled ---*/
    glDisableVertexAttribArray(vPosition);
	if	(texCoord)	glDisableVertexAttribArray(vTexCoord);
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
	// fog mode
	glUniform1i( glGetUniformLocation(program, "fog_mode"), fog_mode);
	glUniform1i( glGetUniformLocation(program, "texture_2D"), 0);
	glUniform1i( glGetUniformLocation(program, "texture_1D"), 1);
	glUniform1i( glGetUniformLocation(program, "Texture_app_flag"), sphere.getTextureAppFlag());
	if(sphere.lattice_flag)	glUniform1i( glGetUniformLocation(program, "lattice_flag"), sphere.lattice_mode);
	else glUniform1i( glGetUniformLocation(program, "lattice_flag"), 0);
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
	drawObj(sphere.sphere_buffer, sphere.vertex_size,GL_TRIANGLES, program, false);  // draw the sphere
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
	// texture
	glUniform1i( glGetUniformLocation(program, "texture_2D"), 0);
	glUniform1i( glGetUniformLocation(program, "lattice_flag"), 0);
	glUniform1i( glGetUniformLocation(program, "Texture_app_flag"), myFloor.texture_mapped_ground);
	// fog mode
	glUniform1i( glGetUniformLocation(program, "fog_mode"), fog_mode);
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
	drawObj(myFloor.floor_buffer, myFloor.vertex_size,GL_TRIANGLES, program, true);  // draw the floor
}
//----------------------------------------------------------------------------
// draw firework
void drawFirework(mat4 &mv, mat4 &p){
	GLuint  program;
	if(!firework.firework_on)	return;
	glPointSize(3.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
	program = programs[2];
	glUseProgram(program); // Use the shader program
	float t = firework.getElapsedTime(glutGet(GLUT_ELAPSED_TIME));
	glUniform1f( glGetUniformLocation(program, "t"), firework.getElapsedTime(glutGet(GLUT_ELAPSED_TIME)));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection" ), 1, GL_TRUE, p); // GL_TRUE: matrix is row-major
	glUniformMatrix4fv(glGetUniformLocation(program, "model_view" ), 1, GL_TRUE, mv); // GL_TRUE: matrix is row-major
	
	//--- Activate the vertex buffer object to be drawn ---//
	glBindBuffer(GL_ARRAY_BUFFER, firework.firework_buffer);
	GLuint vVelocity, vColor;
	/*----- Set up vertex attribute arrays for each vertex attribute -----*/
    vVelocity = glGetAttribLocation(program, "vVelocity");
    glEnableVertexAttribArray(vVelocity);
    glVertexAttribPointer(vVelocity, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	vColor = glGetAttribLocation(program, "vColor"); 
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point3) * firework.vertex_size) ); 
	/* Draw a sequence of geometric objs (triangles) from the vertex buffer
       (using the attributes specified in each enabled vertex attribute array) */
	glDrawArrays(GL_POINTS, 0, firework.vertex_size);

    /*--- Disable each vertex attribute array being enabled ---*/
    glDisableVertexAttribArray(vVelocity);
	glDisableVertexAttribArray(vColor);
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
	
	// Enable blending
	if(blending_shadow){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	if(sphere.shadow && eye[1] > 0){
		program = programs[0];
		glUseProgram(program); // Use the shader program
		// fog mode
		glUniform1i( glGetUniformLocation(program, "fog_mode"), fog_mode);
		glUniform1i( glGetUniformLocation(program, "Texture_app_flag"), 0);
		model_view = glGetUniformLocation(program, "model_view" );
		projection = glGetUniformLocation(program, "projection" );
		if(sphere.lattice_flag)	glUniform1i( glGetUniformLocation(program, "lattice_flag"), sphere.lattice_mode);
		else glUniform1i( glGetUniformLocation(program, "lattice_flag"), 0);
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
		
		drawObj(sphere.shadow_buffer, sphere.vertex_size,GL_TRIANGLES, program, false);  // draw the sphere shadow
	}
	if(blending_shadow){
		glDisable(GL_BLEND);
	}
	// Draw myFloor: only to color buffer
	// Restore default when finished
	mv = LookAt(eye, at, up);
	glDepthMask(GL_TRUE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	drawFloor(mv, p);  // draw the cube
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	
	// draw firework
	drawFirework(mv, p);

	// Draw axises
	program = programs[0];
    glUseProgram(program); // Use the shader program
	// fog mode
	glUniform1i( glGetUniformLocation(program, "fog_mode"), fog_mode);
	glUniform1i( glGetUniformLocation(program, "Texture_app_flag"), 0);
    model_view = glGetUniformLocation(program, "model_view" );
    projection = glGetUniformLocation(program, "projection" );
	glUniform1i( glGetUniformLocation(program, "lattice_flag"), 0);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p); // GL_TRUE: matrix is row-major
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv); // GL_TRUE: matrix is row-major
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0);
	drawObj(myFloor.axis_buffer, myFloor.axis_vertex_size,GL_LINES, program, false);  // draw the axis

	
	
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
	case 'v': case 'V':	sphere.textureCoordDir = _VER_TEX_COORD; break;
	case 's': case 'S': sphere.textureCoordDir = _SLA_TEX_COORD; break;
	case 'o': case 'O': sphere.textureCoordFrame = _TEX_IN_WORLD; break;
	case 'e': case 'E': sphere.textureCoordFrame = _TEX_IN_EYE; break;
	case 'l': case 'L': sphere.lattice_flag = !sphere.lattice_flag; break;
	case 'u': case 'U': sphere.lattice_mode = _UPRIGHT_LATTICE; break;
	case 't': case 'T': sphere.lattice_mode = _TITLED_LATTICE; break;
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
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
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
void fogMenu(int id){
	fog_mode = id-1;
}
//----------------------------------------------------------------------------
void blendingShadowMenu(int id){
	switch(id){
	case 1:
		blending_shadow = false;
		break;
	case 2:
		blending_shadow = true;
		break;
	}
}
//----------------------------------------------------------------------------
void textureMappedGroundMenu(int id){
	switch(id){
	case 1:
		myFloor.texture_mapped_ground = 0;
		break;
	case 2:
		myFloor.texture_mapped_ground = 1;
		break;
	}
}
//----------------------------------------------------------------------------
void textureMappedSphereMenu(int id){
	switch(id){
	case 1:
		sphere.textureFlag = false;
		break;
	case 2:
		sphere.textureFlag = true;
		sphere.texture2D = 0;
		break;
	case 3:
		sphere.textureFlag = true;
		sphere.texture2D = 1;
		break;
	}
}
//----------------------------------------------------------------------------
void fireworkMenu(int id){
	switch(id){
	case 1:
		firework.firework_on = false;
		break;
	case 2:
		if (firework.firework_on == false)firework.start_time = glutGet(GLUT_ELAPSED_TIME);
		firework.firework_on = true;
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
	GLuint subFogMenu = glutCreateMenu(fogMenu);
	glutAddMenuEntry("No Fog",1);
	glutAddMenuEntry("Linear Fog",2);
	glutAddMenuEntry("Exponential Fog",3);
	glutAddMenuEntry("Exponential Square Fog",4);
	GLuint subBSMenu = glutCreateMenu(blendingShadowMenu);
	glutAddMenuEntry("No", 1);
	glutAddMenuEntry("Yes", 2);
	GLuint subGroundTexMenu = glutCreateMenu(textureMappedGroundMenu);
	glutAddMenuEntry("No", 1);
	glutAddMenuEntry("Yes", 2);
	GLuint subSphereTexMenu = glutCreateMenu(textureMappedSphereMenu);
	glutAddMenuEntry("No", 1);
	glutAddMenuEntry("Yes - Contour Lines", 2);
	glutAddMenuEntry("Yes - Checkboard", 3);
	GLuint subFireworkMenu = glutCreateMenu(fireworkMenu);
	glutAddMenuEntry("No", 1);
	glutAddMenuEntry("Yes", 2);
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Default View Port",1);
	glutAddMenuEntry("Quit",2);
	glutAddSubMenu("Shadow", subShadowMenu);
	glutAddSubMenu("Enable Lighting", subLightMenu);
	glutAddSubMenu("Wire Frame Sphere", subWFMenu);
	glutAddSubMenu("Shading", subShadingMenu);
	glutAddSubMenu("Light Source", subLSMenu);
	glutAddSubMenu("Fog", subFogMenu);
	glutAddSubMenu("Blending Shadow", subBSMenu);
	glutAddSubMenu("Texture Mapped Ground", subGroundTexMenu);
	glutAddSubMenu("Texture Mapped Sphere", subSphereTexMenu);
	glutAddSubMenu("Firework", subFireworkMenu);
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
