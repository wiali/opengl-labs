/*
 * MainWindow.h
 *
 * Graham Fletcher (grahamfletchergt@gmail.com)
 * 30 January 2012
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

class CylinderGLWidget;
class QLabel;
class QSlider;

class MainWindow : public QDialog {
    Q_OBJECT

public:
    MainWindow( QWidget *parent = 0 );
    ~MainWindow();

private:
    CylinderGLWidget *cylinderGLWidget;

    QSlider *heightSlider;
    QSlider *radiusSlider;

    QLabel *heightLabel;
    QLabel *radiusLabel;
    QLabel *surfaceAreaLabel;
    QLabel *volumeLabel;

    void createObjects();
    void makeLayout();

private slots:
    void heightSliderChanged( int value );
    void radiusSliderChanged( int value );

    void updateSurfaceArea( double surfaceArea );
    void updateVolume( double volume );
};
#endif
