#include "floor.h"

WCX_floor::WCX_floor(){
	vertex_size = _FLOOR_VERTICES;
	axis_vertex_size = _AXIS_VERTICES;
}

bool WCX_floor::setFloor(point4 topR, point4 downL){
	if(topR.y != downL.y)	return false;
	int y = topR.y;
	floor_points[0] = color4(topR.x,y,topR.z, 1.0);
	floor_points[1] = color4(topR.x,y,downL.z, 1.0);
	floor_points[2] = color4(downL.x,y,downL.z, 1.0);
	floor_points[3] = color4(topR.x,y,topR.z, 1.0);
	floor_points[4] = color4(downL.x,y,topR.z, 1.0);
	floor_points[5] = color4(downL.x,y,downL.z, 1.0);
	// init normals
	for(int i=0; i<vertex_size; i++){
		floor_normals[i] = point3(0.0, 1.0, 0.0);
	}
	// set texture cord
	floor_texture_cord[0] = vec2(5.0, 6.0);
	floor_texture_cord[1] = vec2(5.0, 0.0);
	floor_texture_cord[2] = vec2(0.0, 0.0);
	floor_texture_cord[3] = vec2(5.0, 6.0);
	floor_texture_cord[4] = vec2(0.0, 6.0);
	floor_texture_cord[5] = vec2(0.0, 0.0);
	return true;
}
void WCX_floor::setColor(color4 color){
	for(int i=0; i<_FLOOR_VERTICES; i++){
		
		floor_colors[i] = color;
	}
}
void WCX_floor::generateAxis(){
	// axis x
	axis_points[0] = point4(0.0,0.0,0.0,1.0);	axis_colors[0] = color4(1.0,0.0,0.0,1.0);
	axis_points[1] = point4(10.0,0.0,0.0,1.0);	axis_colors[1] = color4(1.0,0.0,0.0,1.0);
	axis_points[2] = point4(0.0,0.0,0.0,1.0);	axis_colors[2] = color4(1.0,0.0,1.0,1.0);
	axis_points[3] = point4(0.0,10.0,0.0,1.0);	axis_colors[3] = color4(1.0,0.0,1.0,1.0);
	axis_points[4] = point4(0.0,0.0,0.0,1.0);	axis_colors[4] = color4(0.0,0.0,1.0,1.0);
	axis_points[5] = point4(0.0,0.0,10.0,1.0);	axis_colors[5] = color4(0.0,0.0,1.0,1.0);
}
void WCX_floor::setMaterial(){
	this->lp.material_ambient = color4(0.2, 0.2, 0.2, 1.0);
	this->lp.material_diffuse = color4(0.0, 1.0, 0.0, 1.0);
	this->lp.material_specular = color4(0.0, 0.0, 0.0, 1.0);
	this->lp.material_shininess = 1.0;
}
