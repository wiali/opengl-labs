#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <GL\glut.h>
#include <iostream>

class Cube
{
public:
	Cube(float x_, float y_, float z_, float side, bool isDebug_);
	void Draw();
	std::vector< std::vector<float> > Vertexes;
	std::vector< std::vector<float> > Textures;
private:
	void push_vertex(float x, float y, float z);
	void push_texture(float s, float t);
	bool isDebug;
};
#endif // !CUBE_H

