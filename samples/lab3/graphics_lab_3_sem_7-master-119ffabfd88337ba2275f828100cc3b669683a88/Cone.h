#ifndef CONE_H
#define CONE_H

#include "DrawingObject.h"

#include <GL\glut.h>
#include <vector>

class Cone : public DrawingObject
{
public:
	Cone(float x, float y, float z, float radius, float hight,float red, float green, float blue);
	virtual void Draw(bool isShadow);
private:
	float x_;
	float y_;
	float z_;
	float radius_;
	float hight_;

	float mat_diffuse[4];
	float mat_amb[4];
	float mat_spec[4];
	float mat_shininess;

	float red_;
	float green_;
	float blue_;
};

#endif // !CONE_H