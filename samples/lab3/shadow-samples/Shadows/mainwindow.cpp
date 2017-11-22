#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking( true );
    ui->centralWidget->setMouseTracking( true );
    oldPosX = pos().x() + ui->scene->pos().x() + ui->scene->width() / 2.0f;
    oldPosY = pos().y() + ui->scene->pos().y() + ui->scene->height() / 2.0f;
    QCursor::setPos( oldPosX, oldPosY );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch ( event->key() ) {
    case Qt::Key_Escape:
        this->close();
    break;
    case Qt::Key_Up:
        ui->scene->camera.rotateUp();      // повернуть сцену вверх
    break;
    case Qt::Key_Down:
        ui->scene->camera.rotateDown();    // повернуть сцену вниз
    break;
    case Qt::Key_A:
        ui->scene->camera.rotateLeft();     // повернуть сцену влево
    break;
    case Qt::Key_D:
        ui->scene->camera.rotateRight();   // повернуть сцену вправо
    break;
    case Qt::Key_W:
        ui->scene->camera.moveForward();  //перемещение камеры вперед
    break;
    case Qt::Key_S:
        ui->scene->camera.moveBack();     //перемещение камеры назад
    break;
    case Qt::Key_F1:
        //Не функционирует как надо
        /*
        this->setMouseTracking(false);
        ui->centralWidget->setMouseTracking(false);
        helpWindow.setWindowFlags(Qt::WindowStaysOnTopHint);
        helpWindow.show();
        helpWindow.raise();
        this->setMouseTracking(mouseLock);
        ui->centralWidget->setMouseTracking(mouseLock);
        */
    break;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    newPosX = event->globalPos().x();
    newPosY = event->globalPos().y();
    if ( newPosX  == oldPosX && newPosY == oldPosY ) return;
//Смещение старой позиции если курсор заблокирова
        oldPosX = pos().x() + ui->scene->pos().x() + ui->scene->width()/2.0f;
        oldPosY = pos().y() + ui->scene->pos().y() + ui->scene->height()/2.0f;
//Блок проверки смещения
    if ( newPosX > oldPosX ){
        ui->scene->camera.rotateRight();
    }else if ( newPosX < oldPosX ){
        ui->scene->camera.rotateLeft();
    }
    if ( newPosY > oldPosY ){
        ui->scene->camera.rotateDown();
    }else if( newPosY < oldPosY ){
        ui->scene->camera.rotateUp();
    }
//Возврат курсора если он заблокирован
        QCursor::setPos( oldPosX, oldPosY );
}

