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


Object *sphere, *cube, *torus, *cone, *cylinder;


void init(void) {
    sphere = buildRandomSphere(1000, 1000);
    cube = buildRandomCube(400, 400);
    torus = buildRandomTorus(400, 400, 1, 2);
    cone = buildRandomCone(1000, 400);
    cylinder = buildRandomCylinder(400, 400);
}


void draw(void) {
    g3x_Material(G3Xr, 0.25, 0.5, 0.5, 0.5, 1.);
    /*drawObject(sphere, 1);*/
    drawObject(cube, 1);
    /*drawObject(torus, 1);*/
    drawObject(cone, 1);
    /*drawObject(cylinder,1);*/
}


int main(int argc, char **argv) {
    FILE *file;
    Tree *tree;
    
    /* initialisation de la fenêtre graphique et paramétrage Gl */
    g3x_InitWindow(*argv, 768, 512);
    /* param. géométrique de la caméra. cf. gluLookAt(...) */
    g3x_SetPerspective(40., 100., 1.);
    /* position, orientation de la caméra */
    g3x_SetCameraSpheric(0.25 * PI, +0.25 * PI, 6., (G3Xpoint) {0., 0., 0.});
    
    file = fopen(argv[1], "r");
    if (file == NULL) {
        errno = ENOENT;
        perror(argv[1]);
        exit(1);
    }
    /*create tree*/
    tree = parseFile(file);
    
    printTree(tree);
    
    /* définition des fonctions */
    g3x_SetInitFunction(init);     /* la fonction d'initialisation */
    g3x_SetDrawFunction(draw);     /* la fonction de dessin        */
    g3x_SetAnimFunction(NULL);         /* pas de fonction d'animation  */
    g3x_SetExitFunction(NULL);     /* pas de fonction de sortie    */
    
    
    /* boucle d'exécution principale */
    return g3x_MainStart();
}
