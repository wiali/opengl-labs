/*
 * CylinderGLWidget.h
 *
 * Graham Fletcher (grahamfletchergt@gmail.com)
 * 30 January 2012
 */

#ifndef CYLINDERGLWIDGET_H
#define CYLINDERGLWIDGET_H

#include <QGLWidget>

#include "Cylinder.h"

class CylinderGLWidget : public QGLWidget, public Cylinder {
    Q_OBJECT

public:
    CylinderGLWidget( QWidget *parent = 0, double height = 0, double radius = 0 );
    ~CylinderGLWidget();

signals:
    void gotNewSurfaceArea( double surfaceArea );
    void gotNewVolume( double volume );

protected:
    void updateProperties();

    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );

private:
    GLUquadricObj *quadric;
    GLuint texture;
    
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;

    QPoint lastPosition;
};
#endif
