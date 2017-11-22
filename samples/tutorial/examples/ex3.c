#include <GL/glut.h>
// #include <GL/glaux.h>
#include <GL/freeglut.h>
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

/*���������� ������� � ���������, ���������� ������� a,b,c */
void getnorm (float a[3],float b[3],float c[3],float *n)
{
 float mult=0,sqr;
 int i,j;
 n[0]=(b[1]-a[1])*(c[2]-a[2])-(b[2]-a[2])*(c[1]-a[1]);
 n[1]=(c[0]-a[0])*(b[2]-a[2])-(b[0]-a[0])*(c[2]-a[2]);
 n[2]=(b[0]-a[0])*(c[1]-a[1])-(c[0]-a[0])*(b[1]-a[1]);
 /*����������� ������� ����������� �������: �� ����� (0,0,0) */
 for (i=0;i<3;i++) mult+=a[i]*n[i];
 if (mult<0) for (j=0;j<3;j++) n[j]=-n[j];
}

/*���������� ��������� ������ ��������� */
void InitVertexTetr()
{
 float alpha=0;
 int i;
 TetrVertex[0][0]=0;TetrVertex[0][1]=1.3;TetrVertex[0][2]=0;
 /*���������� ��������� ��������� ���������*/
 for (i=1;i<4;i++)
 {
  TetrVertex[i][0]=0.94*cos(alpha);
  TetrVertex[i][1]=0;
  TetrVertex[i][2]=0.94*sin(alpha);
  alpha+=120.0*3.14/180.0;
 }
}

/*���������� �������� ������ ���������*/
void InitNormsTetr()
{
 getnorm(TetrVertex[0],TetrVertex[1],TetrVertex[2],TetrNormal[0]);
 getnorm(TetrVertex[0],TetrVertex[2],TetrVertex[3],TetrNormal[1]);
 getnorm(TetrVertex[0],TetrVertex[3],TetrVertex[1],TetrNormal[2]);
 getnorm(TetrVertex[1],TetrVertex[2],TetrVertex[3],TetrNormal[3]);
}

/*�������� ������ ���������� ���������*/
void MakeTetrList()
{
	int i;
 glNewList (TETR_LIST,GL_COMPILE);
  /*������� ������ ���������*/
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
 /*���������� �������� (������), �������������� ����������� ��� z
   ������ � ������ ��������� ������ ������� ���������, ���������
   ������,��������� ���-����� ��������� ������ � ����� ��� z
   ��� ���� ������� ��������� �������� ��������� � ��������� z=0*/
 gluCylinder (QuadrObj,RingRad,RingRad,RingHeight,30,2);
}

