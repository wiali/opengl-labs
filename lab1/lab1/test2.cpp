#include <stdio.h>
#include <GL/glut.h>


static GLfloat spin = 0.0;
static GLfloat spin_speed = 1.0;
float spin_x = 0;
float spin_y = 1;
float spin_z = 0;
float translate_x = 0.0;
float translate_y = 0.0;
float translate_z = -30.0;

//------- custom functions starts -------
void setSpin(float x, float y, float z)
{
    spin_x = x;
    spin_y = y;
    spin_z = z;
}
void reset()
{
    spin_x = 0;
    spin_y = 1;
    spin_z = 0;
    translate_x = 0.0;
    translate_y = 0.0;
    translate_z = -30.0;
}
//------- custom functions ends -------
void reshape(int w,int h)
{
    glViewport(0,0, (GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, (GLfloat)w/(GLfloat)h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void spinDisplay(void)
{
    spin=spin+spin_speed;
    if(spin>360.0)
    {
        spin=spin-360.0;
    }
    glutPostRedisplay();
}
void spinDisplayReverse(void)
{
    spin=spin-spin_speed;
    if(spin<360.0)
    {
        spin=spin+360.0;
    }
    glutPostRedisplay();
}
void mouse(int button,int state,int x,int y)
{

    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state==GLUT_DOWN)
            glutIdleFunc(spinDisplay);
        break;
    case GLUT_MIDDLE_BUTTON:
        if(state==GLUT_DOWN)
        {
            glutIdleFunc(NULL);
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if(state==GLUT_DOWN)
            glutIdleFunc(spinDisplayReverse);
        break;
    default:
        break;
    }
}
void keyboard(unsigned char key, int x, int y)
{
    //-------- spin --------
    if(key=='x')
    {
        setSpin(1.0,0.0,0.0);
        glutPostRedisplay();
    }
    else if(key=='y')
    {
        setSpin(0.0,1.0,0.0);
        glutPostRedisplay();
    }
    else if(key=='z')
    {
        setSpin(0.0,0.0,1.0);
        glutPostRedisplay();
    }
    else if(key=='a')
    {
        setSpin(1.0,1.0,1.0);
        glutPostRedisplay();
    }
    //-------- spin --------
    //-------- zoom --------
    else if(key=='i')
    {
        translate_z++;
        glutPostRedisplay();
    }
    else if(key=='o')
    {
        translate_z--;
        glutPostRedisplay();
    }
    //-------- zoom --------
    //-------- reset -------
    else if(key=='r')
    {
        reset();
        glutPostRedisplay();
    }
    //-------- reset -------
}

// assuming work-window width=50unit, height=25unit;
void init2()
{
    glClearColor(0,0,0,0);
    glShadeModel(GL_SMOOTH); // Enable Smooth Shading
    glClearDepth(1.0f); // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
}


void drawFan()
{
    glTranslatef(translate_x, translate_y, translate_z);

    glRotatef(spin,spin_x,spin_y,spin_z);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(0, 0);
    glVertex2i(-2, 5);
    glVertex2i(2, 5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(0, 0);
    glVertex2i(5, 2);
    glVertex2i(5, -2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(0, 0);
    glVertex2i(-2, -5);
    glVertex2i(2, -5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(0, 0);
    glVertex2i(-5, 2);
    glVertex2i(-5, -2);
    glEnd();
}

void drawFanStand()
{
    //glTranslatef(translate_x, translate_y, translate_z);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(-1, 0);
    glVertex2i(1, 0);
    glVertex2i(1, -10);
    glVertex2i(-1, -10);
    glVertex2i(-1, 0);
    glEnd();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //******************************************//
    //------- custom code starts -------

    drawFan();
    drawFanStand();

    //------- custom code ends -------
    //******************************************//
    glutSwapBuffers();
}

int main3(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Keyboard and Mouse Interaction");
    printf("ddddd");

    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);


    init2();
    glutMainLoop();

    return 0;
}
