#ifndef TORUS_H
#define TORUS_H
#include <GL\glut.h>
#include "DrawingObject.h"

class Torus : public DrawingObject
{
public:
	Torus();
	Torus(CVector4 pos, double radius, double c, int rSeg, int cSeg, int texture);
	virtual void Draw(bool isShadow);
private:
	double radius_;
	double c_;
	int rSeg_;
	int cSeg_;
	int texture_;
};
#endif // !TORUS_H

