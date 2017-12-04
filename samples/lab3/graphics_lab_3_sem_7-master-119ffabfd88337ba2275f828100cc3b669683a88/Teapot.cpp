#include "Teapot.h"

Teapot::Teapot(CVector4 position)
{
	position_ = position;
}

void Teapot::Draw(bool isShadow)
{
	if (!isShadow)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float diffuse[4] = { .3,.3,.3, 0.3 };
		float ambient[4] = { 1.0,1.0,1.0, 0.3};
		float spec[4] = { 1.0,1.0,1.0,0.3 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	}
	else
	{
		float diffuse[4] = { 0,0,0 };
		float ambient[4] = { 0,0,0 };
		float spec[4] = { 0,0,0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
	}
	glPushMatrix();
	{
		glEnable(GL_TEXTURE_2D);
		glTranslatef(position_.x, position_.y, position_.z);
		glutSolidTeapot(12);
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
	
	if (!isShadow)
	{
		glDisable(GL_BLEND);
	}
}
