#include <errno.h>
#include "../include/object.h"
#include "../include/cone.h"
#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"
#include "../include/matrix.h"
#include "../include/tree.h"
#include "../include/file.h"


Tree *tree;


char *filepath;


void init(void) {
    FILE *file;
    Tree *tree;
    
    file = fopen(filepath, "r");
    if (file == NULL) {
        errno = ENOENT;
        perror(filepath);
        exit(1);
    }
    
    tree = parseFile(file);
    
    fclose(file);
}


void draw(void) {
    g3x_Material(G3Xr, 0.25, 0.5, 0.5, 0.5, 1.);
    drawObject(tree->obj, 1);
}


int main(int argc, char **argv) {
    
    filepath = argv[0];
    
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
}
