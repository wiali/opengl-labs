#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>       
#include "GLUT/glut.h"
#include "test_lib.h"

float perspective =45;

/* pour stocker la modelview, matrice de positionnement de la scène */
GLfloat modelview[16];

/* matrices de positionnement*/
GLfloat cubeModelview[16];
GLfloat sphereModelview[16];


/* Variable pour les déplacements du point de vue */
GLboolean mouv = GL_FALSE, scaling= GL_FALSE;

// Trackball
static GLfloat quaternion_precedent[4];
static GLfloat quaternion_courant[4];

// Propriétés de la fenêtre
GLint width=512, height=512, posx=80, posy=20;


// la sphere
typedef struct sphere {
	double color[3];
	double rayon;
	double force[3];
	double pos[3];
	double vit[3];
} Sphere;

static Sphere sp1;


// Un point 
typedef struct point {
	double x;
	double y;
	double z;
} Point;

static Point point1;
static Point point2;

void Init(int largeur, int hauteur);
void display_cube(void);
void display_boule(void);
void recalcModelView(void);
void getModelViewPosition(GLfloat *x, GLfloat *ty, GLfloat *z);
void printModelviewMatrix(void);
double Distance_signee(Point P, Point P1, Point P2, Point P3);

void Init(int largeur, int hauteur)
{

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);		// background a la couleur blanche
 // glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glEnable(GL_NORMALIZE);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// matrice identité


  glMatrixMode(GL_MODELVIEW);

  // Position du cube, initialise sa matrice de positionnement
  glPushMatrix();
  glLoadIdentity();
  glRotatef(45.0,0.0, 0.0, 1.0);
  glGetFloatv(GL_MODELVIEW_MATRIX, cubeModelview);
  glPopMatrix();

  // Initialisation de la sphere
  sp1.rayon=0.2;
  sp1.color[0]=0.0;//valeur R
  sp1.color[1]=1.0;//valeur G
  sp1.color[2]=1.0;//valeur B
  sp1.pos[0]=0.0;//position du centre de la boule en X
  sp1.pos[1]=0.0;//position du centre de la boule en Y
  sp1.pos[2]=0.0;//position du centre de la boule en Z
  point1.x=0.0;//position du point 
  point1.y=0.0;
  point1.z=0.0;
  sp1.vit[0]=0.0;
  sp1.vit[1]=-2;
  sp1.vit[2]=0.0;
  
  // Position de la sphere, initialise sa matrice de positionnement.
  glPushMatrix();	
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, sphereModelview);
  glPopMatrix();

  /* position de la scene ( cube + sphere) */
  glTranslatef(0.0, -1, -12);


  /* Pour la boule virtuelle, il est impératif de sauvegarder une première fois
   la modelview du départ, car elle définit le centre du repère de la scène, soit
  le centre de la boule virtuelle.*/
  trackball(quaternion_courant, 0.0f, 0.0f, 0.0f, 0.0f); // Rotation nulle. Set à initialiser la rotation 0
  glPushMatrix();
  recalcModelView(); // initialize the modelview matrix 
}



int translateModelview(float distx, float disty, float distz, GLfloat *modelview) {
/* Effectue une translation le long de l'axe Z de la modelview passée en
   paramètre. A la sortie, la modelview est translatée */

	//glTranslatef(distx, disty, distz);
  glPushMatrix();						// Pour ne pas affecter la matrice courante
	  glLoadMatrixf(modelview);			// Matrice courante = la matrice passée en paramètre
	  glTranslatef(distx, disty, distz);		// On translate localement en Z le long de l'axe Z de
										//     la matrice courante. La matrice courante est affectée

	  glGetFloatv(GL_MODELVIEW_MATRIX, modelview);	// On stocke dans modelview la matrice courante
  glPopMatrix();

  return 0;
}



/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int largeur, int hauteur)
{
  if (hauteur==0)// evite la division par zero si la fenetre est trop petite
    hauteur=1;

  glViewport(0, 0, largeur, hauteur);		

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(perspective,(GLfloat)largeur/(GLfloat)hauteur,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);

  width = largeur; height = hauteur;
}

/*---------------------------*/
void recalcModelView(void) {
/*---------------------------*/
/* Utilisée pour le calcul de la rotation de la scène avec la boule virtuelle */
  GLfloat m[4][4];
  
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();				// Matrice courante = matrice sur le haut de la pile. Normalement, 
								// la matrice initiale qui contient le centre de la boule virtuelle

  glPushMatrix();			    // On en met une copie sur le haut de la pile. On ne doit jamais perdre la matrice
								// du début !

  build_rotmatrix(m, quaternion_courant);	// quaternion_courant contient la rotation globale somme de toutes les micro-rotations sur la sphere
								// On transforme le quaternion en matrice de rotation

  glMultMatrixf(&m[0][0]);		// On multiplie à gauche la matrice initiale par cette matrice de rotation. Fait une
								// rotation locale

}



