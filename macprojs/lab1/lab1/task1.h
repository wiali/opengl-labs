//
//  task1.h
//  lab1
//
//  Created by Roman on 04.12.2017.
//  Copyright © 2017 Roman. All rights reserved.
//

#ifndef task1_h
#define task1_h

#include "OpenGl/gl.h"
#include "GLUT/glut.h"
#include <cmath>

void drawCylinder(float r, float h);
void drawSphere(float r);

void doTask1() {
    drawCylinder(0.5, 1);
    drawSphere(0.5);
}

void drawCylinder(float r, float h) {
    glBegin(GL_LINES);
    float x = 0.f;
    float y = 0.f;
    float angle = 0.f;
    float angle_stepsize = 0.1;
    
    while (angle < 2 * M_PI) {
        x = r * cos(angle);
        y = r * sin(angle);
        glVertex3f(x, -h / 2, y);
        glVertex3f(x, h / 2, y );
        angle += angle_stepsize;
    }
    glVertex3f(r, -h / 2, 0.f);
    glVertex3f(r, h / 2, 0.f);
    glEnd();
    
    // top and bottom
    // FIXME circle
    glBegin(GL_LINE_LOOP);
    angle = 0.f;
    
    while (angle < 2 * M_PI) {
        x = r * cos(angle);
        y = r * sin(angle);
        glVertex3f(x, -h / 2, y);
        angle = angle + angle_stepsize;
    }
    glVertex3f(r, -h / 2, 0.f);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    angle = 0.f;
    
    while (angle < 2 * M_PI) {
        x = r * cos(angle);
        y = r * sin(angle);
        glVertex3f(x, h / 2, y);
        angle = angle + angle_stepsize;
    }
    glVertex3f(r, h / 2, 0.f);
    glEnd();
}

void drawSphere(float r) {
    glutWireSphere(r, 10, 10);
}

#endif /* task1_h */
