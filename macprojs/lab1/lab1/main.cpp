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
    glutInitDisplayMode (/*GLUT_DOUBLE | */GLUT_RGB/* | GLUT_DEPTH*/);
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
//
//    glPushMatrix();
//
//    glPushMatrix();
////    drawAxis();
//    glPopMatrix();
//    //    doTask123(positionX, positionY, positionZ);
////    doTask2();
    
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    glColor3f(1.f, 0.f, 0.f);
//    glutSolidTeapot(1.f);
//    glutSolidOctahedron();
//    glPushMatrix();
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    
//    glPopMatrix();
//    gluSolidSphere(1.f, 8, 8);
//    drawTorus();
//    glutSolidOctahedron();
    glutSolidSphere(1, 10, 10);
//    glutSolidTorus(0.5f, 1.f, 10, 10);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();
    
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



/*
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char * imagepath){
    
    unsigned char header[124];
    
    FILE *fp;
    
    
    fp = fopen(imagepath, "rb");
    if (fp == NULL){
        //printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
        throw std::invalid_argument("Wrong texture filename");
        return 0;
    }
    

    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }
    

    fread(&header, 124, 1, fp);
    
    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
    
    
    unsigned char * buffer;
    unsigned int bufsize;

    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);

    fclose(fp);
    
    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(buffer);
            return 0;
    }
    
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);
        
        offset += size;
        width  /= 2;
        height /= 2;
        
        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if(width < 1) width = 1;
        if(height < 1) height = 1;
        
    }
    
    free(buffer);
    
    return textureID;
}
*/
