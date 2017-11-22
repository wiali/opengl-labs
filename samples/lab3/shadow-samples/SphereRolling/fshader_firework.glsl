/***************************
 * File: fshader_firework.glsl:
 *   fragment shader for firework particle
 ***************************/

#version 150
in vec4 color;
in vec4 oPosition;
out vec4 fColor;
void main() 
{
	if(oPosition.y < 0.1){
		discard;
	}
    fColor = color;
} 
