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


void drawOctahedron();
//void drawTorus(double r = 0.07, double c = 0.0, int rSeg = 16, int cSeg = 8);
void drawTorus(double r = 0.07, double c = 0.2, int rSeg = 16, int cSeg = 8);

void doTask2()
{
    glColor3f(1.f, 1.f, 0.f);
    drawOctahedron();
    drawTorus();
}

void drawOctahedron()
{
    glutWireOctahedron();
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
