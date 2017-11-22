/*
 * Struct for sphere
 * Author: Weichen Xu
 * Date : 11/10/2015
 * init & load information for sphere
 * Rolling attribute and function
*/
#ifndef  _WCX_sphere
#define  _WCX_sphere
#include "Angel-yjc.h"
#include "light_products.h"
#include <string>
#include <iostream>
#include <fstream>
#define _MAX_SPHERE_VERTICES	1024
#define _VER_TEX_COORD 0
#define _SLA_TEX_COORD 1
#define _TEX_IN_WORLD 2
#define _TEX_IN_EYE 4
#define _UPRIGHT_LATTICE 1
#define _TITLED_LATTICE 2
#define PI 3.1415
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
typedef Angel::vec3  point3;
class WCX_sphere{
private:
	float rollingSpeed, radius;	// speed radian per frame
	vec4 rollingDirection, rollingAxis; // rotation direction: point B->A, rotation axis, Y cross dir
	vec4 rollingStart;	// start point of the current rolling seg
	mat4 accumuRollingM;	// Accumulated rolling matrix
public:
	WCX_sphere();
	GLuint sphere_buffer,shadow_buffer;	/*vertex buffer object id for sphere */
	bool fill_flag;
	bool shadow;
	int vertex_size;
	point4 sphere_points[_MAX_SPHERE_VERTICES*3];
	point3 sphere_normals[_MAX_SPHERE_VERTICES*3];
	color4 sphere_colors[_MAX_SPHERE_VERTICES*3];
	color4 shadow_colors[_MAX_SPHERE_VERTICES*3];
	void setColor(color4 uniformColor);
	// attributes for shading
	bool lighting_flag;
	// attributes for texture mapping
	bool textureFlag;
	int textureCoordFrame;
	int textureCoordDir;
	int texture2D;
	// attributes for lattice
	bool lattice_flag;
	int lattice_mode;

	WCX_light_products lp;
	//----------------------------------------------
	//functions for rolling
	void loadSphereFromFile();
	void setRadius(float rad){this->radius = rad;}
	int rollingFromAToB(point4 A, point4 B, mat4 lastRotateM); // rolling sphere from A to B
	mat4 rollingFramePosition(int frame); // get rolling translate matrix at frame n
	//vec3 getRollingAxis(){return this->rollingAxis;} 
	mat4 rollingFrameRotate(int frame); // get rolling rotation matrix at frame n

	//----------------------------------------------
	//functions for shadow
	void setShadowColor(color4 color);
	//----------------------------------------------
	//functions for shading
	void setMaterial();
	void setFlatNormals();
	//----------------------------------------------
	//functions for texture
	int getTextureAppFlag();
};
#endif