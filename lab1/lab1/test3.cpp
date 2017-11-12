#include <GL/glut.h>
#include<stdbool.h>
#include<stdio.h>

float xrot = 0.0f;
float yrot = 0.0f;

void drawBox()
{

   glBegin(GL_LINE_LOOP);
       glVertex3f(-0.5f, -0.5f, 0.5f);
       glVertex3f( 0.5f, -0.5f, 0.5f);
       glVertex3f( 0.5f, 0.5f, 0.5f);
       glVertex3f(-0.5f, 0.5f, 0.5f);
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
}

bool init()
{
   glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glClearDepth(1.0f);

   return true;
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   gluLookAt(
   0.0f, 0.0f, 3.0f,
   0.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f);

   glRotatef(xrot, 1.0f, 0.0f, 0.0f);
   glRotatef(yrot, 0.0f, 1.0f, 0.0f);

   drawBox();

   glFlush();
   glutSwapBuffers();
}

void resize(int w, int h)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glViewport(0, 0, w, h);

   gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void specialKeyboard(int key, int x, int y)
{
   //printf("%d",key);
   switch(key)
   {
       case GLUT_KEY_UP:
           printf("up\n");
           xrot+=1.0f;
           break;
       case GLUT_KEY_DOWN:
           printf("down\n");
           xrot-=1.0f;
           break;
       case GLUT_KEY_LEFT:
           printf("left\n");
           yrot-=1.0f;
           break;
       case GLUT_KEY_RIGHT:
           printf("right\n");
           yrot+=1.0f;
           break;
   }
   glutPostRedisplay();

}


int main3113(int argc, char *argv[])
{
   glutInit(&argc, argv);

   glutInitWindowPosition(50, 50);
   glutInitWindowSize(500, 500);

   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

   glutCreateWindow("13 - Solid Shapes");

   glutDisplayFunc(display);
   glutSpecialFunc(specialKeyboard);
   glutReshapeFunc(resize);

   glutMainLoop();

   return 0;
}
