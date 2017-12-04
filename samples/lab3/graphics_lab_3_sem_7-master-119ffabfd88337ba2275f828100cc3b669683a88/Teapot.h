#ifndef TEAPOT_H
#define TEAPOT_H
#include "DrawingObject.h"

class Teapot : public DrawingObject
{
public:
	Teapot(CVector4 position);
	virtual void Draw(bool isShadow);
private:
	CVector4 position_;
};
#endif // !TEAPOT_H

