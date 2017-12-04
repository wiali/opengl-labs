/*
*
*/
#include <stdlib.h>
//#include <glut.h>
#include <GL\glut.h>
#include <math.h>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <SFML\Graphics\Image.hpp>

#include "Cone.h"
#include "CVector.h"
#include "CMatrix.h"
#include "Walls.h"
#include "Shadow.h"
#include "Cylinder.h"
#include "Teapot.h"
#include "Torus.h"
#include "Sphere.h"

/* ширина и высота окна */
GLint Width = 1024, Height = 1024;
char* windowName = "Lab3";

// angle of rotation for the camera direction
float angle = 0.0;
float angleY = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 40.0f, y = 30.0f, z = 160.0f;

float mat_diffuse[] = { 1.0f,1.0f,1.0f };
float mat_amb[] = { 0.3f,1.0f,0.3f };
float mat_spec[] = { 0.6f,0.6f,0.6f };
float mat_shininess = 1.0f * 128;
bool isRotating0 = false;
bool isRotating1 = false;

GLuint TexId;

#define PI 3.1415926
GLUquadric * sphereLight0 = gluNewQuadric();
GLUquadric * sphereLight1 = gluNewQuadric();


bool isDebug = true;

GLUquadricObj *quadObj = gluNewQuadric();
int xLight0 = 8;
int yLight0 = 3;
int zLight0 = 30;

float blueLight1 = 0.0;

CVector4 lightPos(15, 15, 60, 1.0f);

CVector4 cylinderPos = CVector4(25, 30, 20);
CVector4 torusPos = CVector4(cylinderPos);
float cylinderHeight = 20;
float cylinderRadius = 10;

//Cylinder cylinder = Cylinder(cylinderPos, cylinderRadius, cylinderHeight, quadObj);
//Teapot teapot = Teapot(CVector4(60, 40, 20));
Torus torus;
Cone cone = Cone(50, 40, 30, 10, 10, 0.3f, 0.0f, 0.5f);
Sphere sphere = Sphere(20, 15, 10, 7, 10);


void TextureInit()
{
	sf::Image img;
	//img.loadFromFile("quads.png");
	img.loadFromFile("tex_tiles.bmp");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TexId);


	glBindTexture(GL_TEXTURE_2D, TexId);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.getSize().x, img.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	gluQuadricTexture(quadObj, GL_TRUE);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	torusPos.y += 5;
	torus = Torus(torusPos, 1, 6, 20, 20, TexId);
}

void init()
{
	// цвет фона
	glClearColor(0.1f, 0.1f, 0.3f, 0.0f);
	// рассчет освещения
	glEnable(GL_LIGHTING);
	// двухсторонний расчет освещения
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	TextureInit();
	
}

void renderScene(void)
{
	glEnable(GL_NORMALIZE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light0_diffuse[] = { 1, 1, 1, 1.0 };
	GLfloat light0_position[] = { lightPos.x, lightPos.y, lightPos.z, 1.0 };
	GLfloat ambient0[] = { 1*0.3, 1*0.3, 1*0.3, 1.0 };
	GLfloat specular0[] = { 1.0, 1.0, 1.0, 1.0 };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 128);


	// Reset transformations
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);

	
	glBegin(GL_QUADS);
	{
		const int floor = 15;
		const int side = 500;
		glTexCoord2f(0, 0);
		glVertex3f(side*(-1), floor*(-1), side*(-1));
		glTexCoord2f(0, 1);
		glVertex3f(side, floor*(-1), side*(-1));
		glTexCoord2f(1, 1);
		glVertex3f(side, floor*(-1), side);
		glTexCoord2f(1, 0);
		glVertex3f(side*(-1), floor*(-1), side);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);

	const int side = 80;
	CVector4 planeNormalBack(0.0f, 0.0f, 1.0f, -0.1f);
	CVector4 planeNormalLeft(1, 0, 0, -0.1f);
	CVector4 planeNormalRight(-1, 0, 0, side -0.1f);
	CVector4 planeNormalDown(0, 1, 0, -0.1f);
	CVector4 planeNormalUp(0, -1, 0, side -0.1f);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	drawBackWall();
	drawLeftWall();
	drawRightWall();
	drawDownWall();
	drawUpWall();

	drawShadow(planeNormalRight, lightPos, torus);
	drawShadow(planeNormalLeft, lightPos, torus);
	drawShadow(planeNormalBack, lightPos, torus);
	drawShadow(planeNormalUp, lightPos, torus);
	drawShadow(planeNormalDown, lightPos,  torus);

	drawShadow(planeNormalRight, lightPos, sphere);
	drawShadow(planeNormalLeft, lightPos, sphere);
	drawShadow(planeNormalBack, lightPos, sphere);
	drawShadow(planeNormalUp, lightPos, sphere);
	drawShadow(planeNormalDown, lightPos, sphere);

	drawShadow(planeNormalRight, lightPos, cone);
	drawShadow(planeNormalLeft, lightPos, cone);
	drawShadow(planeNormalBack, lightPos, cone);
	drawShadow(planeNormalUp, lightPos, cone);
	drawShadow(planeNormalDown, lightPos, cone);


	cone.Draw(false);
	torus.Draw(false);
	//glEnable(GL_TEXTURE_2D);
	sphere.Draw(false);
	//glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	{
		const int length = 100;
		glVertex3f(0, -5, 0);
		glVertex3f(length, -5, 0);
		glVertex3f(length, 0, 0);
		glVertex3f(0, 0, 0);
	}
	glEnd();
	

	glPushMatrix();
	glTranslatef(lightPos.x, lightPos.y, lightPos.z);
	gluSphere(sphereLight0, 3, 10, 10);
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	glFinish();
}
void updateLight1(int value)
{
	static short direction = 1;
	if (isRotating1)
	{
		lightPos.x += direction*0.5f;
		lightPos.y += direction*0.1f;
		if (lightPos.x < 5)
		{
			direction = 1;
		}
		if (lightPos.x > 50)
		{
			direction = -1;
		}
		glutPostRedisplay();
		glutTimerFunc(25, updateLight1, 0);
	}
}


void processSpecialKeys(int key, int xx, int yy) {
	float fraction = 5.0f;
	const float angle_speed = 0.1f;
	switch (key) {
	case GLUT_KEY_F1:
		angleY -= angle_speed;
		ly = sin(angleY);
		break;
	case GLUT_KEY_F2:
		break;
	case GLUT_KEY_LEFT:
		angle -= angle_speed;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += angle_speed;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		y += ly * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		y -= ly * fraction;
		break;
	case GLUT_KEY_F3:
		lightPos.x += 1;
		break;
	case GLUT_KEY_F4:
		lightPos.x -= 1;
		break;
	case GLUT_KEY_F5:
		lightPos.z += 1;
		break;
	case GLUT_KEY_F6:
		lightPos.z -= 1;
		break;
	case GLUT_KEY_F7:
		lightPos.y += 1;
		break;
	case GLUT_KEY_F8:
		lightPos.y -= 1;
		break;

	}
}
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
	if (key == 50) // '2' key
	{
		if (isRotating1)
		{
			isRotating1 = false;
		}
		else
		{
			isRotating1 = true;
			glutTimerFunc(25, updateLight1, 0);
		}
	}
	}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow(windowName);

	init();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	//glutTimerFunc(25, update, 0);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}