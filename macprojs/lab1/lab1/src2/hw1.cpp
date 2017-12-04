
#include <random>
#include <time.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <vector>
#include "lodepng.h"
#include <iostream>
#include <stdio.h>

#define RED   1
#define GREEN 2
#define BLUE  3
#define WHITE 4

#define X 1
#define Y 2
#define Z 3

#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3

#define MORE_TILES 1
#define LESS_TILES   2
#define TOGGLE_ANIMATION  3

#define LOOPS 0
#define LOOPS2 1
#define TRIANGLES 2
#define TRUMP 3
#define TEST 4
#define NUTEST 5
#define MAZEMAKER 6
#define TERRY 7
#define CUBES 8

void MenuGenerator(int itemSelected);


float X_MAX = 640;
float Y_MAX = 480;
float moveAmount = 0.005f;

float angle = 0.0;
float red=1.0, blue=1.0, green=1.0;
float x=0.0, y=0.0, z=1.0;
//int shape = TRIANGLE;
bool redUp = true, blueUp = true, greenUp = true, xUp = true, yUp = true;
float moveX = 0.0, moveY = 0.0;
static std::vector<GLubyte> image;
static GLubyte texImage[25][128][128][4];
bool animating = true;
float winWidth = 700.0, winHeight = 700.0, maxX, maxY;
std::string texFile;
bool reloadTexture = false;
unsigned spinDirection = 0;
float spinX = 0, spinY = 0, spinZ = 0;
unsigned activeTileset = LOOPS;
bool isCallback = true;

unsigned texWidth, texHeight;

static GLuint texName[100];

GLfloat cubeVertices[] = //Vertices to draw cubes for final tileset.
 {-0.5f, -0.5f, 0.5f,   0.5f, -0.5f, 0.5f,   0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,
  -0.5f, 0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
  0.5f, -0.5f, 0.5f,   0.5f, -0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
  -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, -0.5f
  };

//Vertices of textures to map to cubes
 GLfloat cubeTexCoords[] = { 0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                               0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                               0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                               0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0
                             };

 //List of which vertices to draw for each face of the cube.
 GLubyte cubeIndices[24] = {0,1,2,3, 4,5,6,7, 3,2,5,4, 7,6,1,0,
                                  8,9,10,11, 12,13,14,15};

 //Loads texture from filename.png into memory.
void LoadTexture(std::string filename) {
	lodepng::decode(image, texWidth, texHeight, filename.c_str());
}

//Refreshes and updates the screen.
void ProcAnimation(int value) {
	if (animating) {
		glutPostRedisplay();
		glutTimerFunc(2000, ProcAnimation, 0);
	}
	else {
		isCallback = false;
	}
}

//Generates, binds, and associates textures.
void loadTextures(int numNames, std::string fileNames[]) {
	glGenTextures(numNames, texName);
	for (int n = 0; n < numNames; n++) {
		LoadTexture(fileNames[n]);

		//Move to array, vector doesn't work.
		for (int i = 0; i < texHeight; i++) {
			for (int j = 0; j < texWidth; j++) {
				texImage[n][texHeight - i - 1][j][0] = (GLubyte)image[i * 4 * texHeight + j * 4];
				texImage[n][texHeight - i - 1][j][1] = (GLubyte)image[i * 4 * texHeight + j * 4 + 1];
				texImage[n][texHeight - i - 1][j][2] = (GLubyte)image[i * 4 * texHeight + j * 4 + 2];
				texImage[n][texHeight - i - 1][j][3] = (GLubyte)image[i * 4 * texHeight + j * 4 + 3];
			}
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glBindTexture(GL_TEXTURE_2D, texName[n]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight,
					0, GL_RGBA, GL_UNSIGNED_BYTE, texImage[n]);

		image.clear();
		}
}


void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClearDepth(1.0f);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

}

