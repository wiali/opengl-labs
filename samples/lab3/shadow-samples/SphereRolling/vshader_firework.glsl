/***************************
 * File: vshader_firework.glsl
 *	vertex shader for firework particle
 ***************************/

#version 150
in vec3 vColor;
in vec3 vVelocity;
out vec4 color;
out vec4 oPosition; // world position

uniform mat4 model_view;
uniform mat4 projection;
uniform float t; // pass the time in miliseconds
void main() 
{
    vec3 init_pos = vec3(0.0, 0.1, 0.0);
	float x,y,z;
	float a = -0.00000049;
	
	// calculate world pos for each particle
	x = init_pos.x + 0.001*t*vVelocity.x;
	y = init_pos.y + 0.001*t*vVelocity.y + 0.5*a*t*t; 
	z = init_pos.z + 0.001*t*vVelocity.z;

	color = vec4(vColor, 1.0);
	gl_Position = projection * model_view*vec4(x, y, z, 1.0);
	oPosition = vec4(x,y,z,1.0);
} 
