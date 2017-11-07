
/*
 *  Программа демонстрирует модель освещения OpenGL
 *  Объектам назначаются разные материалы. 
 *  В сцене присутствует источник света.
 */

#include <GL/glut.h>
#include <stdlib.h>

/* параметры материала тора */
float mat1_dif[]={0.8f,0.8f,0.0f};
float mat1_amb[]= {0.2f,0.2f,0.2f};
float mat1_spec[]={0.6f,0.6f,0.6f};
float mat1_shininess=0.5f*128;

/* параметры материала конуса */
float mat2_dif[]={0.0f,0.0f,0.8f};
float mat2_amb[]= {0.2f,0.2f,0.2f};
float mat2_spec[]={0.6f,0.6f,0.6f};
float mat2_shininess=0.7f*128;

/* параметры материала шара */
float mat3_dif[]={0.9f,0.2f,0.0f};
float mat3_amb[]= {0.2f,0.2f,0.2f};
float mat3_spec[]={0.6f,0.6f,0.6f};
float mat3_shininess=0.1f*128;

/*  Инициализируем параметры материалов и источника света
 */
void init (void)
{
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

   /* устанавливаем параметры источника света */
   glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv (GL_LIGHT0, GL_POSITION, light_position);
   
   /* включаем освещение и источник света */
   glEnable (GL_LIGHTING);
   glEnable (GL_LIGHT0);
   /* включаем z-буфер */
   glEnable(GL_DEPTH_TEST);
   
}

/* Функция вызывается при необходимости перерисовки изображения.
 * В ней осуществляется весь вывод геометрии.
 */
void display (void)
{
   /* очищаем буфер кадра и буфер глубины */
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix ();
   glRotatef (20.0, 1.0, 0.0, 0.0);

   /* отображаем тор */
   glMaterialfv (GL_FRONT,GL_AMBIENT,mat1_amb);
   glMaterialfv (GL_FRONT,GL_DIFFUSE,mat1_dif);
   glMaterialfv (GL_FRONT,GL_SPECULAR,mat1_spec);
   glMaterialf  (GL_FRONT,GL_SHININESS,mat1_shininess);
   
   glPushMatrix ();
   glTranslatef (-0.75, 0.5, 0.0); 
   glRotatef (90.0, 1.0, 0.0, 0.0);
   glutSolidTorus (0.275, 0.85, 15, 15);
   glPopMatrix ();

   /* отображаем конус */
   glMaterialfv (GL_FRONT,GL_AMBIENT,mat2_amb);
   glMaterialfv (GL_FRONT,GL_DIFFUSE,mat2_dif);
   glMaterialfv (GL_FRONT,GL_SPECULAR,mat2_spec);
   glMaterialf  (GL_FRONT,GL_SHININESS,mat2_shininess);

   glPushMatrix ();
   glTranslatef (-0.75, -0.5, 0.0); 
   glRotatef (270.0, 1.0, 0.0, 0.0);
   glutSolidCone (1.0, 2.0, 15, 15);
   glPopMatrix ();

   /* отображаем шар */
   glMaterialfv (GL_FRONT,GL_AMBIENT,mat3_amb);
   glMaterialfv (GL_FRONT,GL_DIFFUSE,mat3_dif);
   glMaterialfv (GL_FRONT,GL_SPECULAR,mat3_spec);
   glMaterialf  (GL_FRONT,GL_SHININESS,mat3_shininess);

   glPushMatrix ();
   glTranslatef (0.75, 0.0, -1.0); 
   glutSolidSphere (1.0, 15, 15);
   glPopMatrix ();

   glPopMatrix ();
   /* выводим сцену на экран */
   glFlush ();
}

/* Вызывается при изменении пользователем размеров окна.
 */
void reshape(int w, int h)
{
   /* устанавливаем размер области вывода равным размеру окна */
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   
   /* задаем матрицу проекции с учетом размеров окна */
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
 
   gluPerspective(
	   40.0, /* угол зрения в градусах */
	   (GLfloat)w/h, /* коэффициент сжатия окна*/
	   1,100.0);  /* расстояние до плоскостей отсечения по глубине*/
   glMatrixMode (GL_MODELVIEW);
 
   glLoadIdentity ();
   gluLookAt(
	   0.0f,0.0f,8.0f, /* положение камеры */
	   0.0f,0.0f,0.0f, /* центр сцены */
	   0.0f,1.0f,0.0f); /* положительное направление оси y*/ 
   
}

/* Вызывается при нажатии клавиши на клавиатуре
 */
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27: /* escape */
         exit(0);
         break;
   }
}

/*  Главный цикл приложения
 *  Создается окно, устанавливается режим 
 *  экрана с буфером глубины
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutCreateWindow (argv[0]);
   init ();
   glutReshapeFunc (reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0; 
}
