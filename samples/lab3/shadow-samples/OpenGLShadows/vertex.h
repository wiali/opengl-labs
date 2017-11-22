#ifndef VERTEX_H
#define VERTEX_H

//Represents a single point in the scene.
struct Vertex
{
    int x, y;

    Vertex() { }
    
    Vertex(int x, int y)
    {
	this->x = x;
	this->y = y;
    }

    static Vertex Add(Vertex v1, Vertex v2)
    {
	return Vertex(v2.x + v1.x, v2.y + v1.y);
    }

    static Vertex Sub(Vertex v1, Vertex v2)
    {
	return Vertex(v2.x - v1.x, v2.y - v1.y);
    }

    Vertex Multiply(float value)
    {
	return Vertex(x * value, y * value);
    }
};

#endif
