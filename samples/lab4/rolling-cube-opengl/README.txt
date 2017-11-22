/***********************************************
**		Read Me			****
***********************************************/

J'ai choisi pour le développement la compilation par g++ et 
la séparation du code en 3 fichiers : une bibliothèque .h, un fichier 
de développement des fonctions .cc, et un fichier d'execution .cpp.
Cette compilation se fait donc nécessairement au moyen d'un Makefile.
L'execution se fait au moyen de la commande $./screensaver suivie de la dimension
de l'écran (largeur et hauteur).

Le cube mesure 2 de longueur (centré en (0,0,0) et une unité de part et d'autre
selon chaque dimension), j'ai donc considéré que la balle atteignait une paroi lorsque
une des coordonnées de sa position (+son rayon) valait 1 ou -1 et il suffisait alors
d'inverser la route selon l'axe en question pour pouvoir faire rebondir cette balle.
Ce faisant, la balle ne rebondit non pas dans une sphere mais bien dans un cube, en
revanche, ce cube servant de rebond à la balle est immobile, contrairement au cube
affiché qui lui tourne.

J'ai tenté d'apposer une texture à partir d'une image en m'inspirant du TP "planet.c", 
mais rien n'y a fait, le code ne convenait jamais, les changements sur les lumieres
n'aboutissaient à rien, résultat mon cube et ma balle restent blancs ecarlates.
J'ai laissé ce code en question (structures image et fonctions ImageLoad,
LoadTexture, CreatePlanet) même si elles s'avèrent inefficaces.