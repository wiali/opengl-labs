#include <stdio.h>
#include "mainwindow.h"

int mainp(int argc, char *argv[])
{
/*
    int task = 1;
    printf("Choose task:\n"
           "\t1) Cylinder\n"
           "\t2) SMTH\n\n"
           "write here: ");
    scanf("%d", &task);

    switch (task) {
    case 1:
        printf("cylinder");
        break;
    case 2:
        printf("smth");
        break;
    default:
        break;
    }
*/

    MainWindow window(argc, argv);
    window.init();



    return 0;
}