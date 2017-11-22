/*
 * CylinderGLWidget.cpp
 *
 * Graham Fletcher (grahamfletchergt@gmail.com)
 * 30 January 2012
 */

#include <math.h>
#include <QMouseEvent>
#include <QMutexLocker>

#include "CylinderGLWidget.h"

#define SUBDIVISIONS 32

CylinderGLWidget::CylinderGLWidget( QWidget *parent, double height, double radius ) : QGLWidget( parent ), Cylinder( height, radius ) {
    /* Set a few options we'll appreciate later */
    setFormat( QGLFormat( QGL::DoubleBuffer | QGL::DepthBuffer ) );

    /* Set up an initial tilt, to give a better perspective */
    rotationX = -60.0;
    rotationY = 0.0;
    rotationZ = 0.0;
}

CylinderGLWidget::~CylinderGLWidget() {
    /* Don't forget to clean up when we're done */
    gluDeleteQuadric( quadric );
}

void CylinderGLWidget::updateProperties() {
    /* Perform the actual updates */
    Cylinder::updateProperties();

    QMutexLocker locker( &cylinderMutex );

    /* Emit the signals for any connections that might be listening */
    emit gotNewSurfaceArea( surfaceArea );
    emit gotNewVolume( volume );

    /* Redraw the cylinder */
    updateGL();
}

void CylinderGLWidget::initializeGL() {
    /* Prepare the environment */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glShadeModel( GL_FLAT );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glClearDepth( 1.0f );
    glDepthFunc( GL_LESS );

    /* Make the object look nice and smooth */
    glShadeModel(GL_SMOOTH);

    /* Add some light */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);

    /* Create the quadric to be used for the cylinder */
    quadric = gluNewQuadric();
}

void CylinderGLWidget::resizeGL( int viewportWidth, int viewportHeight ) {
    /* Since the MainWindow cannot be resized, this should only be called once*/
    glViewport( 0, 0, viewportWidth, viewportHeight );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, -100.0, 1000.0 );
    glMatrixMode( GL_MODELVIEW );
}

void CylinderGLWidget::paintGL() {
    /* Calculate the height and radius values to use when drawing the cylinder*/
    float r = (float) 3 * Cylinder::radius / QWidget::width();
    float h = (float) 3 * Cylinder::height / QWidget::height();

    /* Cleanup everything so we can draw */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        /* Position the object so it's in view and apply the user's rotations */
        glTranslatef( 0, -(h / 2), -0.12 );
        glRotatef( rotationX, 1.0, 0.0, 0.0 );
        glRotatef( rotationY, 0.0, 1.0, 0.0 );
        glRotatef( rotationZ, 0.0, 0.0, 1.0 );
 
        /* Draw the cylinder */
        gluQuadricOrientation(quadric,GLU_OUTSIDE);
        gluCylinder(quadric, r, r, h, SUBDIVISIONS, 1);

        /* Draw the first cap */
        gluQuadricOrientation( quadric, GLU_INSIDE );
        gluDisk( quadric, 0.0, r, SUBDIVISIONS, 1 );
        glTranslatef( 0.0, 0.0, h );

        /* Draw the second cap */
        gluQuadricOrientation( quadric, GLU_OUTSIDE );
        gluDisk( quadric, 0.0, r, SUBDIVISIONS, 1);
    glPopMatrix();
}

void CylinderGLWidget::mousePressEvent( QMouseEvent *event ) {
    /* Save the mouse coordinates */
    lastPosition = event->pos();
}

void CylinderGLWidget::mouseMoveEvent( QMouseEvent *event ) {
    /* Calculate how far the mouse has moved in each direction */
    GLfloat dx = GLfloat( event->x() - lastPosition.x() ) / QWidget::width();
    GLfloat dy = GLfloat( event->y() - lastPosition.y() ) / QWidget::height();

    /* See if a buttn was being held down and respond accordingly */
    if ( event->buttons() & Qt::LeftButton ) {
        rotationX += 180 * dy;
        rotationY += 180 * dx;

        updateGL();
    } else if ( event->buttons() & Qt::RightButton ) {
        rotationX += 180 * dy;
        rotationZ += 180 * dx;

        updateGL();
    }

    /* Record the position for next time */
    lastPosition = event->pos();
}

