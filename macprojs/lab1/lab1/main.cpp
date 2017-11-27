
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

    // red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(30, 0, 0);
    glEnd();

    // green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0, 30, 0);
    glEnd();

    // blue
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0, 0, 30);
    glEnd();


    // // glColor3d(10, 1, 1);
    // glBegin(GL_LINES);
    // GLfloat x              = 0.0;
    // GLfloat y              = 0.0;
    // GLfloat angle          = 0.0;
    // GLfloat angle_stepsize = 0.5;
    //
    // while (angle < 2 * M_PI) {
    //     x = r * cos(angle);
    //     y = r * sin(angle);
    //     glVertex3f(x, y , h);
    //     glVertex3f(x, y , 0.0);
    //     angle += angle_stepsize;
    // }
    // glVertex3f(r, 0.0, h);
    // glVertex3f(r, 0.0, 0.0);
    // glEnd();
    //
    // /** Draw the circle on top of cylinder */
    // // glColor3d(10, 1, 1);
    // glBegin(GL_LINE_LOOP);
    // angle = 0.0;
    // while( angle < 2*M_PI ) {
    //     x = r * cos(angle);
    //     y = r * sin(angle);
    //     glVertex3f(x, y , h);
    //     angle = angle + angle_stepsize;
    // }
    // glVertex3f(r, 0.0, h);
    // glEnd();
}

void wireSphere(float r) {

}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // gluLookAt(
    //             0.0f, 0.0f, 20.0f,
    //             0.0f, 0.0f, 0.0f,
    //             0.0f, 1.0f, 0.0f);

    wireCylinder(1.f, 3.f);
    // glRotatef(0, 3.0, 0.0, 10.0);
    // glRotatef(0, 0.0, 3.0, 0.0);
    // glColor3f(1.0, 1.0, 1.0);
    // glTranslatef(10, 0.0, 10.0);

    // glLineWidth(2.5);
    // glColor3f(1.0, 0.0, 0.0);
    // glBegin(GL_LINES);
    // glVertex3f(0.0, 0.0, 0.0);
    // glVertex3f(15, 0, 0);
    // glEnd();

    // glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);


    // // gluLookAt(
    // //             0.0f, 0.0f, 20.0f,
    // //             0.0f, 0.0f, 0.0f,
    // //             1.0f, 1.0f, 1.0f);
    // glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
    //
    //
    // // // left, right, up, down
    // glRotatef(0, 1.0, 0.0, 0.0);
    // glRotatef(0, 0.0, 1.0, 0.0);
    //
    //
    //
    // // cube (f2, f3)
    // glColor3f(1.0, 1.0, 1.0);
    // glTranslatef(0, 0.0, 0.0);
    // wireCylinder(1.f, 3.f);
    //
    // // // octahedron (f1)
    // glColor3f(0.0, 1.0, 0.0);
    // glRotatef(0, 1.0, 0.0, 0.0);
    // glTranslatef(1.0, 0.5, 0.5);
    // glTranslatef(0, 0.0, 0.0);
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
