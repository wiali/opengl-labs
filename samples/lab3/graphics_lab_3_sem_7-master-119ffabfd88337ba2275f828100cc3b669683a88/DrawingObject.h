#ifndef DRAWING_OBJECT_H
#define DRAWING_OBJECT_H
#include "CVector.h"
#include <GL\glut.h>

class DrawingObject
{
public:
	virtual void Draw(bool isShadow) = 0;
	CVector4 position_;	
};
#endif // !DRAWING_OBJECT_H

