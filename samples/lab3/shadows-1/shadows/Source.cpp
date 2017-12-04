#include "CMatrix.hpp"

#include <GL/glut.h>
#include <stdexcept>
#include <cstdio>

/* Main glut functions */

void display();
void usualKey(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void idle();

/* Init functions */

void setLight();
void turnLightOff();
GLuint loadTexture(const char * filename);

/* Figure drawing */

void drawRoom();
void drawSphere();
void drawCube();
void drawCylinder();

/* Data */

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

GLfloat angleX = 0.0f, angleY = 0.0f;
GLfloat sizeVal = 0.2f;
GLfloat offset = 0.1f;
GLfloat rotStep = 1.0f;
GLfloat lightStep = 0.1f;
GLuint levels = 40;

GLfloat lightAmbient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };

CMatrix4x4 shadowMatrix;
CVector4 planeNormal(0.0f, 1.0f, 0.0f, 0.0f);
CVector4 lightPos(0.0, 2.0, -3.0, 0.0);

CMatrix4x4 shadowMatrix2;
CVector4 planeNormal2(0.0f, 0.0f, -1.0f, 0.0f);
CVector4 lightPos2(0.0, 2.0, -1.0, 0.0);

/* Materials */

float sphereDif[] = { 1.0f, 1.0f, 1.0f };
float sphereAmb[] = { 0.4f, 0.4f, 0.4f };
float sphereSpecular[] = { 1.0f, 1.0f, 1.0f };
float sphereShininess[] = { 100.0f, 100.0f, 100.0f };
GLuint sphereTex = 0;

float cubeDif[] = { 1.0f, 0.3f, 0.3f, 0.2f };
float cubeAmb[] = { 0.4f, 0.4f, 0.4f };

float cylDif[] = { 0.2f, 0.8f, 0.2f, 0.2f }; // with opacity
float cylAmb[] = { 0.4f, 0.4f, 0.4f };

float roomDif[] = { 0.5f, 0.5f, 0.5f };
float roomAmb[] = { 1.0f, 1.0f, 1.0f };

/* Implementation */

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2);
	glutCreateWindow("Shadows");

	glutDisplayFunc(display);
	glutKeyboardFunc(usualKey);
	glutSpecialFunc(specialKey);
	glutIdleFunc(idle);

	sphereTex = loadTexture("img/texture.bmp");

	glutMainLoop();

	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

	/* Enable rotation using arrows */

	glRotatef(-angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(-angleY, 0.0f, 1.0f, 0.0f);

	/* Start creating the scene */

	setLight();

	drawRoom();

	/* Creating shadows */

	turnLightOff();

	shadowMatrix.CreateShadowMatrix(planeNormal, lightPos);
	glPushMatrix();
	glMultMatrixf(shadowMatrix.matrix);
	glColor3f(0.0f, 0.0f, 0.0f);

	drawSphere();
	drawCube();
	drawCylinder();

	glPopMatrix();

	/*shadowMatrix2.CreateShadowMatrix(planeNormal2, lightPos2);
	shadowMatrix2.matrix[0] = shadowMatrix.matrix[0];
	shadowMatrix2.matrix[5] = shadowMatrix.matrix[6];
	shadowMatrix2.matrix[9] = shadowMatrix.matrix[10];
	shadowMatrix2.matrix[13] = -1.4;
	shadowMatrix2.matrix[14] = 1.4;
	shadowMatrix2.matrix[15] = shadowMatrix.matrix[15];
	glPushMatrix();
	glMultMatrixf(shadowMatrix2.matrix);
	glColor3f(0.0f, 0.0f, 0.0f);

	drawSphere();
	drawCube();
	drawCylinder();

	glPopMatrix();*/

	setLight();

	/* Drawing original primitives */

	drawSphere();
	drawCube();
	drawCylinder();

	turnLightOff();

	glutSwapBuffers();
}

void usualKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '\033':
	{
		exit(0);
		break;
	}
	// Light rotations
	case 'w':
	{
		lightPos.z += lightStep;
		break;
	}
	case 's':
	{
		lightPos.z -= lightStep;
		break;
	}
	case 'a':
	{
		lightPos.x -= lightStep;
		break;
	}
	case 'd':
	{
		lightPos.x += lightStep;
		break;
	}
	// Light color
	case '1':
	{
		lightDiffuse[0] = !lightDiffuse[0];
		break;
	}
	case '2':
	{
		lightDiffuse[1] = !lightDiffuse[1];
		break;
	}
	case '3':
	{
		lightDiffuse[2] = !lightDiffuse[2];
		break;
	}
	default: break;
	}

	glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
	{
		angleY < 360 ? angleY += rotStep : angleY = 0;
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		angleY > 0 ? angleY -= rotStep : angleY = 360;
		break;
	}
	case GLUT_KEY_UP:
	{
		angleX < 360 ? angleX += rotStep : angleX = 0;
		break;
	}
	case GLUT_KEY_DOWN:
	{
		angleX > 0 ? angleX -= rotStep : angleX = 360;
		break;
	}
	default:
	{
		break;
	}
	}

	glutPostRedisplay();
}

