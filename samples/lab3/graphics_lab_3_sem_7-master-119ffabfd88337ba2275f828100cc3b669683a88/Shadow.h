#ifndef SHADOW_H
#define SHADOW_H
#include <GL\glut.h>
#include "CVector.h"
#include "CMatrix.h"
#include "Cylinder.h"
#include "DrawingObject.h"

void drawShadow(CVector4 plane, CVector4 lighPos, DrawingObject& obj)
{
	CMatrix4x4 ShadowMatrix = CMatrix4x4();
	ShadowMatrix.CreateShadowMatrix(plane, lighPos);
	{
		glPushMatrix();
		glMultMatrixf(ShadowMatrix.matrix);
		obj.Draw(true);
		glPopMatrix();
	}
}
#endif // !SHADOW_H
