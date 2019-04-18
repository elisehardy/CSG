#include <errno.h>
#include "../include/torus.h"


/**
 * Check if a point is inside or on a torus.
 *
 * @param torus The torus the point will be checked against.
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the torus, false otherwise.
 */
static bool insideTorus(G3Xpoint p) {
    return (sqrt(p[0] * p[0] + p[1] * p[1]) - 2) * (sqrt(p[0] * p[0] + p[1] * p[1]) - 2) + p[2] * p[2] < 1;
}


/* TODO : Normals not done yet */
Torus *buildRandomTorus(int n, int p, int innerRadius, int outerRadius) {
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
    torus->vertex = (G3Xpoint *) calloc(torus->size, sizeof(G3Xpoint));
    torus->normal = (G3Xvector *) calloc(torus->size, sizeof(G3Xvector));
    if (!(torus->vertex && torus->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomTorus ");
        exit(1);
    }
    
    G3Xpoint *vertices = torus->vertex;
    
    for (i = 0; i < torus->size; i++) {
        theta = g3x_Rand_Delta(0, 0.5) * 2 * PI;
        phi = g3x_Rand_Delta(0, 0.5) * 2 * PI;
        
        (*vertices)[0] = (outerRadius + innerRadius * cos(phi)) * cos(theta);
        (*vertices)[1] = (outerRadius + innerRadius * cos(phi)) * sin(theta);
        
        (*vertices)[2] = innerRadius * sin(phi);
        
        vertices++;
    }
    
    return torus;
}
