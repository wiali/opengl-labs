
#include <cstdio>
#include <cmath>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

#ifdef __linux__
// macro for linux
#endif


double rotate_y = 0;
double rotate_x = 0;

double rotate_octahedron = 0;
double move_cube = 0;
double move_octahedron = 0;


void wireCylinder(GLfloat r, GLfloat h) {
    
    //    OX, OY, OZ
    // red
    glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_LINES);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(1.f, 0.f, 0.f);
    glEnd();
    
    // green
    glColor3f(0.f, 1.f, 0.f);
    glBegin(GL_LINES);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.5f, 0.f);
    glEnd();
    
    // blue
    glColor3f(0.f, 0.f, 1.f);
    glBegin(GL_LINES);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 1.f);
    glEnd();
    
    //    cylinder
    glColor3d(1.f, 1.f, 0.f);
    glRotatef(75.f, 1.f, 0.f, 0.f);
    glBegin(GL_LINES);
    GLfloat x = 0.f;
    GLfloat y = 0.f;
    GLfloat angle = 0.f;
    GLfloat angle_stepsize = 0.5f;
    //
    while (angle < 2 * M_PI) {
        x = r * cos(angle);
        y = r * sin(angle);
        glVertex3f(x, y , -h / 2);
        glVertex3f(x, y , h / 2);
        angle += angle_stepsize;
    }
    glVertex3f(r, 0.f, -h / 2);
    glVertex3f(r, 0.f, h / 2);
    glEnd();
    
    /** Draw the circle on top of cylinder */
    glBegin(GL_LINE_LOOP);
    angle = 0.f;
    
    while (angle < 2 * M_PI) {
        x = r * cos(angle);
        y = r * sin(angle);
        glVertex3f(x, y, h / 2);
        angle = angle + angle_stepsize;
    }
    glVertex3f(r, 0.f, h / 2);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    angle = 0.f;
    
    while (angle < 2 * M_PI) {
        x = r * cos(angle);
        y = r * sin(angle);
        glVertex3f(x, y, -h / 2);
        angle = angle + angle_stepsize;
    }
    glVertex3f(r, 0.f, -h / 2);
    glEnd();
}

void wireSphere(float r) {
    
}

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glScalef(0.5f, 0.5f, 0.5f);
    //    glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
    //
    //    // left, right, up, down
    //    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    //    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    //    gluPerspective(
    //                   40.0, /* угол зрения в градусах */
    //                   (GLfloat)1, /* коэффициент сжатия окна */
    //                   1,100.0);
    
    //    gluLookAt(
    //              1.f, 1.f, 1.f, // eye position
    //              0.f, 0.f, 0.f,  // scene center
    //              0.f, 0.f, 1.f); // up vector (y)
    //
    wireCylinder(0.5f, 1.f);
    // glRotatef(0, 3.f, 0.f, 10.f);
    // glRotatef(0, 0.f, 3.f, 0.f);
    // glColor3f(1.f, 1.f, 1.f);
    // glTranslatef(10, 0.f, 10.f);
    
    // glLineWidth(2.5);
    // glColor3f(1.f, 0.f, 0.f);
    // glBegin(GL_LINES);
    // glVertex3f(0.f, 0.f, 0.f);
    // glVertex3f(15, 0, 0);
    // glEnd();
    
    //     glOrtho(-2.f, 2.f, -2.f, 2.f, 2.f, -2.f);
    
    //
    // // // left, right, up, down
    // glRotatef(0, 1.f, 0.f, 0.f);
    // glRotatef(0, 0.f, 1.f, 0.f);
    //
    //
    //
    // // cube (f2, f3)
    // glColor3f(1.f, 1.f, 1.f);
    // glTranslatef(0, 0.f, 0.f);
    // wireCylinder(1.f, 3.f);
    //
    // // // octahedron (f1)
    // glColor3f(0.f, 1.f, 0.f);
    // glRotatef(0, 1.f, 0.f, 0.f);
    // glTranslatef(1.f, 0.5, 0.5);
    // glTranslatef(0, 0.f, 0.f);
    // glScalef(0.5, 0.5, 0.5);
    // // glutWireOctahedron();
    
    glFlush();
    glutSwapBuffers();
    
}

// void specialKeys(int key, int x, int y) {
//
//     if (key == GLUT_KEY_RIGHT)
//         rotate_y -= 5;
//
//     else if (key == GLUT_KEY_LEFT)
//         rotate_y += 5;
//
//     else if (key == GLUT_KEY_UP)
//         rotate_x += 5;
//
//     else if (key == GLUT_KEY_DOWN)
//         rotate_x -= 5;
//
//     else if (key == GLUT_KEY_F1)
//         rotate_octahedron += 5;
//
//     else if (key == GLUT_KEY_F2) {
//         move_cube -= 0.1;
//         move_octahedron += 0.1;
//     }
//
//     else if (key == GLUT_KEY_F3) {
//         move_cube += 0.1;
//         move_octahedron -= 0.1;
//     }
//
//     glutPostRedisplay();
//
// }

int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);
    //glewInit();
    glutInitDisplayMode(/*GLUT_DOUBLE | */GLUT_RGBA /*| GLUT_DEPTH*/);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Cube + Octahedron");
    // glEnable(GL_DEPTH_TEST);
    
    glutDisplayFunc(display);
    // glutSpecialFunc(specialKeys);
    
    glutMainLoop();
    
    return 0;
}
