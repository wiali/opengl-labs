/*
 * main.cpp
 *
 * Graham Fletcher (grahamfletchergt@gmail.com)
 * 30 January 2012
 */


#include <iostream>
#include <stdlib.h>
#include <QApplication>

#include "Cylinder.h"
#include "MainWindow.h"

void printUsage( ) {
    std::cout << "Usage: cylinder                  launch GUI" << "\n";
    std::cout << "   or: cylinder [arguments]      run in batch mode" << "\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  -h, --height <float>           height of the cylinder\n";
    std::cout << "  -r, --radius <float>           radius of the cylinder\n";
}

int processBatch( int argc, char *argv[] ) {

    double radius = 0, height = 0;

    for ( int i = 1; i < argc; i++ ) {

        if ( strcmp( argv[i], "--help" ) == 0 ) {
            std::cout << "cylinder - A sample program for CDL Systems (compiled " << __DATE__ << " " << __TIME__ << ")\n\n";
            printUsage();

            return EXIT_SUCCESS;
        } else if ( strcmp( argv[i], "-h" ) == 0 ||
                    strcmp( argv[i], "--height" ) == 0 ) {

            /* Don't try to read an argument that doesn't exist (segmentation fault) */
            if ( ++i < argc && argv[i][0] != '-' ) {
                height = atof( argv[i] );
            } else {
                printUsage();
                
                return EXIT_FAILURE;
            }
        } else if ( strcmp( argv[i], "-r" ) == 0 ||
                    strcmp( argv[i], "--radius" ) == 0 ) {

            /* Don't try to read an argument that doesn't exist (segmentation fault) */
            if ( ++i < argc && argv[i][0] != '-' ) {
                radius = atof( argv[i] );
            } else {
                printUsage();

                return EXIT_FAILURE;
            }
        } else {
            std::cout << "cylinder: invalid parameter " << argv[i] << "\n\n";
            printUsage();

            return EXIT_FAILURE;
        }
    }

    if ( height < 0 || radius < 0 ) {
        std::cout << "cylinder: dimensions cannot be negative\n";

        return EXIT_FAILURE;
    }

    /* Create the cylinder object */
    Cylinder cylinder( height, radius );

    /* Print the properties of the cylinder */
    std::cout << "Surface area: " << cylinder.getSurfaceArea() << "\n";
    std::cout << "Volume: " << cylinder.getVolume() << "\n";

    return EXIT_SUCCESS;
}

int main ( int argc, char *argv[] ) {
    //Cylinder cylinder = new Cylinder();

    if ( argc > 1 ) {
        // running in batch mode

        return processBatch( argc, argv );
    }
    
    QApplication app( argc, argv );

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();

    return app.exec();
}
