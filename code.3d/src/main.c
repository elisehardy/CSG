#include "../include/cone.h"
#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"
#include "../include/matrix.h"


int main(int argc, char **argv) {
    /* initialisation de la fenêtre graphique et paramétrage Gl */
    g3x_InitWindow(*argv, 768, 512);
    /* param. géométrique de la caméra. cf. gluLookAt(...) */
    g3x_SetPerspective(40., 100., 1.);
    /* position, orientation de la caméra */
    g3x_SetCameraSpheric(0.25 * PI, +0.25 * PI, 6., (G3Xpoint) {0., 0., 0.});
    
    /* définition des fonctions */
    g3x_SetInitFunction(init);     /* la fonction d'initialisation */
    g3x_SetDrawFunction(draw);     /* la fonction de dessin        */
    g3x_SetAnimFunction(NULL);         /* pas de fonction d'animation  */
    g3x_SetExitFunction(NULL);     /* pas de fonction de sortie    */
    
    
    /* boucle d'exécution principale */
    return g3x_MainStart();
    /* rien après ça */
}
