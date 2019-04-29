/** @file sphere.c
 *
 *  @brief Contains the definition of the **Sphere**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */


#include <errno.h>
#include "../include/sphere.h"


/**
 * @brief Check if a point is inside or on a sphere.
 *
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the sphere, false otherwise.
 */
static bool insideSphere(G3Xpoint p) {
    return (p[0] * p[0] + p[1] * p[1] + p[2] * p[2]) <= 1.0000001;
}


Sphere *buildRandomSphere(int n, int p) {
    Sphere *sphere = malloc(sizeof(Object));
    if (sphere == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomSphere ");
        exit(1);
    }
    
    G3Xpoint *vertices;
    double d;
    int i;
    
    sphere->n = n;
    sphere->p = p;
    sphere->size = p * n;
    sphere->shape = SHP_SPHERE;
    sphere->pt_in = insideSphere;
    sphere->color = malloc(sizeof(G3Xcolor) * sphere->size);
    sphere->vertex = calloc(sphere->size, sizeof(G3Xpoint));
    sphere->normal = calloc(sphere->size, sizeof(G3Xvector));
    if (!(sphere->vertex && sphere->normal && sphere->color)) {
        errno = ENOMEM;
        perror("Error - buildRandomSphere ");
        exit(1);
    }
    
    for (i = 0; i < sphere->size; i++) {
        memcpy(sphere->color[i], G3Xr, sizeof(float) * 4);
    }
    
    vertices = sphere->vertex;
    
    for (i = 0; i < sphere->size; i++) {
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            (*vertices)[2] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1] + (*vertices)[2] * (*vertices)[2];
        } while (d > 1);
        
        d = sqrt(d);
        (*vertices)[0] = (*vertices)[0] / d;
        (*vertices)[1] = (*vertices)[1] / d;
        (*vertices)[2] = (*vertices)[2] / d;
        vertices++;
    }
    
    memcpy(sphere->normal, sphere->vertex, sphere->size * sizeof(G3Xvector));
    
    return sphere;
}

