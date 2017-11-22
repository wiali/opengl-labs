/*
 * Struct for firework
 * Author: Weichen Xu
 * Date : 12/19/2015
 * init & set attributes for firework, each particle
*/
#ifndef  _WCX_firework
#define  _WCX_firework
#include "Angel-yjc.h"
#define _PARTICLE_NUM 300
#define _T_MAX	10000.0
typedef Angel::vec3  color3;
typedef Angel::vec3  point3;
class WCX_firework{
public:
	bool firework_on;
	int vertex_size;
	float start_time;

	GLuint firework_buffer;
	point3 particle_velocity[_PARTICLE_NUM];
	color3 particle_color[_PARTICLE_NUM];
	void setFirework();
	float getElapsedTime(float currentTime);
};
#endif