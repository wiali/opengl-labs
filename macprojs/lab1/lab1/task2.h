//
//  task2.h
//  lab1
//
//  Created by Roman on 04.12.2017.
//  Copyright © 2017 Roman. All rights reserved.
//

#ifndef task2_h
#define task2_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif
#ifdef __linux__
// macro for linux
#endif
#include <cmath>

//from main start

#define stripeImageWidth 32
GLubyte stripeImage[4*stripeImageWidth];

static GLuint texName;

void makeStripeImage(void)
{
    int j;
    
    for (j = 0; j < stripeImageWidth; j++) {
        stripeImage[4*j] = (GLubyte) ((j<=4) ? 255 : 0);
        stripeImage[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
        stripeImage[4*j+2] = (GLubyte) 0;
        stripeImage[4*j+3] = (GLubyte) 255;
    }
}

//from main finish




void drawOctahedron();
//void drawTorus(double r = 0.07, double c = 0.0, int rSeg = 16, int cSeg = 8);
void drawTorus(double r = 0.07, double c = 0.2, int rSeg = 16, int cSeg = 8);

void doTask2()
{
    glColor3f(1.f, 1.f, 0.f);
    drawOctahedron();
//    drawTorus();
}

void drawOctahedron()
{
//    glutWireOctahedron();
    
    
    glPushMatrix ();
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glBindTexture(GL_TEXTURE_1D, texName);
    
    //    glutWireTorus(0.5, 0.5, 10, 10);
    //    glutSolidTorus(2, 2, 4, 5);
        glutSolidTeapot(2.0);
    //    glutSolidOctahedron();
    //    glutSolidSphere(2, 10, 10);
//    glutSolidTorus(0.1, 0.5, 10, 10);
    glDisable(GL_TEXTURE_1D);
    glPopMatrix ();
    glutSolidSphere(3, 10, 11);
}

static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    //    glShadeModel(GL_SMOOTH);

    makeStripeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_1D, texName);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
    glTexGenfv(GL_S, currentPlane, currentCoeff);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_1D);
    glEnable(GL_CULL_FACE);
    //    glEnable(GL_LIGHTING);
    //    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
}


void drawTorus(double r, double c, int rSeg, int cSeg)
{
    const double TAU = 2 * M_PI;
    for (int i = 0; i < rSeg; i++) {
        //        glBegin(GL_QUAD_STRIP);
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j <= cSeg; j++) {
            for (int k = 0; k <= 1; k++) {
                double s = (i + k) % rSeg + 0.5;
                double t = j % (cSeg + 1);
                double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
                double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
                double z = r * sin(s * TAU / rSeg);
                double u = (i + k) / (float) rSeg;
                double v = t / (float) cSeg;
//                glTexCoord2d(u, v);
                glNormal3f(2 * x, 2 * y, 2 * z);
                glVertex3d(2 * x, 2 * y, 2 * z);
            }
        }
        glEnd();
    }
}

///*
// r = torus ring radius
// c = torus tube radius
// rSeg, cSeg = number of segments/detail
// */
//void drawTorus(double r = 0.07, double c = 0.0,
//               int rSeg = 16, int cSeg = 8,
//               int texture = 0)
//{
//    glFrontFace(GL_CW);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    const double PI = 3.1415926535897932384626433832795;
//    const double TAU = 2 * PI;
//    for (int i = 0; i < rSeg; i++) {
//        //        glBegin(GL_QUAD_STRIP);
//        glBegin(GL_LINE_LOOP);
//        for (int j = 0; j <= cSeg; j++) {
//            for (int k = 0; k <= 1; k++) {
//                double s = (i + k) % rSeg + 0.5;
//                double t = j % (cSeg + 1);
//                double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
//                double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
//                double z = r * sin(s * TAU / rSeg);
//                double u = (i + k) / (float) rSeg;
//                double v = t / (float) cSeg;
//                glTexCoord2d(u, v);
//                glNormal3f(2 * x, 2 * y, 2 * z);
//                glVertex3d(2 * x, 2 * y, 2 * z);
//            }
//        }
//        glEnd();
//    }
//    glFrontFace(GL_CCW);
//}
//

#endif /* task2_h */
