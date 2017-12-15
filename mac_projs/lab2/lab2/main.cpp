// #include "task1.h"
// #include "task2.h"
// #include "task3.h"
// #include "task4.h"
// #include "task5.h"
// #include "task6.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#ifdef __linux__
// macro for linux
#endif
#include <cstring>
#include <stdexcept>
#include <cmath>


static float positionX = 0.f;
static float positionY = 0.f;
static float positionZ = 0.f;
static float rotationX = 0.f;
static float rotationY = 0.f;
static float rotationZ = 0.f;
static const float dPosition = 0.1f;
static const float dRotation = 5.f;

static GLuint tex1 = 0;
static GLuint tex2 = 0;
static GLuint tex3 = 0;

void display();
void specialKeys(int key, int x, int y);
void drawAxis();
void handleSpecialKeys();
void initParams();

GLuint loadTexture(const char * filename);

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Lab1");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    
    
    initParams();


    glutMainLoop();
    
    return 0;
}


struct point
{
    double x, y, z;
};

int r = 10;
float fi = 0;
float z2 = -1;
float k = 1;

GLfloat mat_amb1[] = { 0.2, 0.2, 0.2, 1 };
GLfloat mat_dif1[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_spec1[] = { 1, 1, 1, 1 };
GLfloat mat_emi1[] = { 0, 0, 0, 1 };
GLfloat mat_shin1 = 128;

GLfloat mat_amb2[] = { 0.2, 0.2, 0.2, 0.6 };
GLfloat mat_dif2[] = { 0.8, 0.8, 0.8, 0.6 };
GLfloat mat_spec2[] = { 0, 0, 0, 0.6 };
GLfloat mat_emi2[] = { 0, 0, 0, 1 };
GLfloat mat_shin2 = 0;

GLfloat mat_amb3[] = { 0.2, 0.2, 0.2, 1 };
GLfloat mat_dif3[] = { 0.8, 0.8, 0.8, 1 };
GLfloat mat_spec3[] = { 0, 0, 0, 1 };
GLfloat mat_emi3[] = { 0, 0, 0, 1 };
GLfloat mat_shin3 = 0;

void part1()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    glLoadIdentity();
    
    float x = r*cos(fi);
    float y = r*sin(fi);
    
    GLfloat light1_diffuse[] = {0, 0.0, 1, 1.0};
    GLfloat light1_position[] = {x, y, 0, 1.0};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);
    
    GLfloat light2_diffuse[] = {1, 0, 0, 1.0};
    GLfloat light2_position[] = {z2, 0, -2.5, 1};
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.6);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.6);
    
    gluLookAt(0, 0, -6, 0, 0, 0, 0, 1, 0);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emi1);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shin1);
    
    glPushMatrix();
    glTranslated(0.5, 0.5, 2);
    glutSolidSphere(1, 10, 20);
    glPopMatrix();
    

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emi2);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shin2);
    
    glPushMatrix();
    glRotated(30, 0.0, 1.0, 0.0);
    glutSolidTetrahedron();
    glPopMatrix();

    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emi3);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shin3);
    
    glPushMatrix();
    glTranslated(-1.5, 0, -2.0);
    glRotated(-30, 0.0, 1.0, 0.0);
    glutSolidCube(1);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    
    fi = fi + 0.05;
    
    if (z2 < -1 || z2 > 3)
    {
        k *= -1;
    }
    
    z2 = z2 + k * 0.1;
    
    glutSwapBuffers();
}

void initParams()
{
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    
    glEnable(GL_TEXTURE_2D); // ?
    tex1 = loadTexture("tex1.bmp");
    tex2 = loadTexture("tex2.bmp");
    tex3 = loadTexture("tex3.bmp");
    
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display()
{
    part1();
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//
//    //glScalef(0.5f, 0.5f, 0.5f);
//    glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
//
//    handleSpecialKeys();
//    drawAxis();
//
//    // doTask2();
//
//    glFlush();
//    glutSwapBuffers();
}

void handleSpecialKeys()
{
    glRotatef(rotationX, 1.f, 0.f, 0.f);
    glRotatef(rotationY, 0.f, 1.f, 0.f);
    glRotatef(rotationZ, 0.f, 0.f, 1.f);
}

void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        rotationY -= dRotation;
    else if (key == GLUT_KEY_LEFT)
        rotationY += dRotation;
    else if (key == GLUT_KEY_UP)
        rotationX += dRotation;
    else if (key == GLUT_KEY_DOWN)
        rotationX -= dRotation;
    else if (key == GLUT_KEY_F1)
        rotationZ += dRotation;
    else if (key == GLUT_KEY_F2)
        rotationZ -= dRotation;
    else if (key == GLUT_KEY_F3)
        positionX += dPosition;
    else if (key == GLUT_KEY_F4)
        positionY += dPosition;

    glutPostRedisplay();
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


// read bmp
GLuint loadTexture(const char * filename)
{
    if (!filename)
    {
        throw std::invalid_argument("Empty filename");
    }

    FILE * image = fopen(filename, "rb");
    if (!image)
    {
        throw std::invalid_argument("Wrong texture filename");
    }

    unsigned char header[54]; // header of the BMP file

    if (fread(header, 1, 54, image) != 54)
    {
        throw std::runtime_error("Wrong header of texture file");
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        throw std::runtime_error("Incorrect BMP texture file");
    }

    // Reading header

    int dataPos = *(int *) & (header[0x0A]); // offset for data
    int imageSize = *(int *) & (header[0x22]); // byte size of image
    int width = *(int *) & (header[0x12]);
    int height = *(int *) & (header[0x16]);

    if (imageSize == 0)
    {
        imageSize = width * height * 3; // 3 - for RGB
    }
    if (dataPos == 0)
    {
        dataPos = 54; // straight after header
    }

    unsigned char * data = new unsigned char[imageSize];
    fread(data, 1, imageSize, image);
    fclose(image);

    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return texId;
}