/* Calcul de l'équation d'un plan passant par trois points*/
void Equation_plan(double *eq, Point P1, Point P2, Point P3){

	eq[0]=P2.y*P3.z-P2.y*P1.z-P1.y*P3.z-P3.y*P2.z+P3.y*P1.z+P1.y*P2.z;
	eq[1]=-P3.x*P1.z+P2.x*P1.z+P1.x*P3.z+P3.x*P2.z-P1.x*P2.z-P2.x*P3.z;
	eq[2]=P2.x*P3.y-P2.x*P1.y-P1.x*P3.y-P3.x*P2.y+P1.x*P2.y+P3.x*P1.y;
	eq[3]=-P1.x*P2.y*P3.z+P1.x*P3.y*P2.z+P2.x*P1.y*P3.z-P3.x*P1.y*P2.z-P2.x*P3.y*P1.z+P3.x*P2.y*P1.z;
}


/* Calcul de la distance d'un point a un plan passant par trois points donnés*/
double Distance_carre(Point P, Point P1, Point P2, Point P3){
	double eq[4];
	double a,b,c,d;

	Equation_plan(eq,P1,P2,P3);
	a=eq[0];
	b=eq[1];
	c=eq[2];
	d=eq[3];
	
	return (pow(a*P.x+b*P.y+c*P.z+d,2) / (a*a+b*b+c*c));
}


/* Calcul de la distance d'un point a un plan passant par trois points donnés*/
double Distance_signee(Point P, Point P1, Point P2, Point P3){
	double eq[4];
	double a,b,c,d,dist,sign;

	Equation_plan(eq,P1,P2,P3);
	a=eq[0];
	b=eq[1];
	c=eq[2];
	d=eq[3];

	if (fabs(a*P.x+b*P.y+c*P.z+d) > 0.00000000001) {
		dist = pow(a*P.x+b*P.y+c*P.z+d,2) / (a*a+b*b+c*c);
		sign = -((a*P.x+b*P.y+c*P.z+d) / fabs(a*P.x+b*P.y+c*P.z+d));
		return (sqrt(dist)*sign);
	}
	else
		return 0.0;
}


/* inverse un modelview */
void InvertModelview(GLfloat *m1,GLfloat *b) {

	b[0] = m1[0];
  	b[1] = m1[4];
	b[2] = m1[8];
	b[4] = m1[1];
	b[5] = m1[5];
	b[6] = m1[9];
	b[8] = m1[2];
	b[9] = m1[6];
	b[10] = m1[10];
  
	b[12] = -( m1[12] * b[0] + m1[13] * b[4] + m1[14] * b[8] );
	b[13] = -( m1[12] * b[1] + m1[13] * b[5] + m1[14] * b[9] );
	b[14] = -( m1[12] * b[2] + m1[13] * b[6] + m1[14] * b[10] );
  
	b[3] = b[7] = b[11] = 0.0f; 
	b[15] = 1.0f;
}


/* multiplie un point par une modelview */
void MultModelview(GLfloat *m1,Point p, Point *b) {
	double temp;

	b->x = p.x*m1[0]+p.y*m1[1]+p.z*m1[2]+m1[3];
  	b->y = p.x*m1[4]+p.y*m1[5]+p.z*m1[6]+m1[7];
	b->z = p.x*m1[8]+p.y*m1[9]+p.z*m1[10]+m1[11];
	temp = p.x*m1[12]+p.y*m1[13]+p.z*m1[14]+m1[15];

	b->x /= temp;
	b->y /= temp;
	b->z /= temp;

}


/* produit scalaire de deux vecteurs */
double MultVector(Point p1,Point p2) {
	double temp = 0.0;

	temp += p1.x*p2.x;
	temp += p1.y*p2.y;
	temp += p1.z*p2.z;

	return temp;
}

/* Calcule la distance au carre entre deux points */
double DiffPoint(Point p1,Point p2) {

	Point temp;

	temp.x = p1.x-p2.x;
	temp.y = p1.y-p2.y;
	temp.z = p1.z-p2.z;

	return MultVector(temp,temp);
}

