
#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>


GLfloat xlocmodel=0,ylocmodel=0,zlocmodel=0;
GLint tournex=1,tourney=0,tournez=0;
typedef struct
{
  float x;
  float y;
  float z;
  float r;
  float g;
  float b;
} point;

//tableau de point contenant les 8 sommets du cube
point p[8]={
    {-0.5,-0.5, 0.5,1.0,1.0,1.0},
    {-0.5, 0.5, 0.5,1.0,1.0,1.0},
    { 0.5, 0.5, 0.5,1.0,1.0,1.0},
    { 0.5,-0.5, 0.5,1.0,1.0,1.0},
    {-0.5,-0.5,-0.5,1.0,1.0,1.0},
    {-0.5, 0.5,-0.5,1.0,1.0,1.0},
    { 0.5, 0.5,-0.5,1.0,1.0,1.0},
    { 0.5,-0.5,-0.5,1.0,1.0,1.0}};
    
//stockage des 6 faces  
int f[6][4]={
  {0,1,2,3},
  {3,2,6,7},
  {4,5,6,7},
  {0,1,5,4},
  {1,5,6,2},
  {0,4,7,3}};


//vecteur normale face
float NFace [6][3] ={
      {1,0,0},
      {-1,0,0}
      
      
      
      
      };
char presse;
int anglex,angley,x,y,xold,yold;

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void reshape(int x,int y)
{
     
     /*void glViewport(GLint x,GLint y,GLsizei l,GLsizei h)
     D�finit le rectangle de pixels dans la fen�tre d'affichage
dans lequel l'image calcul�e sera affich�e.*/
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else 
    glViewport((x-y)/2,0,y,y);
}

void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold); 
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }
    
    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }

void affichage()
{
  int i,j;
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  glRotatef(-angley,1.0,0.0,0.0);
  glRotatef(-anglex,0.0,1.0,0.0);
  /* Dessin du cube */
  for (i=0;i<6;i++)
    {
      glBegin(GL_POLYGON);
      for (j=0;j<4;j++)
	{
	  glColor3f(p[f[i][j]].r,p[f[i][j]].g,p[f[i][j]].b);
	  glVertex3f(p[f[i][j]].x,p[f[i][j]].y,p[f[i][j]].z);
	}
      glEnd();
    }
    glPushMatrix();
    glTranslatef(xlocmodel,ylocmodel,zlocmodel);
   glutWireSphere(0.1, 20, 16);
    glPopMatrix(); 
  glFlush();
  
  /* On echange les buffers */
  glutSwapBuffers();
}

void boucle() {
     
     if(anglex<90&&tournex) {
     anglex=anglex+1;
    
     }
     else {
           tournex=0;
           tourney=1;
          }
     if(angley<90&&tourney) {
     angley=angley+1;
     }
     else {
     tourney=0;
     tournez=1;
     
     }
     //angley+=5;
    
   //  printf("anglex %f\n",anglex);
     xlocmodel=xlocmodel+0.001;
    glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
     
     }

int main(int argc,char **argv)
{
   // fprintf(stderr,"Bijour Bijour\n");
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(250,250);
  glutCreateWindow("PROJET 3D");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);
  glutIdleFunc(boucle);
  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}


