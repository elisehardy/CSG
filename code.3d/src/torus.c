/** @file torus.c
 *
 *  @brief Contains the definition of the **Torus**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#include <errno.h>
#include "../include/torus.h"


/**
 * @brief Check if a point is inside or on a torus.
 *
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the torus, false otherwise.
 */
static bool insideTorus(G3Xpoint p) {
    return (sqrt(p[0] * p[0] + p[1] * p[1]) - 2) * (sqrt(p[0] * p[0] + p[1] * p[1]) - 2) + p[2] * p[2] < 1;
}


Torus *buildRandomTorus(int n, int p) {
    Torus *torus = (Object *) malloc(sizeof(Object));
    if (torus == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomorus ");
        exit(1);
    }
    
    int i;
    double theta, phi;
    
    torus->n = n;
    torus->p = p;
    torus->size = n * p;
    torus->shape = SHP_TORUS;
    torus->pt_in = insideTorus;
    torus->color = malloc(sizeof(G3Xcolor) * torus->size);
    torus->vertex = (G3Xpoint *) calloc(torus->size, sizeof(G3Xpoint));
    torus->normal = (G3Xvector *) calloc(torus->size, sizeof(G3Xvector));
    if (!(torus->vertex && torus->normal && torus->color)) {
        errno = ENOMEM;
        perror("Error - buildRandomTorus ");
        exit(1);
    }
    
    for (i = 0; i < torus->size; i++) {
        memcpy(torus->color[i], G3Xr, sizeof(float) * 4);
    }
    
    G3Xpoint *vertices = torus->vertex;
    G3Xvector * normals = torus->normal;
    int innerRadius = 1;
    int outerRadius = 2;
    for (i = 0; i < torus->size; i++) {
        theta = g3x_Rand_Delta(0, 0.5) * 2 * PI;
        phi = g3x_Rand_Delta(0, 0.5) * 2 * PI;
        
        (*vertices)[0] = (outerRadius + innerRadius * cos(phi)) * cos(theta);
        (*vertices)[1] = (outerRadius + innerRadius * cos(phi)) * sin(theta);
        
        (*vertices)[2] = innerRadius * sin(phi);
        
        vertices++;
        (*normals)[0] = cos(phi) * cos(theta);
        (*normals)[1] = cos(phi) * sin(theta);
        (*normals)[2] = sin(phi);
        normals++;
    }
    
    return torus;
}
