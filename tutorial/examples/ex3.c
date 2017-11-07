#include <GL\glut.h>
#include <gl\glaux.h>
#include <math.h>

#define TETR_LIST 1 

GLfloat light_col[] = {1,1,1};
float mat_diff1[]={0.8,0.8,0.8};
float mat_diff2[]={0.0,0.0,0.9};
float mat_amb[]= {0.2,0.2,0.2};
float mat_spec[]={0.6,0.6,0.6};
float shininess=0.7*128, CurAng=0, RingRad=1, RingHeight=0.1;
GLUquadricObj* QuadrObj; 
GLuint TexId;
GLfloat TetrVertex[4][3], TetrNormal[4][3];

/*Вычисление нормали к плоскости, задаваемой точками a,b,c */
void getnorm (float a[3],float b[3],float c[3],float *n)
{
 float mult=0,sqr;
 int i,j;
 n[0]=(b[1]-a[1])*(c[2]-a[2])-(b[2]-a[2])*(c[1]-a[1]);
 n[1]=(c[0]-a[0])*(b[2]-a[2])-(b[0]-a[0])*(c[2]-a[2]);
 n[2]=(b[0]-a[0])*(c[1]-a[1])-(c[0]-a[0])*(b[1]-a[1]);
 /*Определение нужного направления нормали: от точки (0,0,0) */
 for (i=0;i<3;i++) mult+=a[i]*n[i];
 if (mult<0) for (j=0;j<3;j++) n[j]=-n[j]; 
}

/*Вычисление координат вершин тетраэдра */
void InitVertexTetr()
{
 float alpha=0;
 int i;
 TetrVertex[0][0]=0;TetrVertex[0][1]=1.3;TetrVertex[0][2]=0;
 /*Вычисление координат основания тетраэдра*/
 for (i=1;i<4;i++)
 {
  TetrVertex[i][0]=0.94*cos(alpha);
  TetrVertex[i][1]=0;
  TetrVertex[i][2]=0.94*sin(alpha);
  alpha+=120.0*3.14/180.0;
 }
}

/*Вычисление нормалей сторон тетраэдра*/
void InitNormsTetr()
{
 getnorm(TetrVertex[0],TetrVertex[1],TetrVertex[2],TetrNormal[0]);
 getnorm(TetrVertex[0],TetrVertex[2],TetrVertex[3],TetrNormal[1]);
 getnorm(TetrVertex[0],TetrVertex[3],TetrVertex[1],TetrNormal[2]);
 getnorm(TetrVertex[1],TetrVertex[2],TetrVertex[3],TetrNormal[3]);
}

/*Создание списка построения тетраэдра*/
void MakeTetrList()
{
	int i;
 glNewList (TETR_LIST,GL_COMPILE);
  /*Задание сторон тетраэдра*/
  glBegin(GL_TRIANGLES);
   for (i=1;i<4;i++)
   {
    glNormal3fv(TetrNormal[i-1]);
    glVertex3fv(TetrVertex[0]);glVertex3fv(TetrVertex[i]);
    if (i!=3) glVertex3fv(TetrVertex[i+1]);  else glVertex3fv(TetrVertex[1]); 
   }
 glNormal3fv(TetrNormal[3]);
 glVertex3fv(TetrVertex[1]);glVertex3fv(TetrVertex[2]);glVertex3fv(TetrVertex[3]); 
  glEnd();
 glEndList();
}

void DrawRing()
{
 /*Построение цилиндра (кольца), расположенного параллельно оси z
   Второй и третий параметры задают радиусы оснований, четвертый
   высоту,последние два-число разбиений вокруг и вдоль оси z
   При этом дальнее основание цилиндра находится в плоскости z=0*/
 gluCylinder (QuadrObj,RingRad,RingRad,RingHeight,30,2);
}

