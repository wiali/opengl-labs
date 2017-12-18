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

int r = 10;
float fi = 0;
float z2 = -1;
float k = 1;

GLfloat mat_amb1[] = { 0.2, 0.2, 0.2, 1 };
GLfloat mat_dif1[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_spec1[] = { 1, 1, 1, 1 };
GLfloat mat_emi1[] = { 0, 0, 0, 1 };
GLfloat mat_shin1 = 128;

GLfloat mat_amb2[] = { 0.2, 0.2, 0.2, 0.6 };
GLfloat mat_dif2[] = { 0.8, 0.8, 0.8, 0.6 };
GLfloat mat_spec2[] = { 0, 0, 0, 0.6 };
GLfloat mat_emi2[] = { 0, 0, 0, 1 };
GLfloat mat_shin2 = 0;

GLfloat mat_amb3[] = { 0.2, 0.2, 0.2, 1 };
GLfloat mat_dif3[] = { 0.8, 0.8, 0.8, 1 };
GLfloat mat_spec3[] = { 0, 0, 0, 1 };
GLfloat mat_emi3[] = { 0, 0, 0, 1 };
GLfloat mat_shin3 = 0;

AUX_RGBImageRec* tex1;
AUX_RGBImageRec* tex2;
AUX_RGBImageRec* tex3;

void part1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glLoadIdentity();

	float x = r*cos(fi);
	float y = r*sin(fi);

	GLfloat light1_diffuse[] = {0, 0.0, 1, 1.0};
	GLfloat light1_position[] = {x, y, 0, 1.0};
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);

	GLfloat light2_diffuse[] = {1, 0, 0, 1.0};
	GLfloat light2_position[] = {z2, 0, -2.5, 1};
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.6);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.6);

	gluLookAt(0, 0, -6, 0, 0, 0, 0, 1, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		tex3->sizeX,
		tex3->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		tex3->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emi1);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shin1);

	glPushMatrix();
	glTranslated(0.5, 0.5, 2);
	glutSolidSphere(1, 10, 20);
	glPopMatrix();

	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		tex1->sizeX,
		tex1->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		tex1->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emi2);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shin2);

	glPushMatrix();
	glRotated(30, 0.0, 1.0, 0.0);
	glutSolidTetrahedron();
	glPopMatrix();

	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		tex2->sizeX,
		tex2->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		tex2->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emi3);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shin3);

	glPushMatrix();
	glTranslated(-1.5, 0, -2.0);
	glRotated(-30, 0.0, 1.0, 0.0);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	fi = fi + 0.05;

	if (z2 < -1 || z2 > 3)
	{
		k *= -1;
	}

	z2 = z2 + k * 0.1;
	
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
	part1();
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

	glutCreateWindow("Lab_2");

	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(50, Timer, 0);

	glClearColor(1, 1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	tex1 = auxDIBImageLoad(L"tex1.bmp");
	tex2 = auxDIBImageLoad(L"tex2.bmp");
	tex3 = auxDIBImageLoad(L"tex3.bmp");

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();

	return EXIT_SUCCESS;
}