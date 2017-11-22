#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <QString>

struct cordinate{
    float x;
    float y;
    float z;
};

class Loader
{
public:
    Loader();
    static void loadModel(QString fileName, std::vector<float> *vertices, std::vector<float> *textures, std::vector<float> *normals);
};

#endif // LOADER_H
