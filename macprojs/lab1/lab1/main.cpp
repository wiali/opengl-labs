#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif
#ifdef __linux__
// macro for linux
#endif

static float positionX = 0.f;
static float positionY = 0.f;
static float rotationX = 0.f;
static float rotationY = 0.f;
static const float dPosition = 0.1f;
static const float dRotation = 0.1f;

GLuint texture;
//
//// LOADING TEXTURE
////void loadTexture(GLuint* texture, char* filename){
////
////    *texture = SOIL_load_OGL_texture ("ImageName.tga",
////                                     SOIL_LOAD_AUTO,
////                                     SOIL_CREATE_NEW_ID,
////                                     SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
////                                     );
////
////    if(*texture == NULL){
////        printf("[Texture loader] \"%s\" failed to load!\n", filename);
////    }
////}
//
//
///*
// r = torus ring radius
// c = torus tube radius
// rSeg, cSeg = number of segments/detail
// */
//void drawTorus(double r = 0.07, double c = 0.0,
//               int rSeg = 16, int cSeg = 8,
//               int texture = 0)
//{
//    glFrontFace(GL_CW);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    const double PI = 3.1415926535897932384626433832795;
//    const double TAU = 2 * PI;
//    for (int i = 0; i < rSeg; i++) {
//        //        glBegin(GL_QUAD_STRIP);
//        glBegin(GL_LINE_LOOP);
//        for (int j = 0; j <= cSeg; j++) {
//            for (int k = 0; k <= 1; k++) {
//                double s = (i + k) % rSeg + 0.5;
//                double t = j % (cSeg + 1);
//                double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
//                double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
//                double z = r * sin(s * TAU / rSeg);
//                double u = (i + k) / (float) rSeg;
//                double v = t / (float) cSeg;
//                glTexCoord2d(u, v);
//                glNormal3f(2 * x, 2 * y, 2 * z);
//                glVertex3d(2 * x, 2 * y, 2 * z);
//            }
//        }
//        glEnd();
//    }
//    glFrontFace(GL_CCW);
//}
//
//void wireCylinder(float r, float h, int nsides, int nlongs) {
//    glColor3f(1.f, 1.f, 0.f);
//
//    float x = 0.f;
//    float y = 0.f;
//    const float FULL_ANGLE = 360.f;
//    float angle_stepsize = FULL_ANGLE / nsides;
//    float h_stepsize = h / nlongs;
//
//    for (int i = 0; i < nlongs; i++) {
//        glBegin(GL_LINE_LOOP);
//        for (int j = 0; j < nsides; j++) {
//            x = r * cos(j * angle_stepsize);
//            y = r * sin(j * angle_stepsize);
//
//            glVertex3f(y, i * h_stepsize, x);
//        }
//        glEnd();
//    }
//}
//
//void wireCylinder2(float r, float h, float ang_step) {
//
//    glBegin(GL_LINES);
//    float x = 0.f;
//    float y = 0.f;
//    float angle = 0.f;
//    float angle_stepsize = ang_step;
//
//    while (angle < 2 * M_PI) {
//        x = r * cos(angle);
//        y = r * sin(angle);
//        glVertex3f(x, -h / 2, y);
//        glVertex3f(x, h / 2, y );
//        angle += angle_stepsize;
//    }
//    glVertex3f(r, -h / 2, 0.f);
//    glVertex3f(r, h / 2, 0.f);
//    glEnd();
//
//    // top and bottom
//    // FIXME circle
//    glBegin(GL_LINE_LOOP);
//    angle = 0.f;
//
//    while (angle < 2 * M_PI) {
//        x = r * cos(angle);
//        y = r * sin(angle);
//        glVertex3f(x, -h / 2, y);
//        angle = angle + angle_stepsize;
//    }
//    glVertex3f(r, -h / 2, 0.f);
//    glEnd();
//
//    glBegin(GL_LINE_LOOP);
//    angle = 0.f;
//
//    while (angle < 2 * M_PI) {
//        x = r * cos(angle);
//        y = r * sin(angle);
//        glVertex3f(x, h / 2, y);
//        angle = angle + angle_stepsize;
//    }
//    glVertex3f(r, h / 2, 0.f);
//    glEnd();
//}
//
//void wireSphere(float r) {
//
//    glutWireSphere(r,8,8);
//}
//
//void specialKeys(int key, int x, int y) {
//
//    if (key == GLUT_KEY_RIGHT)
//        rotate_y -= 5;
//
//    else if (key == GLUT_KEY_LEFT)
//        rotate_y += 5;
//
//    else if (key == GLUT_KEY_UP)
//        rotate_x += 5;
//
//    else if (key == GLUT_KEY_DOWN)
//        rotate_x -= 5;
//
//    else if (key == GLUT_KEY_F1)
//        rotata_scene += 5;
//
//    else if (key == GLUT_KEY_F2) {
//        move_sphere -= 0.1;
//        //        move_octahedron += 0.1;
//    }
//
//    else if (key == GLUT_KEY_F3) {
//        move_sphere += 0.1;
//        move_octahedron -= 0.1;
//    }
//    //    printf("ddada");
//    glutPostRedisplay();
//
//}
//
//void handleKeys() {
//    glRotatef(rotate_x, 1.0, 0.0, 0.0);
//    glRotatef(rotate_y, 0.0, 1.0, 0.0);
//    //    gluPerspective(
//    //                   40.0, /* угол зрения в градусах */
//    //                   (float)1, /* коэффициент сжатия окна */
//    //                   1,100.0);
//
//    //    gluLookAt(
//    //              1.f, 1.f, 1.f, // eye position
//    //              0.f, 0.f, 0.f,  // scene center
//    //              0.f, 0.f, 1.f); // up vector (y)
//    //
//    glRotatef(rotata_scene, 1.0, 0.0, 0.0);
//}
//
//void workingwithtexture() {
//    //    GLuint texture;
//    //    glGenTextures(1, &texture);
//    //    glBindTexture(GL_TEXTURE_2D, texture);
//    //    // Устанавливаем настройки фильтрации и преобразований (на текущей текстуре)
//    //
//    //    // Загружаем и генерируем текстуру
//    //    int width, height;
//    //    unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    //    glGenerateMipmap(GL_TEXTURE_2D);
//    //    SOIL_free_image_data(image);
//    //    glBindTexture(GL_TEXTURE_2D, 0);
//
////    glColor3f(0.0f,1.0f,.50f);
////    glBindTexture(GL_TEXTURE_2D, texture);
////    glEnable(GL_TEXTURE_2D);
////    glBegin(GL_QUADS);
////    glTexCoord2d(0,0);        glVertex3f(0,0,0);
////    glTexCoord2d(0,1);        glVertex3f(0,1, 1);
////    glTexCoord2d(1,1);        glVertex3f(1,1,1);
////    glTexCoord2d(1,0);        glVertex3f(1, 1, 0);
////
////
////    glEnd();
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_GEN_S);
//    glEnable(GL_TEXTURE_GEN_T);
//
////    glLoadIdentity();
//
//    glColor3f(0.4,0.5, 0);
//    glPushMatrix(); // ?
//    //glTranslatef(0, 0, <#GLfloat z#>)
//    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//
//    glutWireTorus(0.2f, 0.5f, 10, 10);
//    glPopMatrix();
//
//    glDisable(GL_TEXTURE_GEN_S);
//    glDisable(GL_TEXTURE_GEN_T);
//    glDisable(GL_TEXTURE_2D);
//
////    glutSwapBuffers();
//}
//
//
//void display(void) {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//
//    //glScalef(0.5f, 0.5f, 0.5f);
//    glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
//
//    handleKeys();
//
//    drawAxis();
//    //    wireCylinder2(0.5f, 1.f, 0.5);
//        glTranslatef(move_sphere, 0.f, 0.f);
//    //    wireSphere(0.5f);
////    glColor3d(1.f, 1.f, 0.f);
//    //    glutWireTorus(0.2f, 0.5f, 10, 10);
////    drawTorus();
//    //    glutWireOctahedron();
//
//    workingwithtexture();
//
//    glFlush();
//    glutSwapBuffers();
//}
//
//int main(int argc, char* argv[]) {
//
//    glutInit(&argc, argv);
//    //glewInit();
//    glutInitDisplayMode(/*GLUT_DOUBLE | */GLUT_RGBA /*| GLUT_DEPTH*/);
//    glutInitWindowSize(800, 800);
//    glutCreateWindow("Cube + Octahedron");
//    // glEnable(GL_DEPTH_TEST);
//
////    glEnable(GL_TEXTURE_2D);
////    texture = SOIL_load_OGL_texture ("tree.jpg",
////                                      SOIL_LOAD_AUTO,
////                                      SOIL_CREATE_NEW_ID,
////                                      SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
////                                      );
////
//
//
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    // Устанавливаем настройки фильтрации и преобразований (на текущей текстуре)
//
//    // Загружаем и генерируем текстуру
//    int width, height;
//    unsigned char* image = SOIL_load_image("tree.png", &width, &height, 0, SOIL_LOAD_RGB);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    SOIL_free_image_data(image);
//    glBindTexture(GL_TEXTURE_2D, 0);
//
//
//
//    glutDisplayFunc(display);
//    glutSpecialFunc(specialKeys);
//    glutMainLoop();
//
//    return 0;
//}

