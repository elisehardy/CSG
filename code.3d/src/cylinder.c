/** @file cylinder.c
 *
 *  @brief Contains the definition of the **Cylinder**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#include <errno.h>
#include "../include/cylinder.h"


/**
 * @brief Check if a point is inside or on a cylinder.
 *
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the cylinder, false otherwise.
 */
static bool insideCylinder(G3Xpoint p) {
    return abs(p[2]) < 1 && p[0] * p[0] + p[1] * p[1] < 1;
}


Cylinder *buildRandomCylinder(int n, int p) {
    Cylinder *cylinder = (Object *) malloc(sizeof(Object));
    if (cylinder == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCylinder ");
        exit(1);
    }
    
    int i;
    
    cylinder->n = n;
    cylinder->p = p;
    cylinder->size = n * p;
    cylinder->shape = SHP_CYLINDER;
    cylinder->pt_in = insideCylinder;
    cylinder->color = malloc(sizeof(G3Xpoint) * cylinder->size);
    cylinder->vertex = (G3Xpoint *) calloc(cylinder->size, sizeof(G3Xpoint));
    cylinder->normal = (G3Xvector *) calloc(cylinder->size, sizeof(G3Xvector));
    if (!(cylinder->vertex && cylinder->normal && cylinder->color)) {
        errno = ENOMEM;
        perror("Error - buildRandomCylinder ");
        exit(1);
    }
    
    for (i = 0; i < cylinder->size; i++) {
        memcpy(cylinder->color[i], G3Xr, sizeof(float) * 4);
    }
    
    double d;
    G3Xpoint *vertices = cylinder->vertex;
    G3Xvector *normals = cylinder->normal;
    
    for (i = 0; i < cylinder->size / 3; i++) {
        /*cercle dessus*/
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        } while (d > 1);
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = 1;
        
        (*vertices)[2] = 1;
        vertices++;
        normals++;
        
        
        /*cercle dessous*/
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        } while (d > 1);
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = -1;
        
        (*vertices)[2] = -1;
        vertices++;
        normals++;
        
        /*bandeau*/
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        } while (d > 1);
        d = sqrt(d);
        (*vertices)[0] = (*vertices)[0] / d;
        (*vertices)[1] = (*vertices)[1] / d;
        
        (*normals)[0] = (*vertices)[0] / d;
        (*normals)[1] = (*vertices)[1] / d;
        (*normals)[2] = 0;
        
        (*vertices)[2] = g3x_Rand_Delta(0, +1);
        vertices++;
        normals++;
    }
    
    return cylinder;
}
