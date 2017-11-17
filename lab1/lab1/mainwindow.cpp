#include "mainwindow.h"

#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>

float MainWindow::_xrot = 0;
float MainWindow::_yrot = 0;

MainWindow::MainWindow(int argc, char *argv[])
{
    // general
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Lab1");
}

void MainWindow::init()
{
    _xrot = 0;
    _yrot = 0;

    // logic
    glutDisplayFunc(display);
    glutSpecialFunc(handleKeyboard);
    glutReshapeFunc(resize);

    //params
    //    glEnable(GL_DEPTH_TEST);
    //    glEnable(GL_LIGHT0); // Включение нулевого источника света

    // loop
    glutMainLoop();
}

void MainWindow::drawCylinder()
{
    /*
    glBegin(GL_LINE_LOOP);
//        glScalef(0.01, 0.01, 0.01);
        glVertex3i(0, -0, 0);
//        glVertex3f( 0.5f, -0.5f, 0.5f);
//        glVertex3f( 0.5f, 0.5f, 0.5f);
        glVertex3i(1, 1, 0);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f( 0.5f, 0.5f, -0.5f);
        glVertex3f( 0.5f, -0.5f, -0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f( 0.5f, -0.5f, -0.5f);
        glVertex3f( 0.5f, 0.5f, -0.5f);
        glVertex3f( 0.5f, 0.5f, 0.5f);
        glVertex3f( 0.5f, -0.5f, 0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f( 0.5f, 0.5f, 0.5f);
        glVertex3f( 0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f( 0.5f, -0.5f, -0.5f);
        glVertex3f( 0.5f, -0.5f, 0.5f);
    glEnd();
*/
    /*
    glTranslated(0, 0, 0);
    glColor3d(10, 1, 1);
    glutWireCylinder(1, 3, 10, 1);
*/

    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.5;

    /** Draw the tube */
    glColor3d(10, 1, 1);
    glBegin(GL_LINES);
    angle = 0.0;
    float PI = 3.14;
    GLfloat radius = 1;
    GLfloat height = 3;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        glVertex3f(x, y , 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3d(10, 1, 1);
    glBegin(GL_LINE_LOOP);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void MainWindow::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
                0.0f, 0.0f, 20.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f);

    glRotatef(_xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(_yrot, 0.0f, 1.0f, 0.0f);

    drawCylinder();

    glFlush();
    glutSwapBuffers();
}

void MainWindow::resize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MainWindow::handleKeyboard(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        printf("up\n");
        _xrot+=3.0f;
        break;
    case GLUT_KEY_DOWN:
        printf("down\n");
        _xrot-=3.0f;
        break;
    case GLUT_KEY_LEFT:
        printf("left\n");
        _yrot-=3.0f;
        break;
    case GLUT_KEY_RIGHT:
        printf("right\n");
        _yrot+=3.0f;
        break;
    }
    glutPostRedisplay();
}
