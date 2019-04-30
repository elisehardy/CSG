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
    
    DrawData *data;
    double d;
    int i;
    
    sphere->n = n;
    sphere->p = p;
    sphere->size = p * n;
    sphere->shape = SHP_SPHERE;
    sphere->pt_in = insideSphere;
    sphere->drawData = calloc(sphere->size, sizeof(DrawData));
    if (sphere->drawData == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomSphere ");
        exit(1);
    }
    
    for (i = 0; i < sphere->size; i++) {
        memcpy(sphere->drawData[i].color, G3Xr, sizeof(G3Xcolor));
    }
    
    data = sphere->drawData;
    
    for (i = 0; i < sphere->size; i++) {
        do {
            (*data).vertex[0] = g3x_Rand_Delta(0, +1);
            (*data).vertex[1] = g3x_Rand_Delta(0, +1);
            (*data).vertex[2] = g3x_Rand_Delta(0, +1);
            d = (*data).vertex[0] * (*data).vertex[0] + (*data).vertex[1] * (*data).vertex[1] + (*data).vertex[2] * (*data).vertex[2];
        } while (d > 1);
        
        d = sqrt(d);
        (*data).vertex[0] = (*data).vertex[0] / d;
        (*data).vertex[1] = (*data).vertex[1] / d;
        (*data).vertex[2] = (*data).vertex[2] / d;
        memcpy((*data).normal, (*data).vertex, sizeof(G3Xcoord));
        data++;
    }
    
    return sphere;
}

