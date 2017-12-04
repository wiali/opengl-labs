#ifndef CYLINDER_H
#define CYLINDER_H
#include <GL\glut.h>
#include "DrawingObject.h"
#include "CVector.h"

class Cylinder : public DrawingObject
{
public:
	Cylinder(CVector4 position, float radius, float height_, GLUquadricObj* obj);
	virtual ~Cylinder();
	virtual void Draw(bool isShadow);
private:
	GLUquadricObj* object_;
	float radius_;
	float height_;
	
};
#endif // !CYLINDER_H

