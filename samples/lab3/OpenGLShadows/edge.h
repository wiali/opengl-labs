#ifndef EDGE_H
#define EDGE_H

//Represents the edge
struct Edge
{
    //The first point in the edge
    Vertex a;

    //The second point in the edge
    Vertex b;
    
    Edge(Vertex a, Vertex b)
    {
	this->a = a;
	this->b = b;
    }
};

#endif
