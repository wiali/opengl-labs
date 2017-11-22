#include <GL/glut.h>
#include <stdlib.h>

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
static int year = 0, day = 0;
GLfloat jaune[4] = { 1, 1, 0, 0 };
GLfloat bleu[4] = { 0, 0, 1, 0 };

void init(void) 
{
 //  glClearColor (0.0, 0.0, 0.0, 0.0);
  // glShadeModel (GL_FLAT);     
glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glMaterialf(GL_FRONT, GL_SHININESS, 25.0);

  GLfloat light_ambient[] = { 4.0, 4.0, 4.0, 0.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 0.0 };
/*	light_position is NOT default value	*/
    GLfloat light_position[] = { 0, 0, -4, 0.0 };

    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
   glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   //glColor3f (1.0, 1.0, 1.0);
// glColor3b(200, 12, 12);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, jaune);
   glPushMatrix();
  // glutWireSphere(1.0, 20, 16);   /* draw sun */   
   glRotatef ((GLfloat) year, 0.3, 0.1, 0.3);
   glRotatef ((GLfloat) year, 0.3, 0.3, 0.1);
 glutWireCube (2.0);
glFlush();
   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
 glTranslatef (0.8, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
  // glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
// glColor3b(0, 0, 255);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, bleu);
 glutSolidSphere (0.2, 10, 12);
glFlush();
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/* ARGSUSED1 */
void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         day = (day - 10) % 360;
         glutPostRedisplay();
         break;
      case 'y':
         year = (year + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         year = (year - 5) % 360;
         glutPostRedisplay();
         break;
	case 'a' :             
	/*	diffuseMaterial[1] += 0.1;
            if (diffuseMaterial[1] > 1.0)
               diffuseMaterial[1] = 0.0;
            glColor4fv(diffuseMaterial);*/
         year = (year + 5) % 360;
         day = (day + 10) % 360;
         glutPostRedisplay();
	break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 600); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
