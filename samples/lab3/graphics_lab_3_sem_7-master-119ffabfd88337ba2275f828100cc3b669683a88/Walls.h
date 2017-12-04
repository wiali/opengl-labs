#ifndef  WALLS_H
#define WALLS_H
#include <GL\glut.h>

const int side = 80;

void drawBackWall()
{
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	{
		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(side, 0, 0);
		glTexCoord2f(1, 0);
		glVertex3f(side, side, 0);
		glTexCoord2f(1, 1);
		glVertex3f(0, side, 0);
		glTexCoord2f(0, 1);
	}
	glEnd();
}
void drawLeftWall()
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	{
		glNormal3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, side*3);
		glTexCoord2f(0, 1);
		glVertex3f(0, side, side*3);
		glTexCoord2f(1, 1);
		glVertex3f(0, side, 0);
		glTexCoord2f(1, 0);
	}
	glEnd();

}
void drawRightWall()
{
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	{		
		glNormal3f(-1, 0, 0);

		glVertex3f(side, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(side, 0, side*3);
		glTexCoord2f(0, 1);
		glVertex3f(side, side, side*3);
		glTexCoord2f(1, 1);
		glVertex3f(side, side, 0);
		glTexCoord2f(1, 0);
	}
	glEnd();
}
void drawDownWall()
{
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
	{
		glNormal3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(side, 0, 0);
		glVertex3f(side, 0, side*3);
		glVertex3f(0, 0, side*3);
	}
	glEnd();
}
void drawUpWall()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	{
		glNormal3f(0, -1, 0);
		glVertex3f(0, side, 0);
		glVertex3f(side, side, 0);
		glVertex3f(side, side, side*3);
		glVertex3f(0, side, side*3);
	}
	glEnd();
}
void drawWalls()
{
	
	glBegin(GL_QUADS);
	{

		glNormal3f(0, -1, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(side, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(side, 0, side);
		glTexCoord2f(1, 1);
		glVertex3f(0, 0, side);
		glTexCoord2f(1, 0);

		glNormal3f(0, -1, 0);
		glVertex3f(0, side, 0);
		glTexCoord2f(0, 0);
		glVertex3f(side, side, 0);
		glTexCoord2f(0, 1);
		glVertex3f(side, side, side);
		glTexCoord2f(1, 1);
		glVertex3f(0, side, side);
		glTexCoord2f(1, 0);
	}
	glEnd();

}
#endif // ! WALLS_H