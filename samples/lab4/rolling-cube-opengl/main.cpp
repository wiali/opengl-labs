

#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include "screensaver.h"


int main(int argc, char** argv){
	// if (argc < 3) {
	// 	cout << "syntaxe d'execution : \n" <<
	// 	" ./screensaver WSCREEN HSCREEN\n";
	// 	return 0;
	// }//if
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (atoi(argv[1]), atoi(argv[2]));
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutIdleFunc(idleFunction);
   glutMainLoop();
   return 1;
}//main
