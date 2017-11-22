#include "camera.h"

Camera::Camera()
{
    distance = 1.0f;
}

Camera::~Camera(){

}

void Camera::setPosition( QVector3D position ){
    eye = position;
    hRot = 0.0f;
    vRot = M_PI / 2.0f;
    center.setZ( eye.x() + distance * sin(vRot) * cos(hRot) );
    center.setY( eye.y() + distance * cos(vRot) );
    center.setZ( eye.z() + distance * sin(vRot) * sin(hRot) );
}

void Camera::moveForward(){
    eye = center;
}

void Camera::moveBack(){
    eye.setX( eye.x() - distance * sin(vRot) * cos(hRot) );
    eye.setY( eye.y() - distance * cos(vRot) );
    eye.setZ( eye.z() - distance * sin(vRot) * sin(hRot) );
}

void Camera::rotateUp() // повернуть сцену вверх
{
    if (vRot > M_PI / 10) vRot -= 0.02f;
}

void Camera::rotateDown() // повернуть сцену вниз
{
    if (vRot < M_PI * 9 / 10) vRot += 0.02f;
}

void Camera::rotateLeft() // повернуть сцену влево
{

    if (hRot > 0)
        hRot -= 0.02f;
    else
        hRot = 2 * M_PI - hRot;

}

void Camera::rotateRight() // повернуть сцену вправо
{
    if (hRot < 2 * M_PI)
        hRot += 0.02f;
    else
        hRot = hRot - 2 * M_PI;
}

QMatrix4x4 Camera::getMatrix(){
    vMatrix.setToIdentity();
    center.setX( eye.x() + distance * sin(vRot) * cos(hRot) );
    center.setY( eye.y() + distance * cos(vRot) );
    center.setZ( eye.z() + distance * sin(vRot) * sin(hRot) );
    vMatrix.lookAt( eye, center, QVector3D(0.0f, 1.0f, 0.0f) );
    return vMatrix;
}

QVector3D Camera::getPosition(){
    return eye;
}
