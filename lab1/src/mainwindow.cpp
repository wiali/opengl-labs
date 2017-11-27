//#include "mainwindow.h"
//
//#include <stdio.h>
//#include <GL/glut.h>
//#include <GL/freeglut.h>
//#include <cmath>
//
//float MainWindow::_xrot = 0;
//float MainWindow::_yrot = 0;
//
//MainWindow::MainWindow(int argc, char *argv[])
//{
//    // general
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA);
//    glutInitWindowSize(800, 800);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("Lab1");
//}
//
//void MainWindow::init()
//{
//    _xrot = 0;
//    _yrot = 0;
//
//    // logic
//    glutDisplayFunc(display);
//    glutSpecialFunc(handleKeyboard);
//    glutReshapeFunc(resize);
//
//    //params
//    //    glEnable(GL_DEPTH_TEST);
//    //    glEnable(GL_LIGHT0); // Включение нулевого источника света
//
//    // loop
//    glutMainLoop();
//}
//
//void MainWindow::drawCylinder()
//{
//    /*
//    glBegin(GL_LINE_LOOP);
////        glScalef(0.01, 0.01, 0.01);
//        glVertex3i(0, -0, 0);
////        glVertex3f( 0.5f, -0.5f, 0.5f);
////        glVertex3f( 0.5f, 0.5f, 0.5f);
//        glVertex3i(1, 1, 0);
//    glEnd();
//
//    glBegin(GL_LINE_LOOP);
//        glVertex3f(-0.5f, -0.5f, -0.5f);
//        glVertex3f(-0.5f, 0.5f, -0.5f);
//        glVertex3f( 0.5f, 0.5f, -0.5f);
//        glVertex3f( 0.5f, -0.5f, -0.5f);
//    glEnd();
//
//    glBegin(GL_LINE_LOOP);
//        glVertex3f(-0.5f, -0.5f, 0.5f);
//        glVertex3f(-0.5f, 0.5f, 0.5f);
//        glVertex3f(-0.5f, 0.5f, -0.5f);
//        glVertex3f(-0.5f, -0.5f, -0.5f);
//    glEnd();
//
//    glBegin(GL_LINE_LOOP);
//        glVertex3f( 0.5f, -0.5f, -0.5f);
//        glVertex3f( 0.5f, 0.5f, -0.5f);
//        glVertex3f( 0.5f, 0.5f, 0.5f);
//        glVertex3f( 0.5f, -0.5f, 0.5f);
//    glEnd();
//
//    glBegin(GL_LINE_LOOP);
//        glVertex3f(-0.5f, 0.5f, 0.5f);
//        glVertex3f( 0.5f, 0.5f, 0.5f);
//        glVertex3f( 0.5f, 0.5f, -0.5f);
//        glVertex3f(-0.5f, 0.5f, -0.5f);
//    glEnd();
//
//    glBegin(GL_LINE_LOOP);
//        glVertex3f(-0.5f, -0.5f, 0.5f);
//        glVertex3f(-0.5f, -0.5f, -0.5f);
//        glVertex3f( 0.5f, -0.5f, -0.5f);
//        glVertex3f( 0.5f, -0.5f, 0.5f);
//    glEnd();
//*/
//    /*
//    glTranslated(0, 0, 0);
//    glColor3d(10, 1, 1);
//    glutWireCylinder(1, 3, 10, 1);
//*/
//
//    GLfloat x              = 0.0;
//    GLfloat y              = 0.0;
//    GLfloat angle          = 0.0;
//    GLfloat angle_stepsize = 0.5;
//
//    /** Draw the tube */
//    glColor3d(10, 1, 1);
//    glBegin(GL_LINES);
//    angle = 0.0;
//    float PI = 3.14;
//    GLfloat radius = 1;
//    GLfloat height = 3;
//    while( angle < 2*PI ) {
//        x = radius * cos(angle);
//        y = radius * sin(angle);
//        glVertex3f(x, y , height);
//        glVertex3f(x, y , 0.0);
//        angle = angle + angle_stepsize;
//    }
//    glVertex3f(radius, 0.0, height);
//    glVertex3f(radius, 0.0, 0.0);
//    glEnd();
//
//    /** Draw the circle on top of cylinder */
//    glColor3d(10, 1, 1);
//    glBegin(GL_LINE_LOOP);
//    angle = 0.0;
//    while( angle < 2*PI ) {
//        x = radius * cos(angle);
//        y = radius * sin(angle);
//        glVertex3f(x, y , height);
//        angle = angle + angle_stepsize;
//    }
//    glVertex3f(radius, 0.0, height);
//    glEnd();
//}
//
//void MainWindow::drawSphere()
//{
//    double r = 1;
//    int lats = 10;
//    int longs = 10;
//    int i, j;
//    for(i = 0; i <= lats; i++) {
//        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
//        double z0  = sin(lat0);
//        double zr0 =  cos(lat0);
//
//        double lat1 = M_PI * (-0.5 + (double) i / lats);
//        double z1 = sin(lat1);
//        double zr1 = cos(lat1);
//
//        glBegin(GL_LINE_LOOP);
//        for(j = 0; j <= longs; j++) {
//            double lng = 2 * M_PI * (double) (j - 1) / longs;
//            double x = cos(lng);
//            double y = sin(lng);
//
//            glNormal3f(x * zr0, y * zr0, z0);
//            glVertex3f(x * zr0, y * zr0, z0);
//            glNormal3f(x * zr1, y * zr1, z1);
//            glVertex3f(x * zr1, y * zr1, z1);
//        }
//        glEnd();
//    }
//}
//
//void MainWindow::torus()
//{
//    int numc = 3;
//    int numt = 3;
//
//    int i, j, k;
//    double s, t, x, y, z, twopi;
//    double PI = 3.14;
//    twopi = 2 * PI;
//    for (i = 0; i < numc; i++) {
//        glBegin(GL_LINE_LOOP);
//        for (j = 0; j <= numt; j++) {
//            for (k = 1; k >= 0; k--) {
//                s = (i + k) % numc + 0.5;
//                t = j % numt;
//
//                x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
//                y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
//                z = .1 * sin(s * twopi / numc);
//                glVertex3f(x, y, z);
//            }
//        }
//        glEnd();
//    }
//
//}
//
//void MainWindow::display()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//
//    gluLookAt(
//                0.0f, 0.0f, 20.0f,
//                0.0f, 0.0f, 0.0f,
//                1.0f, 1.0f, 1.0f);
//
//    glRotatef(_xrot, 1.0f, 0.0f, 0.0f);
//    glRotatef(_yrot, 0.0f, 1.0f, 0.0f);
//
//    drawCylinder();
////    drawSphere();
//    // torus();
//
//    glFlush();
//    glutSwapBuffers();
//}
//
//void MainWindow::resize(int w, int h)
//{
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    glViewport(0, 0, w, h);
//
//    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//void MainWindow::handleKeyboard(int key, int x, int y)
//{
//    switch(key)
//    {
//    case GLUT_KEY_UP:
//        printf("up\n");
//        _xrot+=3.0f;
//        break;
//    case GLUT_KEY_DOWN:
//        printf("down\n");
//        _xrot-=3.0f;
//        break;
//    case GLUT_KEY_LEFT:
//        printf("left\n");
//        _yrot-=3.0f;
//        break;
//    case GLUT_KEY_RIGHT:
//        printf("right\n");
//        _yrot+=3.0f;
//        break;
//    }
//    glutPostRedisplay();
//}

