#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"

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


static float positionX = 0.f;
static float positionY = 0.f;
static float positionZ = 0.f;
static float rotationX = 0.f;
static float rotationY = 0.f;
static float rotationZ = 0.f;
static const float dPosition = 0.1f;
static const float dRotation = 5.f;
static float torusParam = 0.4;
static float torusStep = 0.1;


static GLuint textureID = 0;

void display();
void specialKeys(int key, int x, int y);
void drawAxis();
void handleSpecialKeys();
//GLuint loadDDS(const char * imagepath);
GLuint loadTexture(const char * filename);


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Lab1");
    
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    textureID = loadTexture("texture.bmp"); //loadDDS("test_file.DDS");
    
    
    glutMainLoop();
    
    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    //glScalef(0.5f, 0.5f, 0.5f);
    glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
    
    handleSpecialKeys();
    
//    doTask2();
    drawTorus3(0.2, torusParam, 10, 10);
    
    
    glFlush();
    glutSwapBuffers();
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
        torusParam += torusStep;
    else if (key == GLUT_KEY_F4)
        torusParam -= torusStep;
    
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




