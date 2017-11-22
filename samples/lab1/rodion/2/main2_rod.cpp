#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI_ 3.14159265358979323846

GLuint draw;
double torusWidth = 0.075;
double torusHeight = 0.075;

/* Draw a torus */
static void torus(int numc, int numt, double w, double h) {

	int i, j, k;
	double s, t, x, y, z, twopi;

	twopi = 2 * PI_;
	for (i = 0; i < numc; i++) {

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= numt; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (1 + w*cos(s*twopi / numc))*cos(t*twopi / numt);
				y = (1 + w*cos(s*twopi / numc))*sin(t*twopi / numt);
				z = h*sin(s*twopi / numc);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}

}

/* Draw a sphere */
static void sphere(double r) {

	glutSolidSphere(r, 16, 5);

}

/* Create display list with Torus and initialize state */
static void init(void) {

	draw = glGenLists(1);
	glNewList(draw, GL_COMPILE);
	torus(6, 16, torusWidth, torusHeight);
	glEndList();

	glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

}

/* Clear window and draw torus */
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glCallList(draw);
	glFlush();

}

/* Handle window resize */
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

}

/* Rotate about x-axis when "x" typed; rotate about y-axis
when "y" typed; "i" returns torus to original view */
void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'x':
	case 'X':
		glRotatef(5.0, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		glRotatef(5.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case 'i':
	case 'I':
		glLoadIdentity();
		gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 'f':
	case 'F':
		if (torusWidth < 1.14 || torusHeight < 1.84) {
			torusWidth += 0.1;
			torusHeight += 0.17;
			glNewList(draw, GL_COMPILE);
			torus(6, 16, torusWidth, torusHeight);
			glEndList();
			glutPostRedisplay();
		}
		else {
			glNewList(draw, GL_COMPILE);
			sphere(2.19);
			glEndList();
			glutPostRedisplay();
		}
		break;
	case 'g':
	case 'G':
		if (torusWidth > 0.01 || torusHeight > 0.01) {
			glNewList(draw, GL_COMPILE);
			torus(6, 16, torusWidth, torusHeight);
			glEndList();
			torusWidth -= 0.2;
			torusHeight -= 0.34;
			glutPostRedisplay();
		}
		break;
	case 27:
		exit(0);
		break;
	}

}

int main(int argc, char **argv) {

	glutInitWindowSize(1600, 900);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}