void TextureInit()
{
 char strFile[]="texture.bmp";
 AUX_RGBImageRec *pImage;

 /*Выравнивание в *.bmp по байту*/
 glPixelStorei(GL_UNPACK_ALIGNMENT,1);
 /*Создание идентификатора для текстуры*/
 glGenTextures(1,&TexId);
 /*Загрузка изображения в память*/
 pImage = auxDIBImageLoad(strFile);
  
 /*Начало описания свойств текстуры*/
 glBindTexture (GL_TEXTURE_2D,TexId);
 /*Создание уровней детализации и инициализация текстуры*/
 gluBuild2DMipmaps(GL_TEXTURE_2D,3,pImage->sizeX, pImage->sizeY,
                   GL_RGB,GL_UNSIGNED_BYTE,pImage->data);
 /*Разрешение наложения этой текстуры на quadric-объекты*/
 gluQuadricTexture(QuadrObj, GL_TRUE);
 /*Задание параметров текстуры*/
 /*Повтор изображения по параметрическим осям s и t*/
 glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
 glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
 /*Не использовать интерполяцию при выборе точки на текстуре*/
 glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
 glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
 /*Совмещать текстуру и материал объекта*/
 glTexEnvi (GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}


void Init(void)
{
 InitVertexTetr(); 
 InitNormsTetr();
 MakeTetrList();
 /*Определение свойств материала*/
 glMaterialfv (GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
 glMaterialfv (GL_FRONT_AND_BACK,GL_SPECULAR,mat_spec);
 glMaterialf  (GL_FRONT,GL_SHININESS,shininess);  
 /*Определение свойств освещения*/
 glLightfv(GL_LIGHT0, GL_DIFFUSE, light_col);
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 /*Проводить удаление невидимых линий и поверхностей*/
 glEnable(GL_DEPTH_TEST);
 /*Проводить нормирование нормалей*/
 glEnable(GL_NORMALIZE);
 /*Материалы объектов отличаются только цветом диффузного отражения*/
 glEnable(GL_COLOR_MATERIAL);
 glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
 /*Создания указателя на quadric-объект для построения колец*/
 QuadrObj=gluNewQuadric();
 /*Определение свойств текстуры*/
 TextureInit();
 /*Задание перспективной проекции*/
 glMatrixMode(GL_PROJECTION);
 gluPerspective(89.0,1.0,0.5,100.0);
 /*Далее будет проводиться только преобразование объектов сцены*/
 glMatrixMode(GL_MODELVIEW);
}

void DrawFigures(void)
{
 /*Включение режима нанесения текстуры*/
 glEnable(GL_TEXTURE_2D);
 /*Задаем цвет диффузного отражения для колец*/
 glColor3fv(mat_diff1);
 /*Чтобы не проводить перемножение с предыдущей матрицей загружаем
   единичную матрицу*/
 glLoadIdentity();
 /*Определяем точку наблюдения*/
 gluLookAt(0.0, 0.0, 2.5,0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
 /*Сохраняем видовую матрицу, так как дальше будет проводиться
  поворот колец*/
 glPushMatrix();
  /*Производим несколько поворотов на новый угол (это быстрее, чем
    умножать предыдущую видовую матрицу на матрицу поворота с фикси
    рованным углом поворота)*/
  glRotatef (-CurAng,1,1,0);
  glRotatef (CurAng,1,0,0);
  /*Для рисования колец каждое из них надо преобразовать отдельно,
   поэтому сначала сохраняем видовую матрицу, затем восстанавливаем*/
  glPushMatrix();
   glTranslatef (0,0,-RingHeight/2);
   DrawRing();
  glPopMatrix();
  glPushMatrix();
   glTranslatef (0,RingHeight/2,0);
   glRotatef (90,1,0,0);
   DrawRing();
  glPopMatrix();
  glPushMatrix();
   glTranslatef (-RingHeight/2,0,0);
   glRotatef (90,0,1,0);
   DrawRing();
  glPopMatrix();
 /*Восстанавливаем матрицу для поворотов тераэдра*/
 glPopMatrix();
/*Выключаем режим наложения текстуры*/
 glDisable(GL_TEXTURE_2D);
 /*Проводим повороты*/
 glRotatef (CurAng,1,0,0);
 glRotatef (CurAng/2,1,0,1);
 /*Чтобы тетраэдр вращался вокруг центра, его надо сдвинуть вниз по
   оси oz*/
 glTranslatef (0,-0.33,0);
 /*Задаем цвет диффузного отражения для тетраэдра*/
 glColor3fv(mat_diff2);
 /*Проводим построение тетраэдра*/
 glCallList(TETR_LIST);
}

void Display(void)
{
 /*Инициализация (очистка) текущего буфера кадра и глубины*/
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 /*Построение объектов*/
 DrawFigures();
 /*Перестановка буферов кадра*/
 glutSwapBuffers();
}

void Redraw(void)
{
 /*Увеличение текущего угла поворота*/
 CurAng+=1;
 /*Сигнал для вызова процедуры создания изображения (для обновления)*/
 glutPostRedisplay();
}

int main(int argc, char **argv)
{
  /*Инициализация функций библиотеки GLUT*/
  glutInit(&argc, argv);
  /*Задание режима с двойной буферизацией, представление цвета в
    формате RGB, использование буфера глубины*/
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  /*Создание окна приложения*/
  glutCreateWindow("Example of using OpenGL");
  /*Регистрация функции построения изображения*/
  glutDisplayFunc(Display);
  /*Регистрация функции обновления изображения*/
  glutIdleFunc(Redraw);
  /*Инициализация функций OpenGL*/
  Init();
  /*Цикл обработки событий*/
  glutMainLoop();
  return 0;
}