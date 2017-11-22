#include "firework.h"
void WCX_firework::setFirework(){
	this->firework_on = false;
	this->vertex_size = _PARTICLE_NUM;
	for(int i=0; i<_PARTICLE_NUM; i++){
		particle_velocity[i].x = 2.0*((rand()%256)/256.0-0.5);
		particle_velocity[i].y = 1.2*2.0*((rand()%256)/256.0);
		particle_velocity[i].z = 2.0*((rand()%256)/256.0-0.5);
		particle_color[i].x = (rand()%256)/256.0;
		particle_color[i].y = (rand()%256)/256.0;
		particle_color[i].z = (rand()%256)/256.0;
	}
}
// return the t%_T_MAX
float WCX_firework::getElapsedTime(float currentTime){
	int divider = (currentTime - this->start_time)/_T_MAX;
	return currentTime - this->start_time - divider*_T_MAX;
}