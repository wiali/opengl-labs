#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "rect.h"
#include <vector>

//The dimensions of the screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//All things that block the light
std::vector<Rect> occluders;

//The position the light source is at.
Vertex lightSource;

void createObstacles()
{
    //Create two sample obstacles
    occluders.push_back(Rect(640, 360, 100, 100));
    occluders.push_back(Rect(850, 600, 150, 150));
}

void trackMousePosition(GLFWwindow* window)
{
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    //Rounds to int since it will be drawing to pixels
    lightSource.x = (int)mouseX;
    lightSource.y = (int)mouseY;

    //Draws the position of the light source (mouse position)
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(lightSource.x, lightSource.y);
    glEnd();
}

//Called foreach edge in the occluder
void renderShadow(Rect rect)
{
    for (int i = 0; i < rect.edges.size(); i++)
    {
	//The distance from the light source to the first corner of the polygon
	Vertex displacementA = Vertex::Sub(lightSource, rect.edges[i].a);

	//The backpoint of the shadow calculated by adding the distance above.
	Vertex backpointA = Vertex::Add(rect.edges[i].a, displacementA);

	//The process is repeated for the other point in the line segment.
	Vertex displacementB = Vertex::Sub(lightSource, rect.edges[i].b);
	Vertex backpointB = Vertex::Add(rect.edges[i].b, displacementB);

	//Gray colour for shadows
	glColor3f(0.75,0.75,0.75);

	//Draws the shadow additively, the order is clockwise (this is important)
	glBegin(GL_POLYGON);
	glVertex2f(rect.edges[i].a.x, rect.edges[i].a.y);
	glVertex2f(backpointA.x, backpointA.y);
	glVertex2f(backpointB.x, backpointB.y);
	glVertex2f(rect.edges[i].b.x, rect.edges[i].b.y);
	glEnd();
    }
}

int main()
{
    //Initialize GLFW
    glfwInit();

    //Create a window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
					  "OpenGL Dynamic Shadows", NULL, NULL);

    //Prevents a segmentation fault
    glfwMakeContextCurrent(window);

    //Changes the coordinate system from -1 to 1 to the entire screen size.
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);

    createObstacles();

    while (!glfwWindowShouldClose(window))
    {
	//Fill with a white background
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	trackMousePosition(window);

	//The first pass draws all of the shadows
	for (int i = 0; i < occluders.size(); i++)
	    renderShadow(occluders[i]);

	//The colour of the squares are dark grey.
	glColor3f(0.2, 0.2, 0.2);
	
	//The shapes are drawn on top of the shadows.
	for (int i = 0; i < occluders.size(); i++)
	    occluders[i].render();	    

	//Update the screen
	glfwSwapBuffers(window);

	//Check for input, and close events.
	glfwPollEvents();
    }
    
    return 0;
}
