#include "mainwindow.h"

#include <stdio.h>
#include <GL/glut.h>

float MainWindow::_xrot = 0;
float MainWindow::_yrot = 0;

MainWindow::MainWindow(int argc, char *argv[])
{
    // general
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
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

}

void MainWindow::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
                0.0f, 0.0f, 3.0f,
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
        _xrot+=1.0f;
        break;
    case GLUT_KEY_DOWN:
        printf("down\n");
        _xrot-=1.0f;
        break;
    case GLUT_KEY_LEFT:
        printf("left\n");
        _yrot-=1.0f;
        break;
    case GLUT_KEY_RIGHT:
        printf("right\n");
        _yrot+=1.0f;
        break;
    }
    glutPostRedisplay();
}
