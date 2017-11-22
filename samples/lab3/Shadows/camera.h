#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <math.h>

class Camera
{
    QVector3D eye;
    QVector3D center;
    float hRot;
    float vRot;
    float distance;
    QMatrix4x4 vMatrix;
public:
    Camera();
    ~Camera();
    void setPosition( QVector3D position );
    void moveForward();
    void moveBack();
    void rotateUp();
    void rotateDown();
    void rotateRight();
    void rotateLeft();
    QMatrix4x4 getMatrix();
    QVector3D getPosition();
};

#endif // CAMERA_H