/*Gestion des collisions entre la sphere et les faces du cube */
int  Collisions(double *next_vit, Point *next_point){

	int flag = 0;
	Point P1,P2,P3,P4,P5,P6,x,v_temp,vx;
	Point normale;
	double comp_normale;
	GLfloat	cubeModelviewInv[16];
	double attenuation = 0.8;
	double seuil = 0.5;
	double dist;
	/* sommets du cube dans son propre repère*/
	P1.x=-1.0;P1.y=-1.0;P1.z=1.0;
	P2.x=-1.0;P2.y=-1.0;P2.z=-1.0;
	P3.x=1.0;P3.y=-1.0;P3.z=-1.0;
	P4.x=1.0;P4.y=1.0;P4.z=-1.0;
	P5.x=1.0;P5.y=1.0;P5.z=1.0;
	P6.x=-1.0;P6.y=1.0;P6.z=1.0;

	/* on transforme next_point et old_vit dans le repère du cube */
	InvertModelview(cubeModelview,cubeModelviewInv);
	MultModelview(cubeModelviewInv,*next_point,&x);


	v_temp.x=next_vit[0];
	v_temp.y=next_vit[1];
	v_temp.z=next_vit[2];
	MultModelview(cubeModelviewInv,v_temp,&vx);
	
	/* on teste sur les six faces définient par : 
	{P1, P2, P3}
	{P4, P5, P6}
	{P2, P1, P6}
	{P5, P4, P3}
	{P1, P6, P5}
	{P4, P3, P2} */


		if (!((dist=Distance_signee(x, P1, P2, P3)) > sp1.rayon)){
			flag = 1;
			normale.x=0.0f;
			normale.y=1.0f;
			normale.z=0.0f;
		}
		else 
			if (!((dist=Distance_signee(x, P4, P5, P6)) < -sp1.rayon)) {
				flag = 1;
				normale.x=0.0f;
				normale.y=-1.0f;
				normale.z=0.0f;
			}
			else 
				if (!((dist=Distance_signee(x, P2, P1, P6)) > sp1.rayon)) {
					flag = 1;
					normale.x=1.0f;
					normale.y=0.0f;
					normale.z=0.0f;
				}
				else 
					if (!((dist=Distance_signee(x, P5, P4, P3)) < -sp1.rayon)) {
						flag = 1;
						normale.x=-1.0f;
						normale.y=0.0f;
						normale.z=0.0f;
					}
					else 
						if (!((dist=Distance_signee(x, P4, P3, P2)) > sp1.rayon)) {
							flag = 1;
							normale.x=0.0f;
							normale.y=0.0f;
							normale.z=1.0f;
						}
						else 
							if (!((dist=Distance_signee(x, P1, P6, P5)) < -sp1.rayon)) {
								flag = 1;
								normale.x=0.0f;
								normale.y=0.0f;
								normale.z=-1.0f;
						}

	if (flag == 1){
		comp_normale = MultVector(normale,vx);
		/* calcul nouvelle vitesse dans le repere du cube*/
		vx.x -= 2*comp_normale*normale.x;
		vx.y -= 2*comp_normale*normale.y;
		vx.z -= 2*comp_normale*normale.z;

		/* expression de la nouvelle vitesse dans le repere du monde */
		MultModelview(cubeModelview,vx,&v_temp);
		next_vit[0] = v_temp.x;
		next_vit[1] = v_temp.y;
		next_vit[2] = v_temp.z;
		
	}

	return flag;
}



void Simulation(int r){

	double next_vit[3];
	double next_pos[3];
	Point next_point;
	int i, choc;
	double dt = 0.08;
	/* seuil à utiliser losque l'on ne fait pas la symetrie dans Collisions */
	double seuil = 0.005; /* pour cube incliné */


	/* Calcul nouvelle vitesse et nouvelle position */
	for (i=0; i<3;i++){
		next_vit[i]=sp1.vit[i];//gravite[i]*dt;
		next_pos[i]=sp1.pos[i]+dt*next_vit[i]+(dt*dt)/2.0;//*gravite[i];
	}

	next_point.x=next_pos[0];
	next_point.y=next_pos[1];
	next_point.z=next_pos[2];

	choc = Collisions(next_vit,&next_point);
	


	if ( choc == 1){
                 //choc -> changement de la vitesse et de la position puis translation
		{ 
		next_pos[0]=sp1.pos[0]+dt*next_vit[0]+(dt*dt)/2.0;
		next_pos[1]=sp1.pos[1]+dt*next_vit[1]+(dt*dt)/2.0;
		next_pos[2]=sp1.pos[2]+dt*next_vit[2]+(dt*dt)/2.0;
		next_point.x=next_pos[0];
		next_point.y=next_pos[1];
		next_point.z=next_pos[2];
		point2.x=next_point.x-sp1.pos[0];
		point2.y=next_point.y-sp1.pos[1];
		point2.z=next_point.z-sp1.pos[2];
		}
		if (DiffPoint(point1,point2) > seuil) { 
			translateModelview(next_point.x-sp1.pos[0],next_point.y-sp1.pos[1],next_point.z-sp1.pos[2],sphereModelview);
			sp1.pos[0]=next_point.x;
			sp1.pos[1]=next_point.y;
			sp1.pos[2]=next_point.z;
			sp1.vit[0]=next_vit[0];
			sp1.vit[1]=next_vit[1];
			sp1.vit[2]=next_vit[2];
			point1.x=point2.x;
			point1.y=point2.y;
			point1.z=point2.z;
		}
	}
	else {

		translateModelview(next_point.x-sp1.pos[0],next_point.y-sp1.pos[1],next_point.z-sp1.pos[2],sphereModelview);
		sp1.pos[0]=next_point.x;
		sp1.pos[1]=next_point.y;
		sp1.pos[2]=next_point.z;
		sp1.vit[0]=next_vit[0];
		sp1.vit[1]=next_vit[1];
		sp1.vit[2]=next_vit[2];
	}

	glutTimerFunc(60, &Simulation,0);
}



