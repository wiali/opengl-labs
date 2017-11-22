/*
 * MainWindow.cpp
 *
 * Graham Fletcher (grahamfletchergt@gmail.com)
 * 30 January 2012
 */

#include <QtGlobal>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

#include "CylinderGLWidget.h"
#include "MainWindow.h"

#define MAX_HEIGHT 100.0
#define MAX_RADIUS 50.0

MainWindow::MainWindow( QWidget *parent ) : QDialog( parent ) {
    /* Set everything up */
    createObjects();
    makeLayout();

    /* Give us a nice window title */
    setWindowTitle( "Cylinder: CDL Systems Sample Program" );

    /* Set each slider to the middle of its range */
    heightSlider->setValue( 5 * MAX_HEIGHT );
    radiusSlider->setValue( 5 * MAX_RADIUS );
}

MainWindow::~MainWindow() {

}

void MainWindow::createObjects() {
    /* OpenGL widget */

    cylinderGLWidget = new CylinderGLWidget( this );

    QObject::connect( cylinderGLWidget, SIGNAL( gotNewSurfaceArea( double ) ),
                      this,             SLOT( updateSurfaceArea( double ) ) );
    QObject::connect( cylinderGLWidget, SIGNAL( gotNewVolume( double ) ),
                      this,             SLOT( updateVolume( double ) ) );


    /* Height and radius sliders */

    heightSlider = new QSlider( Qt::Vertical, this );
    radiusSlider = new QSlider( Qt::Horizontal, this );

    heightSlider->setRange( 0, (10 * MAX_HEIGHT) );
    radiusSlider->setRange( 0, (10 * MAX_RADIUS) );

    QObject::connect( heightSlider, SIGNAL( valueChanged( int ) ),
                      this,         SLOT( heightSliderChanged( int ) ) );
    QObject::connect( radiusSlider, SIGNAL( valueChanged( int ) ),
                      this,         SLOT( radiusSliderChanged( int ) ) );


    /* Labels */

    heightLabel =      new QLabel( "0.0", this );
    radiusLabel =      new QLabel( "0.0", this );
    surfaceAreaLabel = new QLabel( "0.0", this );
    volumeLabel =      new QLabel( "0.0", this );
}

void MainWindow::makeLayout() {
    /* Create/setup widgets */
    cylinderGLWidget->setFixedSize( (3 * MAX_HEIGHT), (6 * MAX_RADIUS) );

    QLabel *heightBuddy =      new QLabel( "Height:",       this );
    QLabel *radiusBuddy =      new QLabel( "Radius:",       this );
    QLabel *surfaceAreaBuddy = new QLabel( "Surface area:", this );
    QLabel *volumeBuddy =      new QLabel( "Volume:",       this );

    QFrame *line = new QFrame( this );
    line->setFrameShape( QFrame::HLine );
    line->setFrameShadow( QFrame::Sunken );

    /* Create first grid layout */
    QGridLayout *gridLayout1 = new QGridLayout();
    
    gridLayout1->addWidget( cylinderGLWidget, 0, 0 );
    gridLayout1->addWidget( heightSlider,     0, 1 );
    gridLayout1->addWidget( radiusSlider,     1, 0 );

    /* Create second grid layout */
    QGridLayout *gridLayout2 = new QGridLayout();

    gridLayout2->addWidget( heightBuddy, 0, 0 );
    gridLayout2->addWidget( heightLabel, 0, 1 );
    gridLayout2->addWidget( radiusBuddy, 1, 0 );
    gridLayout2->addWidget( radiusLabel, 1, 1 );
    gridLayout2->addWidget( surfaceAreaBuddy, 2, 0 );
    gridLayout2->addWidget( surfaceAreaLabel, 2, 1 );
    gridLayout2->addWidget( volumeBuddy, 3, 0 );
    gridLayout2->addWidget( volumeLabel, 3, 1 );

    /* Add everything to the outer, vertical layout */
    QVBoxLayout *verticalLayout = new QVBoxLayout();

    verticalLayout->addLayout( gridLayout1 );
    verticalLayout->addWidget( line );
    verticalLayout->addLayout( gridLayout2 );

    /* Apply the layout to the main window */
    setLayout( verticalLayout );

    /* Disable resizing of the window */
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::heightSliderChanged( int value ) {
    /* The slider only reports in integers; compensate for this */
    double height = (double) value / 10;

    /* Update the CylinderGLWidget */
    cylinderGLWidget->setHeight( height );

    /* Update the height label */
    heightLabel->setText( QString::number( height, 'f', 1 ) );
}

void MainWindow::radiusSliderChanged( int value ) {
    /* The slider only reports in integers; compensate for this */
    double radius = (double) value / 10;

    /* Update the CylinderGLWidget */
    cylinderGLWidget->setRadius( radius );

    /* Update the radius label */
    radiusLabel->setText( QString::number( radius, 'f', 1 ) );
}

void MainWindow::updateSurfaceArea( double surfaceArea ) {
    /* Update the surface area label */
    surfaceAreaLabel->setText( QString::number( surfaceArea, 'f', 1 ) );
}

void MainWindow::updateVolume( double volume ) {
    /* Update the volume label */
    volumeLabel->setText( QString::number( volume, 'f', 1 ) );
}
