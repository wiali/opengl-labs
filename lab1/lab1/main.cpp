/*
Задание 35.

1. Изобразить каркасный цилиндр и каркасную сферу внутри цилиндра. Размеры объектов задать самостоятельно.
2. Совместить центр основания цилиндра и центр сферы.
3. Выполнить перемещение двух объектов на dy=20.
4. Изобразить тор и октаэдр, считая, что вершина октаэдра совпадает с центром тора. Размеры примитивов задать самостоятельно.
5. Наложить текстуры на объекты.
6. Произвести пошаговый пересчет координат вершин двух любых (из перечисленных) объектов так, чтобы один из них превращался в другой (морфинг).
*/


#include <GL/glut.h>

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world :D");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}
