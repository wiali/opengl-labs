
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

void wireCylinder(float r, float h, int nsides, int nlongs) {
    glColor3f(1.f, 1.f, 0.f);
    
    float x = 0.f;
    float y = 0.f;
    const float FULL_ANGLE = 360.f;
    float angle_stepsize = FULL_ANGLE / nsides;
    float h_stepsize = h / nlongs;
    
    for (int i = 0; i < nlongs; i++) {
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < nsides; j++) {
            x = r * cos(j * angle_stepsize);
            y = r * sin(j * angle_stepsize);
            
            glVertex3f(y, i * h_stepsize, x);
        }
        glEnd();
    }
}

void wireCylinder2(float r, float h, float ang_step) {
    
    glColor3d(1.f, 1.f, 0.f);
    glBegin(GL_LINES);
    float x = 0.f;
    float y = 0.f;
    float angle = 0.f;
    float angle_stepsize = angle_stepsize;
    
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

void wireSphere(float r) {
    
    glutWireSphere(r,8,8);
}

void drawAxis() {
    // red OX
    glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_LINES);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(1.f, 0.f, 0.f);
    glEnd();
    
    // green OY
    glColor3f(0.f, 1.f, 0.f);
    glBegin(GL_LINES);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 1.f, 0.f);
    glEnd();
    
    // blue OZ
    glColor3f(0.f, 0.f, 1.f);
    glBegin(GL_LINES);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 1.f);
    glEnd();
}

void specialKeys(int key, int x, int y) {
    
    if (key == GLUT_KEY_RIGHT)
        rotate_y -= 5;
    
    else if (key == GLUT_KEY_LEFT)
        rotate_y += 5;
    
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    
    else if (key == GLUT_KEY_F1)
        rotate_octahedron += 5;
    
    else if (key == GLUT_KEY_F2) {
        move_cube -= 0.1;
        move_octahedron += 0.1;
    }
    
    else if (key == GLUT_KEY_F3) {
        move_cube += 0.1;
        move_octahedron -= 0.1;
    }
    
    glutPostRedisplay();
    
}

void handleKeys() {
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    //    gluPerspective(
    //                   40.0, /* угол зрения в градусах */
    //                   (float)1, /* коэффициент сжатия окна */
    //                   1,100.0);
    
    //    gluLookAt(
    //              1.f, 1.f, 1.f, // eye position
    //              0.f, 0.f, 0.f,  // scene center
    //              0.f, 0.f, 1.f); // up vector (y)
    //
    glRotatef(rotate_octahedron, 1.0, 0.0, 0.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    //glScalef(0.5f, 0.5f, 0.5f);
    glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
    
    handleKeys();
    
    drawAxis();
    //    wireCylinder(0.5f, 1.f, 5, 5);
    //    glTranslatef(move_cube, 0.0, 0.0);
    wireCylinder2(0.5f, 1.f, 2.f);
    //    glTranslatef(move_octahedron, 0.f, 0.f);
    wireSphere(0.5f);
    
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);
    //glewInit();
    glutInitDisplayMode(/*GLUT_DOUBLE | */GLUT_RGBA /*| GLUT_DEPTH*/);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Cube + Octahedron");
    // glEnable(GL_DEPTH_TEST);
    
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    
    glutMainLoop();
    
    return 0;
}