void Display() {

	// On s'occupe d'abord de positionner toute la scène dans l'espace, en fonction de la Boule virtuelle
	if(mouv)
		recalcModelView();

	// On efface la fenêtre
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// éclairage ambient
	{
		GLfloat lmodel_ambient[] = {2., 2., 2., 1. };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	}

	display_boule();
	glRotated(0.5,1,0,0);
	glRotated(0.5,0,1,0);
	glRotated(0.5,0,0,1);
	display_cube();

	glutSwapBuffers();
}



void display_boule() 
{

	glPushMatrix();
	
	glMultMatrixf(sphereModelview);

	//glColorMaterial(GL_FRONT, GL_AMBIENT);
	//glEnable(GL_COLOR_MATERIAL);
	glColor3f(sp1.color[0],sp1.color[1],sp1.color[2]);

	glutSolidSphere(sp1.rayon, 70., 70.);
	//glDisable(GL_COLOR_MATERIAL);

	glPopMatrix();
}


void display_cube() {
	glClearColor(0, 0, 0, 0);
     
     	glPushMatrix();
	
	glMultMatrixf(cubeModelview);
			/*{
			GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };
			GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
			GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			}*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				
	glBegin(GL_QUADS);// trace le quadrilatère cube
		/* face 1 */
	glColor4f(0.16, 0.85, 1.0,0.5);
	glNormal3f(0,0,1);
	glVertex3i(1, 1, 1);		
	glVertex3i(1, -1, 1);
	glVertex3i(-1, -1, 1);
	glVertex3i(-1, 1, 1);
	
	/* face 2 */
	glColor4f(0.16, 0.82, 1.0,0.5);
	glNormal3f(0,0,-1);
	glVertex3i(1, 1, -1);  
	glVertex3i(1, -1, -1);
	glVertex3i(-1, -1, -1);
	glVertex3i(-1, 1, -1);
	
	/*face 3*/
	glColor4f(0.15, 0.80,1.0,0.5);
	glNormal3f(1,0,0);
	glVertex3i(1, 1, 1);
	glVertex3i(1, -1, 1);
	glVertex3i(1, -1, -1);
	glVertex3i(1, 1, -1);
	
	/*face 4*/
	glColor4f(0.165, 0.78, 1.0,0.5);
	glNormal3f(-1,0,0);
	glVertex3i(-1, 1, 1); 
	glVertex3i(-1, -1, 1);
	glVertex3i(-1, -1, -1);
	glVertex3i(-1, 1, -1);

	/*face 5 , du dessus*/
	glColor4f(0.15, 0.76, 1.0,0.5);
	glNormal3f(0,1,0);
	glVertex3i(-1, 1, -1); 
	glVertex3i(-1, 1, 1);
	glVertex3i(1, 1, 1);
	glVertex3i(1, 1, -1);

	/*face 6 , en dessous*/

	glColor4f(0.16, 0.74, 1.0,0.5);
	glNormal3f(0,-1,0);       //face 6 , celle den dessous
	glVertex3i(-1, -1, -1);
	glVertex3i(-1, -1, 1);
	glVertex3i(1, -1, 1);
	glVertex3i(1, -1, -1);

	glEnd();

	glDisable(GL_BLEND);
	glPopMatrix();
	glutSwapBuffers();//échange des buffers
	glutPostRedisplay();
}



/*gestion de la touche clavier */
 void key (unsigned char key, int x, int y) 
{
	;
	switch (key)
	{
	case 27: 
		printf("\nFermeture en cours...\n");
		exit(0); 
		break;

	
	}
}


int main(int argc, char **argv) 
{  
glutInit(&argc, argv);  
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
glutInitWindowSize(950, 650);//taille de la fenetre
glutInitWindowPosition(150,150);//position
glutCreateWindow("Projet screensaver");  //création fenêtre
glutFullScreen();//affichage plein ecran
glutDisplayFunc(Display);  
glutTimerFunc(60, &Simulation,0);
//glutIdleFunc(Display);// NULL);
glutReshapeFunc(ReSizeGLScene);
glutKeyboardFunc(key);
Init(width, height);//initialisation de la fenetre
glutMainLoop();  

return (0);
}
