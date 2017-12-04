#include "Torus.h"

Torus::Torus()
{
}

Torus::Torus(CVector4 pos, double radius, double c, int rSeg, int cSeg, int texture)
{
	position_ = pos;
	radius_ = radius;
	c_ = c;
	rSeg_ = rSeg;
	cSeg_ = cSeg;
	texture_ = texture;
}

void Torus::Draw(bool isShadow)
{
	if (!isShadow)
	{
		float diffuse[4] = { .3 , .3, .3, 0.4 };
		float ambient[4] = { 0.2, 0.0, 0.5, 0.4 };
		float spec[4] = { 1.0,1.0,1.0, 0.4 };
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
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	}

	//glFrontFace(GL_CW);

	glPushMatrix();
	glTranslatef(position_.x, position_.y, position_.z);
	glRotatef(90, 1, 0, 0);

	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	const double PI = 3.1415926535897932384626433832795;
	const double TAU = 2 * PI;

	for (int i = 0; i < rSeg_; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= cSeg_; j++) {
			for (int k = 0; k <= 1; k++) {
				double s = (i + k) % rSeg_ + 0.5;
				double t = j % (cSeg_ + 1);

				double x = (c_ + radius_ * cos(s * TAU / rSeg_)) * cos(t * TAU / cSeg_);
				double y = (c_ + radius_ * cos(s * TAU / rSeg_)) * sin(t * TAU / cSeg_);
				double z = radius_ * sin(s * TAU / rSeg_);

				double u = (i + k) / (float)rSeg_;
				double v = t / (float)cSeg_;

				glTexCoord2d(u, v);
				glNormal3f(2 * x, 2 * y, 2 * z);
				glVertex3d(2 * x, 2 * y, 2 * z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	//glFrontFace(GL_CCW);
}
