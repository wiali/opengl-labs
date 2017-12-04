
#ifndef SPHERE_H
#define SPHERE_H

#include "DrawingObject.h"

#include <vector>
#include <GL\glut.h>
#include <iostream>

class Sphere : public DrawingObject
{
public:
	Sphere(float cx, float cy, float cz, float r, int p);
	Sphere();
	virtual void Draw(bool isShadow);
	std::vector< std::vector<float> > Vertexes;
	std::vector< std::vector<float> > TexCoords;
};
#endif // SPHERE_H