void TextureInit()
{
 char strFile[]="texture.bmp";
 AUX_RGBImageRec *pImage;

 /*������������ � *.bmp �� �����*/
 glPixelStorei(GL_UNPACK_ALIGNMENT,1);
 /*�������� �������������� ��� ��������*/
 glGenTextures(1,&TexId);
 /*�������� ����������� � ������*/
 pImage = auxDIBImageLoad(strFile);

 /*������ �������� ������� ��������*/
 glBindTexture (GL_TEXTURE_2D,TexId);
 /*�������� ������� ����������� � ������������� ��������*/
 gluBuild2DMipmaps(GL_TEXTURE_2D,3,pImage->sizeX, pImage->sizeY,
                   GL_RGB,GL_UNSIGNED_BYTE,pImage->data);
 /*���������� ��������� ���� �������� �� quadric-�������*/
 gluQuadricTexture(QuadrObj, GL_TRUE);
 /*������� ���������� ��������*/
 /*������ ����������� �� ��������������� ���� s � t*/
 glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
 glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
 /*�� ������������ ������������ ��� ������ ����� �� ��������*/
 glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
 glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
 /*��������� �������� � �������� �������*/
 glTexEnvi (GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}


void Init(void)
{
 InitVertexTetr();
 InitNormsTetr();
 MakeTetrList();
 /*����������� ������� ���������*/
 glMaterialfv (GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
 glMaterialfv (GL_FRONT_AND_BACK,GL_SPECULAR,mat_spec);
 glMaterialf  (GL_FRONT,GL_SHININESS,shininess);
 /*����������� ������� ���������*/
 glLightfv(GL_LIGHT0, GL_DIFFUSE, light_col);
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 /*��������� �������� ��������� ����� � ������������*/
 glEnable(GL_DEPTH_TEST);
 /*��������� ������������ ��������*/
 glEnable(GL_NORMALIZE);
 /*��������� �������� ���������� ������ ������ ���������� ���������*/
 glEnable(GL_COLOR_MATERIAL);
 glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
 /*�������� ��������� �� quadric-������ ��� ���������� �����*/
 QuadrObj=gluNewQuadric();
 /*����������� ������� ��������*/
 TextureInit();
 /*������� ������������� ��������*/
 glMatrixMode(GL_PROJECTION);
 gluPerspective(89.0,1.0,0.5,100.0);
 /*����� ����� ����������� ������ �������������� �������� �����*/
 glMatrixMode(GL_MODELVIEW);
}

void DrawFigures(void)
{
 /*��������� ������ ��������� ��������*/
 glEnable(GL_TEXTURE_2D);
 /*������ ���� ���������� ��������� ��� �����*/
 glColor3fv(mat_diff1);
 /*����� �� ��������� ������������ � ���������� �������� ���������
   ��������� �������*/
 glLoadIdentity();
 /*���������� ����� ����������*/
 gluLookAt(0.0, 0.0, 2.5,0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 /*��������� ������� �������, ��� ��� ������ ����� �����������
  ������� �����*/
 glPushMatrix();
  /*���������� ��������� ��������� �� ����� ���� (��� �������, ���
    �������� ���������� ������� ������� �� ������� �������� � �����
    �������� ����� ��������)*/
  glRotatef (-CurAng,1,1,0);
  glRotatef (CurAng,1,0,0);
  /*��� ��������� ����� ������ �� ��� ���� ������������� ��������,
   ������� ������� ��������� ������� �������, ����� ���������������*/
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
 /*��������������� ������� ��� ��������� ��������*/
 glPopMatrix();
/*��������� ����� ��������� ��������*/
 glDisable(GL_TEXTURE_2D);
 /*�������� ��������*/
 glRotatef (CurAng,1,0,0);
 glRotatef (CurAng/2,1,0,1);
 /*����� �������� �������� ������ ������, ��� ���� �������� ���� ��
   ��� oz*/
 glTranslatef (0,-0.33,0);
 /*������ ���� ���������� ��������� ��� ���������*/
 glColor3fv(mat_diff2);
 /*�������� ���������� ���������*/
 glCallList(TETR_LIST);
}

void Display(void)
{
 /*������������� (�������) �������� ������ ����� � �������*/
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 /*���������� ��������*/
 DrawFigures();
 /*������������ ������� �����*/
 glutSwapBuffers();
}

void Redraw(void)
{
 /*���������� �������� ���� ��������*/
 CurAng+=1;
 /*������ ��� ������ ��������� �������� ����������� (��� ����������)*/
 glutPostRedisplay();
}

int main(int argc, char **argv)
{
  /*������������� ������� ���������� GLUT*/
  glutInit(&argc, argv);
  /*������� ������ � ������� ������������, ������������� ����� �
    ������� RGB, ������������� ������ �������*/
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  /*�������� ���� ����������*/
  glutCreateWindow("Example of using OpenGL");
  /*����������� ������� ���������� �����������*/
  glutDisplayFunc(Display);
  /*����������� ������� ���������� �����������*/
  glutIdleFunc(Redraw);
  /*������������� ������� OpenGL*/
  Init();
  /*���� ��������� �������*/
  glutMainLoop();
  return 0;
}
