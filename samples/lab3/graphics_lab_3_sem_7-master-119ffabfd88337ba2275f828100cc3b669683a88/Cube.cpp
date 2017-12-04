#include "Cube.h"

Cube::Cube(float x_, float y_, float z_, float side, bool isDebug_)
{
	isDebug = isDebug_;

	push_texture(0, 0);
	push_vertex(x_, y_, z_);
	push_texture(1, 0);
	push_vertex(x_ + side, y_, z_);
	push_texture(0, 1);
	push_vertex(x_, y_ + side, z_);
	push_texture(1, 1);
	push_vertex(x_ + side, y_ + side, z_);

	push_texture(0, 0);
	push_vertex(x_, y_ + side, z_);
	push_texture(1, 0);
	push_vertex(x_ + side, y_ + side, z_);
	push_texture(0, 1);	
	push_vertex(x_, y_ + side, z_ + side);
	push_texture(1, 1);
	push_vertex(x_ + side, y_ + side, z_ + side);

	push_texture(0, 0);
	push_vertex(x_, y_ + side, z_ + side);
	push_texture(0, 1);
	push_vertex(x_ + side, y_ + side, z_ + side);
	push_texture(1, 0);
	push_vertex(x_, y_, z_ + side);
	push_texture(1, 1);
	push_vertex(x_ + side, y_, z_ + side);

	push_texture(0, 0);
	push_vertex(x_, y_, z_ + side);
	push_texture(0, 1);
	push_vertex(x_ + side, y_, z_ + side);
	push_texture(1, 0);
	push_vertex(x_, y_, z_);
	push_texture(1, 1);
	push_vertex(x_ + side, y_, z_);

	push_texture(0, 0);
	push_vertex(x_, y_, z_);
	push_texture(0, 1);
	push_vertex(x_, y_ + side, z_);
	push_texture(1, 0);
	push_vertex(x_, y_, z_ + side);
	push_texture(1, 1);
	push_vertex(x_, y_ + side, z_ + side);

	push_texture(0, 0);
	push_vertex(x_ + side, y_, z_);
	push_texture(0, 1);
	push_vertex(x_ + side, y_ + side, z_);
	push_texture(1, 0);
	push_vertex(x_ + side, y_, z_ + side);
	push_texture(1, 1);
	push_vertex(x_ + side, y_ + side, z_ + side);
}

void Cube::Draw()
{	

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	//glBegin(GL_LINE_STRIP);
	float matAmbientAndDiffuse[4] = { 1.0f, 1.0f, 1.0f, 0.8f };
	float matSpecular[4] = { 0.0f, 0.0f, 0.0f, 0.8f };
	float shininess = 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbientAndDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glBegin(GL_QUADS);
	for (int idx = 0; idx < Vertexes.size(); ++idx)
	{
		glTexCoord2f(Textures[idx][0], Textures[idx][1]);
		glVertex3f(Vertexes[idx][0], Vertexes[idx][1], Vertexes[idx][2]);		
	}
	glEnd();

	//glDisable(GL_BLEND);
}

void Cube::push_vertex(float x, float y, float z)
{
	std::vector<float> temp;
	temp.push_back(x);
	temp.push_back(y);
	temp.push_back(z);
	Vertexes.push_back(temp);
	temp.clear();
}
void Cube::push_texture(float s, float t)
{
	std::vector<float> temp;
	temp.push_back(s);
	temp.push_back(t);
	Textures.push_back(temp);
}