//void drawAxis() {
//    // red OX
//    glColor3f(1.f, 0.f, 0.f);
//    glBegin(GL_LINES);
//    glVertex3f(0.f, 0.f, 0.f);
//    glVertex3f(1.f, 0.f, 0.f);
//    glEnd();
//
//    // green OY
//    glColor3f(0.f, 1.f, 0.f);
//    glBegin(GL_LINES);
//    glVertex3f(0.f, 0.f, 0.f);
//    glVertex3f(0.f, 1.f, 0.f);
//    glEnd();
//
//    // blue OZ
//    glColor3f(0.f, 0.f, 1.f);
//    glBegin(GL_LINES);
//    glVertex3f(0.f, 0.f, 0.f);
//    glVertex3f(0.f, 0.f, 1.f);
//    glEnd();
//}


/*
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

/*  
static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

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
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glBindTexture(GL_TEXTURE_1D, texName);
    
//    glutWireTorus(0.5, 0.5, 10, 10);
//    glutSolidTorus(2, 2, 4, 5);
//    glutSolidTeapot(2.0);
//    glutSolidOctahedron();
//    glutSolidSphere(2, 10, 10);
    glutSolidTorus(0.1, 0.5, 10, 10);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix ();
    glutSolidSphere(3, 10, 11);
    
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-3.5, 3.5, -3.5*(GLfloat)h/(GLfloat)w,
                 3.5*(GLfloat)h/(GLfloat)w, -3.5, 3.5);
    else
        glOrtho (-3.5*(GLfloat)w/(GLfloat)h,
                 3.5*(GLfloat)w/(GLfloat)h, -3.5, 3.5, -3.5, 3.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'e':
        case 'E':
            currentGenMode = GL_EYE_LINEAR;
            currentPlane = GL_EYE_PLANE;
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
            glTexGenfv(GL_S, currentPlane, currentCoeff);
            glutPostRedisplay();
            break;
        case 'o':
        case 'O':
            currentGenMode = GL_OBJECT_LINEAR;
            currentPlane = GL_OBJECT_PLANE;
            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
            glTexGenfv(GL_S, currentPlane, currentCoeff);
            glutPostRedisplay();
            break;
        case 's':
        case 'S':
            currentCoeff = slanted;
            glTexGenfv(GL_S, currentPlane, currentCoeff);
            glutPostRedisplay();
            break;
        case 'x':
        case 'X':
            currentCoeff = xequalzero;
            glTexGenfv(GL_S, currentPlane, currentCoeff);
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
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
//    glutInitWindowPosition(100, 100);
    glutCreateWindow (argv[0]);
//    init();
    
//    GLuint ss = loadTexture("texture.bmp");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


*/
