/***************************
 * File: vshader42.glsl:
 *   A simple vertex shader.
 *
 * - Vertex attributes (positions & colors) for all vertices are sent
 *   to the GPU via a vertex buffer object created in the OpenGL program.
 *
 * - This vertex shader uses the Model-View and Projection matrices passed
 *   on from the OpenGL program as uniform variables of type mat4.
 ***************************/

#version 150 // YJC: Comment/un-comment this line to resolve compilation errors
                 //      due to different settings of the default GLSL version

in  vec4 vPosition;
in  vec4 vColor;
in  vec2 vTexCoord;

out vec4 color;
out vec4 ePosition; // position in eye frame
out vec4 oPosition; // position in world frame
out float texS;
out float texT;
out float latS;
out float latT;

uniform mat4 model_view;
uniform mat4 projection;
uniform int Texture_app_flag;
uniform int lattice_flag;
void main() 
{
    // YJC: Original, incorrect below:
    //      gl_Position = projection*model_view*vPosition/vPosition.w;
	oPosition = vPosition;
	ePosition = model_view*vPosition;
    gl_Position = projection * model_view * vPosition;
	color = vColor;
	// texture coord compuation and set
	switch(Texture_app_flag){
	case 1:
		texS = vTexCoord.x;
		texT = vTexCoord.y;
		break;
	case 2:
		texS = 2.5*oPosition.x;
		break;
	case 3:
		texS = 1.5*(oPosition.x+oPosition.y+oPosition.z);
		break;
	case 4:
		texS = 2.5*ePosition.x;
		break;
	case 5:
		texS = 1.5*(ePosition.x+ePosition.y+ePosition.z);
		break;
	case 6:
		texS = 0.75*(oPosition.x+1);
		texT = 0.75*(oPosition.y+1);
		break;
	case 7:
		texS = 0.45*(oPosition.x+oPosition.y+oPosition.z);
		texT = 0.45*(oPosition.x-oPosition.y+oPosition.z);
		break;
	case 8:
		texS = 0.75*(ePosition.x+1);
		texT = 0.75*(ePosition.y+1);
		break;
	case 9:
		texS = 0.45*(ePosition.x+ePosition.y+ePosition.z);
		texT = 0.45*(ePosition.x-ePosition.y+ePosition.z);
		break;
	default:
		break;
	}
	if(lattice_flag == 1){
		latS = 0.5*oPosition.x + 1;
		latT = 0.5*oPosition.y + 1;
	}
	if(lattice_flag == 2){
		latS = 0.3*(oPosition.x+oPosition.y+oPosition.z);
		latT = 0.3*(oPosition.x-oPosition.y+oPosition.z);
	}
} 
