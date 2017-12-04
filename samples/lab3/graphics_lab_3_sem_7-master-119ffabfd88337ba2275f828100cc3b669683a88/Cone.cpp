#include "Cone.h"
#define PI 3.1415926

Cone::Cone(float x, float y, float z, float radius, float hight, float red, float green, float blue) 
	//: mat_amb { red * 0.2f, green * 0.2f, blue * 0.2f, 1.0f }
	//, mat_diffuse{ red * 0.7f, green * 0.7f, blue * 0.7f, 1.0f }
	//, mat_spec{ 0.0f,0.0f,0.0f,0.0f }
{
	float temp[4] = { red * 0.2f, green * 0.2f, blue * 0.2f, 1.0f };
	std::copy(temp, temp + 4, mat_amb);
	float temp1[4] = { red * 0.7f, green * 0.7f, blue * 0.7f, 1.0f };
	std::copy(temp1, temp1 + 4, mat_diffuse);
	//mat_diffuse = { red * 0.7f, green * 0.7f, blue * 0.7f, 1.0f };
	float temp2[4] = { 0.0f,0.0f,0.0f,0.0f };
	std::copy(temp2, temp2 + 4, mat_spec);
	//mat_spec = { 0.0f,0.0f,0.0f,0.0f };

	x_ = x;
	y_ = y;
	z_ = z;
	radius_ = radius;
	hight_ = hight;
	mat_shininess = 128;
	
}

void Cone::Draw(bool isShadow)
{
	std::vector<std::vector<float>> bottom;
	if (!isShadow)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float diffuse[4] = { .3,.3,.3, 0.4 };
		float ambient[4] = { 1.0,1.0,1.0, 0.4};
		float spec[4] = { 1.0,1.0,1.0,0.4 };
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
	const int polygons = 50;
	glBegin(GL_TRIANGLE_FAN);
	//glColor3f(red_, green_, blue_);
	glVertex3f(x_ - hight_, y_, z_);	

	for (float temp = 0; temp < (2 * PI) + PI / polygons; temp += 2 * PI / polygons)
	{
		std::vector<float> vertex;
		glVertex3f(x_, y_ + radius_*sinf(temp), z_ + radius_*cosf(temp));
		vertex.push_back(x_);
		vertex.push_back(y_ + radius_*sinf(temp));
		vertex.push_back(z_ + radius_*cosf(temp));
		bottom.push_back(vertex);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < bottom.size(); ++i)
	{
		glVertex3f(bottom[i][0], bottom[i][1], bottom[i][2]);
	}
	glEnd();
	
	if (!isShadow)
	{
		glDisable(GL_BLEND);
	}
}
