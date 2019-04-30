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
    Torus *torus = malloc(sizeof(Object));
    if (torus == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomorus ");
        exit(1);
    }
    
    int innerRadius = 1, outerRadius = 2, i;
    DrawData *data;
    double theta, phi;
    
    torus->n = n;
    torus->p = p;
    torus->size = n * p;
    torus->shape = SHP_TORUS;
    torus->pt_in = insideTorus;
    torus->drawData = calloc(torus->size, sizeof(DrawData));
    if (torus->drawData == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomTorus ");
        exit(1);
    }
    
    for (i = 0; i < torus->size; i++) {
        memcpy(torus->drawData[i].color, G3Xr, sizeof(G3Xcolor));
    }
    
    data = torus->drawData;
    
    for (i = 0; i < torus->size; i++) {
        theta = g3x_Rand_Delta(0, 0.5) * 2 * PI;
        phi = g3x_Rand_Delta(0, 0.5) * 2 * PI;
        
        (*data).vertex[0] = (outerRadius + innerRadius * cos(phi)) * cos(theta);
        (*data).vertex[1] = (outerRadius + innerRadius * cos(phi)) * sin(theta);
        (*data).vertex[2] = innerRadius * sin(phi);
        
        (*data).normal[0] = cos(phi) * cos(theta);
        (*data).normal[1] = cos(phi) * sin(theta);
        (*data).normal[2] = sin(phi);
    
        data++;
    }
    
    return torus;
}