void renderScene(void) {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_TEXTURE_2D);

	//Set up 2D drawing if we're not doing cubes.
	if (activeTileset != CUBES) {
		//Reinitialize our matrices, because they may have been in 3D mode.
		init();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, winWidth, 0, winHeight);

		glBindTexture(GL_TEXTURE_2D, texName[4]);

		//Draw squares, and texture them.
		for (int i = 0; i < winHeight + 20; i += 20) {
			for (int j = 0; j < winWidth + 20; j+= 20) {

				glPushMatrix();

				if (activeTileset == TERRY) {
					glBindTexture(GL_TEXTURE_2D, texName[rand() % 6 + 7]);
				}

				glTranslatef((i), (j), 0);
				glRotatef((rand() % 4) * 90, 0, 0, 1);
				glTranslatef(-(i + 10), -(j + 10), 0);
				glBegin(GL_POLYGON);
				glTexCoord2f(0.0, 0.0);glVertex2f(i,j);
				glTexCoord2f(1.0, 0.0); glVertex2f(i + 20,j);
				glTexCoord2f(1.0, 1.0);glVertex2f(i + 20,j + 20);
				glTexCoord2f(0.0, 1.0);glVertex2f(i,j + 20);
				glEnd();

				glPopMatrix();
			}
		}
	}
	//Set up 3D mode if we're doing cubes.
	else if (activeTileset == CUBES) {
		glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glColor3f( 1, 1, 1);

		glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	   gluPerspective(60.0, (GLfloat) maxX/(GLfloat) maxY, 0.1, 1000.0);

	   	switch(spinDirection) {
		case 0:
			spinX += 0.4;
			break;
		case 1:
			spinX -= 0.4;
			break;
		case 2:
			spinY += 0.4;
			break;
		case 3:
			spinY -= 0.4;
			break;
		case 4:
			spinZ += 0.4;
			break;
		case 5:
			spinZ -= 0.4;
			break;
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(0, -30, 50, 0, 0, -10, 0, 1, 0);
		//Draw the cubes and texture them.
		for (int i = -50; i < 50; i += 10) {
			for (int j = -50; j < 50; j+= 10) {
				if (angle >= 90) {
					angle = 0;
					spinDirection = rand() % 6;
				}

				glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, texName[7]);

				glTranslatef((i), (j), 0);
				glScalef(10, 10, 10);
				glRotatef(spinX, 1, 0, 0);
				glRotatef(spinY, 0, 1, 0);
				glRotatef(spinZ, 0, 0, 1);

				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glEnableClientState(GL_VERTEX_ARRAY);

				for (int k = 0; k < 6; k++) {
					glPushMatrix();
					//Random-looking rotation based on the cube position, since actually keeping track would be difficult.
					switch (k) {
					case 0:
						glRotatef(90 * ((j / 12) + (i / 12)), 0, 0, 1);
						break;
					case 1:
						glRotatef(90 * ((j / 12) + (i / 12)), 0, 0, 1);
						break;
					case 2:
						glRotatef(90 * ((j / 12) + (i / 12)), 0, 1, 0);
						break;
					case 3:
						glRotatef(90 * ((j / 12) + (i / 12)), 0, 1, 0);
						break;
					case 4:
						glRotatef(90 * ((j / 12) + (i / 12)), 1, 0, 0);
						break;
					case 5:
						glRotatef(90 * ((j / 12) + (i / 12)), 1, 0, 0);
						break;

					}
					glBindTexture(GL_TEXTURE_2D, texName[k+1]);
					glTexCoordPointer(2, GL_FLOAT, 0, cubeTexCoords);
					glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
					glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &cubeIndices[k * 4]);

					glPopMatrix();

				}

				glDisableClientState(GL_VERTEX_ARRAY);

				glPopMatrix();

			}
		}
		angle += 0.4;
	}

	glutSwapBuffers();    // double buffering
	glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
	maxX = w;
	maxY = h;

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.1, 1000.0);

   glViewport(0, 0, w, h);



   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void processRightMenuEvents(int option) {

	activeTileset = option;
	MenuGenerator(option);
	glutPostRedisplay();
}

void processLeftMenuEvents(int option) {

	switch (option) {
		case MORE_TILES :
			winWidth *= 2;
			winHeight *= 2;
			glutPostRedisplay();
			break;
		case LESS_TILES :
			winWidth /= 2;
			winHeight /= 2;
			glutPostRedisplay();
			break;
		case TOGGLE_ANIMATION :
			if (animating)
				animating = false;
			else {
				if (!isCallback) {
					isCallback = true;
					glutTimerFunc(2000, ProcAnimation, 0);
				}
				animating = true;
			}
			break;
	}
}

void MenuGenerator(int itemSelected) {
	std::string titles[] = {"Loops", "Loops 2", "Triangles", "Trump", "Test", "NuTest", "Maze", "Faculty", "Cubes"};
	titles[itemSelected]  = "* " + titles[itemSelected];

	glutCreateMenu(processRightMenuEvents);
	glutAddMenuEntry(titles[0].c_str(), LOOPS);
	glutAddMenuEntry(titles[1].c_str(), LOOPS2);
	glutAddMenuEntry(titles[2].c_str(), TRIANGLES);
	glutAddMenuEntry(titles[3].c_str(), TRUMP);
	glutAddMenuEntry(titles[4].c_str(), TEST);
	glutAddMenuEntry(titles[5].c_str(), NUTEST);
	glutAddMenuEntry(titles[6].c_str(), MAZEMAKER);
	glutAddMenuEntry(titles[7].c_str(), TERRY);
	glutAddMenuEntry(titles[8].c_str(), CUBES);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//Only need to animate when we're doing the cubes.
void idleFunc() {
	if (activeTileset == CUBES) {
		glutPostRedisplay();
	}
}

int main(int argc, char **argv) {

	srand((unsigned int) time(0));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);      // set the display mode to double buffering
	glutInitWindowPosition(100,100);
	glutInitWindowSize(700,700);
	glutCreateWindow("Truchet Tiles");
	glutDisplayFunc(renderScene);
	glutIdleFunc(idleFunc);
	glutReshapeFunc(reshape);

	//Generate and load textures
	std::string fnames[] =  {"circle.png", "circles2.png", "triangles.png", "trump.png", "test.png", "nutest.png", "src2/mazemaker.png",
				"src2/terry.png", "src2/jon.png", "src2/doc.png", "src2/cal.png", "src2/gavin.png", "src2/stephen.png"};
	loadTextures(13, fnames);

	init();

	// create the menus
//    MenuGenerator(LOOPS);
//
//    glutCreateMenu(processLeftMenuEvents);
//    glutAddMenuEntry("Increase Density", MORE_TILES );
//    glutAddMenuEntry("Decrease Density", LESS_TILES);
//    glutAddMenuEntry("Toggle Animation", TOGGLE_ANIMATION);
//    glutAttachMenu(GLUT_LEFT_BUTTON);
//
//    glutTimerFunc(2000, ProcAnimation, 0);

	glutMainLoop();

  return 0;
}
