///*
//Задание 35.

//1. Изобразить каркасный цилиндр и каркасную сферу внутри цилиндра. Размеры объектов задать самостоятельно.
//2. Совместить центр основания цилиндра и центр сферы.
//3. Выполнить перемещение двух объектов на dy=20.
//4. Изобразить тор и октаэдр, считая, что вершина октаэдра совпадает с центром тора. Размеры примитивов задать самостоятельно.
//5. Наложить текстуры на объекты.
//6. Произвести пошаговый пересчет координат вершин двух любых (из перечисленных) объектов так, чтобы один из них превращался в другой (морфинг).
//*/

//#include <GL/glut.h>
//#include <GL/freeglut.h>

//static const GLint WINDOW_WIDTH = 512, WINDOW_HEIGHT = 512;

//void displayMe(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_POLYGON);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3f(0.5, 0.0, 0.0);
//    glVertex3f(0.5, 0.5, 0.0);
//    glVertex3f(0.0, 0.5, 0.0);
//    glEnd();
//    glFlush();
//}

//void display(void)
//{

//}


//void drawCylinder(void)
//{
//    // Очистка буфера кадра
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    // Перенос системы координат, связанной с объектом, на 0.01
//    //    glTranslated(-0.5, -0.5, -0.5);
//    glRotated(90, 1, 0, 0);
//    glRotated(10, 0, 1, 0);
//    glScaled(0.3, 0.3, 0.3);
//    glTranslated(0, 0, -1);
//    // Рисование в начале координат, связанных с объектом, сферы
//    // радиусом 1, окрашенной в красный цвет
//    glColor3d(5, 5, 0);
////    glutSolidCylinder(1, 3, 15, 15);
//    glutWireCylinder(1, 3, 15, 15);

//    // Копирование содержимого буфера кадра на экран
//    glutSwapBuffers();
//}

//void drawSphere(void)
//{
//    // Очистка буфера кадра
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    // Перенос системы координат, связанной с объектом, на 0.01
//    glTranslated(0, 0, 0);
//    // Рисование в начале координат, связанных с объектом, сферы
//    // радиусом 1, окрашенной в красный цвет
//    glColor3d(10, 1, 1);
//    glutWireSphere(1, 32, 32);
////    glut
//    // Копирование содержимого буфера кадра на экран
//    glutSwapBuffers();
//}

//int main1(int argc, char** argv)
//{
//    // init
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA);
//    glutInitWindowSize(800, 800);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Lab1");

//    // logic
//    glutDisplayFunc(drawCylinder);

//    //params
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHT0); // Включение нулевого источника света

//    // loop
//    glutMainLoop();

//    return 0;
//}
