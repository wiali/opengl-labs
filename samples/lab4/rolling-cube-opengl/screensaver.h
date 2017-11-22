
/* Image type - contains height, width, and data */
typedef struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
} Image;

//Pour transformer les degres en radians
float degToRad (float deg);

//Pour transformer les radians en degres
float radToDeg (float rad);

//pre affichage, initialisation de toutes les variables utiles.
void init(void);

//fonction d'affichage rappelee continuellement par glutpostredisplay
void display(void);

//fonction qui reattribue certaines valeurs relatives au contenant :
//la camera par exemple
void reshape(int, int);

void idleFunction(void);

//fonction qui recalcule en focntion de la position precedente la nouvelle position du cube
void cubeRotation();

//fonction qui recalcule en focntion de la position precedente la nouvelle position de la sphere
void sphereMoving();

//fonction qui determine la valeur absolue d'un float
float absoluteValue(float);

int ImageLoad(char*, Image*);

void LoadTexture(char*, int*);

void CreatePlanet(float, int);

typedef struct point {
	float x, y, z;
} point;
/*
typedef struct vector {
	point ptOfAppli; point Direction; float norm;
} vector;
*/

