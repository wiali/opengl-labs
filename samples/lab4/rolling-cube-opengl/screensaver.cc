#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "cstdio"
#include <math.h>

#include "screensaver.h"

#define PI 3.1415927
#define EARTH 1
#define SIZE 7

GLfloat yellow[4] = { 1, 1, 0, 0 };
float sphereRadius = 0.2;
//Tableau de vecteurs normaux aux faces pour calculer des produits vectoriels
float NFace [6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
//il y a trois modes pour tourner le cube, selon x, selon y, selon z
int steeringMode;
//angles utiles a la rotation du cube incrementes a tour de role.
float anglex, angley, anglez;

int texture[SIZE];

//velocity est la coordonnée de la boule (et de son vecteur vitesse)
point velocity;
//diff est ce qui est rajoute a ce vecteur a chaque reaffichage
point diff;



float degToRad (float deg){
	return  ((deg*PI)/180.0);
}//degToRad

float radToDeg (float rad){
	return ((rad*180.0)/PI);
}//radToDeg


//la librairie math.h prend en parametres des int
float absoluteValue (float v){
	return (v>0.0)? v : (v*(-1.0));
}//absoluteValue

void init(void) {
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	velocity.x = 0.0;
	velocity.y = 0.0;
	velocity.z = 0.0;
	diff.x = 0.01;
	diff.y = 0.005;
	diff.z = 0.015;
	steeringMode = 0;
	anglex = 0, angley = 0, anglez = 0;
  	LoadTexture("earth.bmp", &texture[EARTH]);
	CreatePlanet(sphereRadius, EARTH);
}//init

/* BMP RGB 24 bpp uniquement */
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;
    unsigned long i;
    unsigned short int planes;
    unsigned short int bpp;
    char temp;
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }//if
    fseek(file, 18, SEEK_CUR);
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }//if
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }//if
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }//if
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }//if
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }//if
    if ((bpp != 24) && (bpp!=32)) {
        printf("Bpp from %s is not 24 or 32: %u\n", filename, bpp);
        return 0;
    }//if
    size = image->sizeX * image->sizeY * (bpp/8);
    fseek(file, 24, SEEK_CUR);
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }//if
    if ((i = fread(image->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }//if
    for (i=0;i<size;i+=(bpp/8)) {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }//for
    return bpp;
}//imageload

void LoadTexture(char* filename, int* ident){
  Image im;
  int bpp;
  if(bpp=ImageLoad(filename, &im)) {
     glGenTextures(1, (GLuint*)ident);
     glBindTexture(GL_TEXTURE_2D, *ident);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     if(bpp==24)
       glTexImage2D(GL_TEXTURE_2D,0,3,
		    im.sizeX,im.sizeY,
		    0,GL_RGB,GL_UNSIGNED_BYTE,im.data);
     else if(bpp==32)
       glTexImage2D(GL_TEXTURE_2D,0,4,
		    im.sizeX,im.sizeY,
		    0,GL_RGBA,GL_UNSIGNED_BYTE,im.data);
   }//if
 }//loadtexture

void CreatePlanet(float radius, int ident) {
  GLfloat Black[4] = {0.0, 0.5, 0.7, 1.0};
  GLfloat ambient[] = { 4.0, 4.0, 4.0, 0.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
GLUquadricObj* sph1 = gluNewQuadric();
  glNewList(ident,GL_COMPILE);
  glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Black);
  glMaterialfv(GL_FRONT, GL_EMISSION, ambient);
  glMaterialf(GL_FRONT,GL_SHININESS,0.3);
  gluQuadricDrawStyle(sph1,GLU_FILL);
  gluQuadricNormals(sph1,GLU_SMOOTH);
  gluQuadricTexture(sph1,GL_TRUE);
  gluSphere(sph1,radius,20,20);
  glEndList();
}//createPlanet

void display_earth() {
 glPushMatrix();
//pour faire tourner la boule sur elle même dans tous les sens
  glRotatef(-53,0.0,0.0,1.0);
  glRotatef(-75,1.0,0.0,0.0);
  glRotatef(-90,0.0,0.0,1.0);
	glTranslatef (velocity.x, velocity.y, velocity.z);
  glBindTexture(GL_TEXTURE_2D, texture[EARTH]);
    glCallList(EARTH);
  glPopMatrix();
}//display_earth

void display(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	cubeRotation();
	glPushMatrix ();
	glRotatef(anglex,1.0,0.0,0.0);
	glRotatef(angley,0.0,1.0,0.0);
	glRotatef(anglez,0.0,0.0,1.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glutWireCube (2.0);
   	glPopMatrix();
	glFlush();
 	display_earth();
 	glFlush();
	glutSwapBuffers();
	//afterfirstdisplay :
	sphereMoving();
}//display


void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 15.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (-2.0, -4.0, -4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}//reshape

void sphereMoving () {
	//chaque instant la translation est plus grande selon
	//des proportions fixees jusqu'au moment ou la balle rebondit
	velocity.x += diff.x;
	velocity.y += diff.y;
	velocity.z += diff.z;
	//pour renvoyer la sphere en sens inverse
	if (absoluteValue(velocity.x) + sphereRadius >= 1.0)
		diff.x *= (-1.0);
	if (absoluteValue(velocity.y) + sphereRadius >= 1.0)
		diff.y *= (-1.0);
	if (absoluteValue(velocity.z) + sphereRadius >= 1.0)
		diff.z *= (-1.0);
}//sphereMoving

void cubeRotation() {
	switch (steeringMode) {
	case 0 : if (anglex < 90) anglex++;
		else {
			steeringMode++;
			anglex = 0;
		}//else
		break;
	case 1 : if (angley < 90) angley++;
		else {
			steeringMode++;
			angley = 0;
		}//else
		break;
	default : if (anglez < 90) anglez++;
		else {
			steeringMode-=2;
			anglez = 0;
		}//else
		break;
	}//switch
}//cubeRotation

void idleFunction(void){
         glutPostRedisplay();
}//idleFunction
