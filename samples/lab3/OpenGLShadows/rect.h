#ifndef RECT_H
#define RECT_H

#include <vector>
#include "vertex.h"
#include "edge.h"

struct Rect
{
    //Position of the rectangle
    int x, y;

    //Width and height of the rectangle.
    int w, h;

    //Each vertex of the rectangle
    std::vector<Vertex> points;

    //The edges of the rectangle
    std::vector<Edge> edges;
    
    Rect(int x, int y, int w, int h)
    {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	//The vertices in clock wise order.
	points.push_back(Vertex(x - w / 2, y - h / 2)); //Top left
	points.push_back(Vertex(x - w / 2, y + h / 2)); //Bottom left
	points.push_back(Vertex(x + w / 2, y + h / 2)); //Bottom right
	points.push_back(Vertex(x + w / 2, y - h / 2)); //Top right

	//The edges of the rectangle
	edges.push_back(Edge(points[1], points[2])); //Bottom 
	edges.push_back(Edge(points[1], points[0])); //Left
	edges.push_back(Edge(points[0], points[3])); //Top
	edges.push_back(Edge(points[2], points[3]));//Right
     }

    //Draw the rectangle
    void render()
    {
	glBegin(GL_QUADS);
	for (int i = 0; i < points.size(); i++)
	   glVertex2f(points[i].x, points[i].y);
	glEnd();
    }
};

#endif
