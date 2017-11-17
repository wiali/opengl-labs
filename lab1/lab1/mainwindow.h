#ifndef MAINWINDOW_H
#define MAINWINDOW_H


class MainWindow
{


public:
//    static MainWindow& getInstance();
    MainWindow(int argc, char *argv[]);
    static void init();
    static void display();
    static void resize(int w, int h);
    static void handleKeyboard(int key, int x, int y);


//    MainWindow(MainWindow const&) = delete;
//    void operator=(MainWindow const&) = delete;

private:
    static float _xrot;
    static float _yrot;

    static void drawCylinder();
};

#endif // MAINWINDOW_H
