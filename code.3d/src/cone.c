/** @file cone.c
 *
 *  @brief Contains the definition of the **Cone**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */


#include <errno.h>
#include "../include/cone.h"


/**
 * @brief Check if a point is inside or on a cone.
 *
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the cone, false otherwise.
 */
static bool insideCone(G3Xpoint p) {
    return (p[2] > -1 && p[2] < 0) && (p[0] * p[0] + p[1] * p[1]) < (p[2] * p[2]);
}


Cone *buildRandomCone(int n, int p) {
    Cone *cone = malloc(sizeof(Object));
    if (cone == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCone ");
        exit(1);
    }
    
    double theta, z, d;
    DrawData *data;
    int i;
    
    cone->n = n;
    cone->p = p;
    cone->size = n * p;
    cone->shape = SHP_CONE;
    cone->pt_in = insideCone;
    cone->drawData = malloc(sizeof(DrawData) * cone->size);
    if (cone->drawData == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCone ");
        exit(1);
    }
    
    for (i = 0; i < cone->size; i++) {
        memcpy(cone->drawData[i].color, G3Xr, sizeof(G3Xcolor));
    }
    
    data = cone->drawData;

    for (i = 0; i < cone->size / 2; i++) {
        
        z = -sqrt(g3x_Rand_Delta(0, 1));
        theta = g3x_Rand_Delta(0, 2 * PI);
        (*data).vertex[0] = z * cos(theta);
        (*data).vertex[1] = z * sin(theta);
        (*data).vertex[2] = z;
        
        (*data).normal[0] = cos(theta);
        (*data).normal[1] = sin(theta);
        (*data).normal[2] = 1;
        data++;
        
        do {
            (*data).vertex[0] = g3x_Rand_Delta(0, +1);
            (*data).vertex[1] = g3x_Rand_Delta(0, +1);
            
            d = (*data).vertex[0] * (*data).vertex[0] + (*data).vertex[1] * (*data).vertex[1];
        } while (d > 1);
        (*data).vertex[2] = -1;
    
        (*data).normal[0] = 0;
        (*data).normal[1] = 0;
        (*data).normal[2] = -1;
        
        data++;
    }
    
    return cone;
}


