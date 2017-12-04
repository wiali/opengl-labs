#pragma comment( lib, "glaux.lib" )
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include "glaux.h"

struct point
{
	double x, y, z;
};

float rotation = 0;
float k = 1;
double time = 0;
int check = 1;
const int pointsNum = 6;

AUX_RGBImageRec* photo_image;
point matrix[pointsNum][pointsNum][pointsNum];
point sphereMatrix[pointsNum][pointsNum][pointsNum];
point vectors[pointsNum][pointsNum][pointsNum];

void part1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(80, 50, -100, 0, 0, 0, 0, 1, 0);

	glColor3d(1, 0, 0);
	glPushMatrix();
	glTranslated(40, 30, -50 - 20);
	glRotated(rotation, 0.0, 1.0, 0.0);
	glutWireCube(25);
	glPopMatrix();

	glColor3d(0, 0, 0);
	glPushMatrix();
	glTranslated(40, 30, -50);
	glRotated(rotation, 0.0, 1.0, 0.0);
	glScaled(1.25, 1.25, 1.25);
	glutWireSphere(21.6505, 20, 20);
	glPopMatrix();

	rotation += 1.0;
	if (rotation >= 360) rotation -= 360;

	glutSwapBuffers();
}

void part2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glLoadIdentity();
	//gluLookAt(80, 50, -100, 0, 0, 0, 0, 1, 0);

	glColor3d(0.4, 0.5, 0);
	glPushMatrix();
	glTranslated(0, 0, -6);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glRotated(rotation, 1.0, 0.0, 0.0);
	glutSolidTorus(1, 2, 20, 20);
	glPopMatrix();

	glColor3d(1, 0, 0);
	glPushMatrix();
	glTranslated(0.5, 0.5, -6);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glRotated(rotation, 0.0, 1.0, 0.0);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	rotation += k;
	if (rotation >= 120)
	{
		k = -1;
	}
	else if (rotation <= 0)
	{
		k = +1;
	}

	glutSwapBuffers();
}

void part3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 0, 0);
	glLoadIdentity();
	gluLookAt(-10, 15, -40, 0, 0, 0, 0, 1, 0);
	glRotated(rotation, 0.0, 1.0, 0.0);
	glPointSize(5);
	glBegin(GL_POINTS);

	for (int i = 0; i < pointsNum; ++i)
	{
		for (int j = 0; j < pointsNum; ++j)
		{
			for (int k = 0; k < pointsNum; ++k)
			{
				if (matrix[i][j][k].x != 0 && matrix[i][j][k].y != 0 && matrix[i][j][k].z != 0)
				{
					if (check == 1) {
						glVertex3d(matrix[i][j][k].x + vectors[i][j][k].x * time, matrix[i][j][k].y + vectors[i][j][k].y * time, matrix[i][j][k].z + vectors[i][j][k].z * time);
					}
					else
					{
						glVertex3d(matrix[i][j][k].x + vectors[i][j][k].x * time, matrix[i][j][k].y + vectors[i][j][k].y * time, matrix[i][j][k].z + vectors[i][j][k].z * time);
					}
					
				}
			}
		}
	}

	glEnd();

	time = time + check * 0.01;
	if (time > 1 || time < 0) check *= -1;

	rotation += 1.0;
	if (rotation >= 360) rotation -= 360;

	glutSwapBuffers();
}

static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void display(void)
{
	//part1();
	//part2();
	part3();
	
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Lab_1_1");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(50, Timer, 0);

	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_TEXTURE_2D);
	photo_image = auxDIBImageLoad(L"awesomeface.bmp");

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		photo_image->sizeX,
		photo_image->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		photo_image->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	double step = 1;
	double shift = -2.5;

	for (int i = 0; i < pointsNum; ++i)
	{
		for (int j = 0; j < pointsNum; ++j)
		{
			for (int k = 0; k < pointsNum; ++k)
			{
				if (k > 0 && k < pointsNum - 1 && j > 0 && j < pointsNum - 1 && i > 0 && i < pointsNum - 1) {}
				else
				{
					matrix[i][j][k].x = k * step + shift;
					matrix[i][j][k].y = j * step + shift;
					matrix[i][j][k].z = i * step + shift;
				}
			}
		}
	}

	double radius = 5;

	for (int i = 0; i < pointsNum; ++i)
	{
		for (int j = 0; j < pointsNum; ++j)
		{
			for (int k = 0; k < pointsNum; ++k)
			{
				if (matrix[i][j][k].x != 0 && matrix[i][j][k].y != 0 && matrix[i][j][k].z != 0)
				{
					double d = sqrt((pow(matrix[i][j][k].x, 2) + pow(matrix[i][j][k].y, 2) + pow(matrix[i][j][k].z, 2)));
					double theta = acos(matrix[i][j][k].z / d);
					double phi = atan2(matrix[i][j][k].y, matrix[i][j][k].x);

					sphereMatrix[i][j][k].x = radius * sin(theta) * cos(phi);
					sphereMatrix[i][j][k].y = radius * sin(theta) * sin(phi);
					sphereMatrix[i][j][k].z = radius * cos(theta);

					vectors[i][j][k].x = sphereMatrix[i][j][k].x - matrix[i][j][k].x;
					vectors[i][j][k].y = sphereMatrix[i][j][k].y - matrix[i][j][k].y;
					vectors[i][j][k].z = sphereMatrix[i][j][k].z - matrix[i][j][k].z;
				}
			}
		}
	}

	glutMainLoop();

	return EXIT_SUCCESS;
}