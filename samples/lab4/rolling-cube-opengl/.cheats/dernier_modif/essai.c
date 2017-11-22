#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>       
#include "GLUT/glut.h"

void Display();
void Init();
void myReshape (int largeur, int hauteur);
void motion();
void key (unsigned char, int, int);


float angle_X = 0;
float angle_Y = 0;
float angle_Z = 0;

int rotx = 0;
int roty = 0;
int rotz = 0;

float mouv = 0;
float vitesse = 0.5;
int perspective=60;//eloignement du cube



typedef enum {RIEN, SPHERE, TAILLE} ID_SPHERE;
int texture_boule[TAILLE];

/* Image type - contains height, width, and data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

/* BMP RGB 24 bpp uniquement */
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;
    unsigned long i;
    unsigned short int planes;
    unsigned short int bpp;
    char temp;

    if ((file = fopen(filename, "rb"))==NULL)
    {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    
    fseek(file, 18, SEEK_CUR);

    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }

    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    if ((bpp != 24) && (bpp!=32)) {
        printf("Bpp from %s is not 24 or 32: %u\n", filename, bpp);
        return 0;
    }
    
    size = image->sizeX * image->sizeY * (bpp/8);

    fseek(file, 24, SEEK_CUR);

    image->data = (char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;       
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }

    for (i=0;i<size;i+=(bpp/8)) {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }

    return bpp;
}

/*  fonction pour charger la texture de la sphere */
void LoadTexture(char* filename, int* ident)
 {
  Image im;
  int bpp;

  if(bpp=ImageLoad(filename, &im))
   {
     glGenTextures(1, (GLuint*)ident);
     glBindTexture(GL_TEXTURE_2D, *ident);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     if(bpp==24)
       glTexImage2D(GL_TEXTURE_2D,0,3,
		    im.sizeX,im.sizeY,
		    0,GL_RGB,GL_UNSIGNED_BYTE,im.data);
     else if(bpp==32)
       glTexImage2D(GL_TEXTURE_2D,0,4,
		    im.sizeX,im.sizeY,
		    0,GL_RGBA,GL_UNSIGNED_BYTE,im.data);
   }
 }
 
 
 
/***************************************************************************
  Creation d'une sphere
***************************************************************************/
void CreerSphere(float rayon , int ident)
{
  GLfloat ambient[4] = {0.7, 0.7, 0.7, 1.0};
  GLfloat diffuse[4] = {0.8, 0.8, 0.8, 1.0};
  GLfloat Black[4] = {1.0, 1.0, 0.0, 1.0};
  GLUquadricObj* sph1 = gluNewQuadric();

  glNewList(ident,GL_COMPILE);

  glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, Black);
  glMaterialfv(GL_FRONT, GL_EMISSION, ambient);
  glMaterialf(GL_FRONT,GL_SHININESS,0.0);

  gluQuadricDrawStyle(sph1,GLU_FILL);
  gluQuadricNormals(sph1,GLU_SMOOTH);
  gluQuadricTexture(sph1,GL_TRUE);
  gluSphere(sph1,rayon,70,70);

  glEndList();
}


/***************************************************************************
  Initialisation
***************************************************************************/
void init_texture(void)
{
  glEnable(GL_TEXTURE_2D);
  printf("Chargement des textures....\n");
  LoadTexture("earth.bmp", &texture_boule[SPHERE]);
 }

/***************************************************************************
  Affichage de la Terre
***************************************************************************/
void display_boule()
{
  glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_boule[SPHERE]);
    glCallList(SPHERE);
  glPopMatrix();

}
//ECLAIRAGE
void myinit (void)
{
    GLfloat light_ambient[] = { 0.5, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.1, 0.1, 0.6, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//	light_position is NOT default value	
    GLfloat light_position[] = { 10.0, 10.0, 80.0, 0.0 };

    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDepthFunc(GL_LESS);
    //glEnable(GL_DEPTH_TEST);
}


void Display()
{
	glClearColor(0, 0, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//réinitialisation du z-buffer
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	gluLookAt(4,3,3,0,0,0,0,1,0);


	if(rotx ==1) 
	glRotated(angle_X,1,0,0);
	if(roty ==1)
	glRotated(angle_Y,0,1,0);
	if(rotz ==1)
	glRotated(angle_Z,0,0,1);
	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//calcul des facteurs de transparence du cube

	glBegin(GL_QUADS);		// trace le quadrilatère cube
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

glColor3d(1, 1, 1);// affiche la sphere mais non transparente
display_boule();
	glutSwapBuffers();//échange des buffers
	glutPostRedisplay();
}

void Init()
{

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND); //activation de la transparence (alpha-blending)
	CreerSphere(0.25 , SPHERE);
    	init_texture();
	

}

void myReshape (int largeur, int hauteur)
{
	glViewport(0, 0, largeur, hauteur);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(perspective, (float) largeur/hauteur, 1.0, 10.0);
}

void motion()
{
if ( angle_X <90 ) 
{
	angle_X = angle_X + vitesse;
	rotx=1;
	//angle_X=0;
}

if(angle_Y <90)
{
//angle_X=0;
	angle_Y = angle_Y + vitesse;
	rotx=0;
	roty=1;
	//angle_Y=0;
}
if(angle_Z <90)
{
//angle_Y=0;
	angle_Z = angle_Z + vitesse;
	roty=0;
	rotz=1;
	angle_Z=0;
}

if (angle_X <360) 
	{
	angle_Z=0;
	rotz=0;
	rotx=1;
	}



/*if ( angle_X <90 ) {
	angle_X = angle_X + vitesse;
	rotx=1;
	//angle_X=0;
} else if(angle_Y <90){

	angle_Y = angle_Y + vitesse;
	rotx=0;
	roty=1;
	//angle_Y=0;
} else if(angle_Z <90){

	angle_Z = angle_Z + vitesse;
	roty=0;
	rotz=1;
} else { 

rotz=0;
rotx=1;
}*/

    /*
	angle_X = angle_X + vitesse;
	if (angle_X <=90) 
	{rotx=1;}
	angle_X=0;
	angle_Y = angle_Y + vitesse;
	if (angle_Y <=90) 
	{
	//angle_X=0;
	rotx=0;
	roty=1;
	//angle_Y=0;
	}
	angle_Z = angle_Z + vitesse;
	if (angle_Z <=90) 
	{
	roty=0;
	rotz=1;
	//angle_Z=0;
	} 
	*/
	glutPostRedisplay();
}

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

int main (int argc, char** argv)
{
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(950, 650);
	glutInitWindowPosition(150,150);

	glutCreateWindow("Projet screensaver");
	glutFullScreen();
	
	Init();
	//myinit(); // rajout , test eclairage
	glutDisplayFunc(Display); //affichage cube
	glutReshapeFunc(myReshape);
	glutIdleFunc(motion);
	glutKeyboardFunc(key);

	glutMainLoop();

	return (0);
}
