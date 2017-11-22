#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    //w.setWindowFlags(Qt::WindowStaysOnTopHint);
    //w.setWindowState(Qt::WindowNoState);
    w.setFocusPolicy(Qt::StrongFocus);
    w.show();
    return a.exec();
}
