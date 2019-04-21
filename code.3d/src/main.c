/** @file main.c
 *
 *  @brief Contains the ***main*** of the project and *g3x*'s `init()` and `draw()` functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 *
 *  @dir include
 *  @brief Contains **headers** of the project.
 *  @dir src
 *  @brief Contains **sources** of the project.
 */


#include <errno.h>
#include "../include/tree.h"
#include "../include/file.h"


Tree *tree;


char *filepath;


void init(void) {
    FILE *file;
    
    file = fopen(filepath, "r");
    if (file == NULL) {
        errno = ENOENT;
        perror(filepath);
        exit(1);
    }
    
    tree = parseFile(file);
    fclose(file);
    
    printTree(tree);
}


void draw(void) {
    drawNode(tree, 1);
}


int main(int argc, char **argv) {
    filepath = argv[1];
    
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
