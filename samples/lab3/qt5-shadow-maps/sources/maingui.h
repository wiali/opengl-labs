#ifdef _MSC_VER
#pragma once
#endif

#ifndef _MAINGUI_H_
#define _MAINGUI_H_

#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qopenglwidget.h>

#include "openglviewer.h"

class MainGUI : public QMainWindow {
    Q_OBJECT
public:
    // Public methods
    explicit MainGUI(QWidget* parent = nullptr);
    ~MainGUI();

private slots:
    // Private slots
    void OnSaveButtonClicked();
    void OnRadioButtonChanged(bool);

private:
    // Private fields
    QWidget *mainWidget;
    QGridLayout *mainLayout;

    OpenGLViewer *viewer;

    class Ui;
    Ui *ui;
};

#endif  // _MAINGUI_H_
