/*
 * Struct for floor
 * Author: Weichen Xu
 * Date : 11/10/2015
 * Generate floor points & color
*/
#ifndef _WCX_floor
#define _WCX_floor
#include "Angel-yjc.h"
#include "light_products.h"
#define _FLOOR_VERTICES 2*3
#define _AXIS_VERTICES 3*2
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
typedef Angel::vec3  point3;
class WCX_floor{
public:
	WCX_floor();
	GLuint floor_buffer;	/*vertex buffer object id for floor */
	GLuint axis_buffer;
	int vertex_size;
	int axis_vertex_size;
	bool fill_flag;
	point4 floor_points[_FLOOR_VERTICES];
	color4 floor_colors[_FLOOR_VERTICES];
	point4 axis_points[_AXIS_VERTICES];
	color4 axis_colors[_AXIS_VERTICES];

	// attributes for shading
	bool lighting_flag;
	point3 floor_normals[_FLOOR_VERTICES];
	WCX_light_products lp;
	// attributes for texture
	int texture_mapped_ground;
	vec2 floor_texture_cord[_FLOOR_VERTICES];

	bool setFloor(point4 topR, point4 downL);
	void setColor(color4 uniformColor);
	void generateAxis();
	//----------------------------------------------
	//functions for lighting
	void setMaterial();
	
};
#endif