#include <stdlib.h>
#include <GL/glut.h>

double rotate_y = 0;
double rotate_x = 0;

double rotate_octahedron = 0;
double move_cube = 0;
double move_octahedron = 0;

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);

    // left, right, up, down
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // cube (f2, f3)
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(move_cube, 0.0, 0.0);
    glutWireCube(1.0);

    // octahedron (f1)
    glColor3f(0.0, 1.0, 0.0);
    glRotatef(rotate_octahedron, 1.0, 0.0, 0.0);
    glTranslatef(1.0, 0.5, 0.5);
    glTranslatef(move_octahedron, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
    glutWireOctahedron();

    glFlush();
    glutSwapBuffers();

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

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);

    glutCreateWindow("Cube + Octahedron");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    glutMainLoop();

    return 0;

}
