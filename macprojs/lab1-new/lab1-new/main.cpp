
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <stdlib.h>
#include <stdio.h>

#define stripeImageWidth 32
GLubyte stripeImage[4*stripeImageWidth];

static GLuint texName;

void makeStripeImage(void)
{
    int j;
    
    for (j = 0; j < stripeImageWidth; j++) {
        stripeImage[4*j] = (GLubyte) ((j<=4) ? 255 : 0);
        stripeImage[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
        stripeImage[4*j+2] = (GLubyte) 0;
        stripeImage[4*j+3] = (GLubyte) 255;
    }
}

/*  planes for texture coordinate generation  */
static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

void drawCube();
void drawSphere();


void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    //    glShadeModel(GL_SMOOTH);
    
    makeStripeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_1D, texName);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
    glTexGenfv(GL_S, currentPlane, currentCoeff);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_1D);
    glEnable(GL_CULL_FACE);
    //    glEnable(GL_LIGHTING);
    //    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix ();
//    glRotatef(45.0, 0.0, 0.0, 1.0);
    glEnable(GL_TEXTURE_1D);
    glBindTexture(GL_TEXTURE_1D, texName);
    
    //    glutWireTorus(0.5, 0.5, 10, 10);
    //    glutSolidTorus(2, 2, 4, 5);
    //    glutSolidTeapot(2.0);
    //    glutSolidOctahedron();
    //    glutSolidSphere(2, 10, 10);
    glutSolidTorus(0.1, 0.5, 10, 10);
    glDisable(GL_TEXTURE_1D);
    glPopMatrix ();
    glutSolidSphere(3, 10, 11);
    
    
    glPushMatrix();
    glColor3f(1, 0, 1);
//    glWireOctahedron();
    glutWireTeapot(0.4);
    glPopMatrix();
    
    
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    //    glutInitWindowPosition(100, 100);
    glutCreateWindow (argv[0]);
    init();
    
//    GLuint ss = loadTexture("texture.bmp");
    
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


//void drawSphere()
//{
////    glMaterialfv(GL_FRONT, GL_AMBIENT, sphereAmb);
////    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sphereDif);
////    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
////    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sphereSpecular);
//
//    glPushMatrix();
//
//    GLUquadricObj * sphere = gluNewQuadric();
//
//    gluQuadricNormals(sphere, GLU_SMOOTH);
//    gluQuadricTexture(sphere, GL_TRUE);
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, sphereTex);
//
////    glTranslatef(0.0f, sizeVal + 0.2f, 0.0f);
////    gluSphere(sphere, sizeVal, levels, levels);
//
//    glDisable(GL_TEXTURE_2D);
//
//    glPopMatrix();
//}
//
//void drawCube()
//{
//    // Opacity
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    glMaterialfv(GL_FRONT, GL_AMBIENT, cubeAmb);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cubeDif);
//
//    glColor4f(0.0f, 0.0f, 0.0f, 0.2f); // for shadows - if DEPTH_TEST disabled
//
//    glPushMatrix();
//
//    glTranslatef(0.0f, sizeVal + 0.2f, 0.0f);
//
//    glutSolidCube(sizeVal * 2 + 0.3);
//
//    glPopMatrix();
//}
//
//