void idle()
{
	// TODO: automatic changes are placed here
}

void setLight()
{
	glMatrixMode(GL_PROJECTION);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	GLfloat lightCoords[] = { lightPos.x, lightPos.y, lightPos.z, lightPos.w };
	glLightfv(GL_LIGHT0, GL_POSITION, lightCoords);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void turnLightOff()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
}

void drawRoom()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, roomAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, roomDif);

	GLfloat dim = 3 * sizeVal + 3 * offset;

	glPushMatrix();

	/* Draw floor */
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	//glVertex3f(dim, 0, dim - 0.2f);
	//glVertex3f(-dim, 0, dim - 0.2f);
	//glVertex3f(-dim, 0, -dim);
	//glVertex3f(dim, 0, -dim);
	glVertex3f(100.0f, 0, 100.0f - 0.2f);
	glVertex3f(-100.0f, 0, 100.0f - 0.2f);
	glVertex3f(-100.0f, 0, -100.0f);
	glVertex3f(100.0f, 0, -100.0f);
	glEnd();

	/* Draw back wall */
	/*glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glVertex3f(dim, dim, dim - 0.2f);
	glVertex3f(-dim, dim, dim - 0.2f);
	glVertex3f(-dim, 0, dim - 0.2f);
	glVertex3f(dim, 0, dim - 0.2f);
	glEnd();*/

	glPopMatrix();
}

void drawSphere()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, sphereAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sphereDif);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sphereSpecular);

	glPushMatrix();

	GLUquadricObj * sphere = gluNewQuadric();

	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(sphere, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sphereTex);

	glTranslatef(0.0f, sizeVal + 0.2f, 0.0f);
	gluSphere(sphere, sizeVal, levels, levels);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void drawCube()
{
	// Opacity
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMaterialfv(GL_FRONT, GL_AMBIENT, cubeAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cubeDif);

	glColor4f(0.0f, 0.0f, 0.0f, 0.2f); // for shadows - if DEPTH_TEST disabled

	glPushMatrix();

	glTranslatef(0.0f, sizeVal + 0.2f, 0.0f);

	glutSolidCube(sizeVal * 2 + 0.3);

	glPopMatrix();
}

void drawCylinder()
{
	// Opacity
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMaterialfv(GL_FRONT, GL_AMBIENT, cylAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cylDif);

	glColor4f(0.0f, 0.0f, 0.0f, 0.2f); // for shadows - if DEPTH_TEST disabled

	glPushMatrix();

	GLUquadricObj * cylinder = gluNewQuadric();

	glTranslatef(sizeVal * 2 + offset + 50.0f, sizeVal + 50.0f, -sizeVal);

	gluCylinder(cylinder,
		sizeVal, sizeVal,
		2 * sizeVal,
		levels, levels);

	glPopMatrix();

	glDisable(GL_BLEND);
}

GLuint loadTexture(const char * filename)
{
	if (!filename)
	{
		throw std::invalid_argument("Empty filename");
	}

	FILE * image = fopen(filename, "rb");
	if (!image)
	{
		throw std::invalid_argument("Wrong texture filename");
	}

	unsigned char header[54]; // header of the BMP file

	if (fread(header, 1, 54, image) != 54)
	{
		throw std::runtime_error("Wrong header of texture file");
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		throw std::runtime_error("Incorrect BMP texture file");
	}

	// Reading header

	int dataPos = *(int *) & (header[0x0A]); // offset for data
	int imageSize = *(int *) & (header[0x22]); // byte size of image
	int width = *(int *) & (header[0x12]);
	int height = *(int *) & (header[0x16]);

	if (imageSize == 0)
	{
		imageSize = width * height * 3; // 3 - for RGB
	}
	if (dataPos == 0)
	{
		dataPos = 54; // straight after header
	}

	unsigned char * data = new unsigned char[imageSize];
	fread(data, 1, imageSize, image);
	fclose(image);

	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return texId;
}
