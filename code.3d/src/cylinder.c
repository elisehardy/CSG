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
    Cylinder *cylinder = malloc(sizeof(Object));
    if (cylinder == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCylinder ");
        exit(1);
    }
    
    DrawData *data;
    double d;
    int i;
    
    cylinder->n = n;
    cylinder->p = p;
    cylinder->size = n * p;
    cylinder->shape = SHP_CYLINDER;
    cylinder->pt_in = insideCylinder;
    cylinder->drawData = calloc(cylinder->size, sizeof(DrawData));
    if (cylinder->drawData == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCylinder ");
        exit(1);
    }
    
    for (i = 0; i < cylinder->size; i++) {
        memcpy(cylinder->drawData[i].color, G3Xr, sizeof(G3Xcolor));
    }
    
    data = cylinder->drawData;
    
    for (i = 0; i < cylinder->size / 3; i++) {
        /*cercle dessus*/
        do {
            (*data).vertex[0] = g3x_Rand_Delta(0, +1);
            (*data).vertex[1] = g3x_Rand_Delta(0, +1);
            
            d = (*data).vertex[0] * (*data).vertex[0] + (*data).vertex[1] * (*data).vertex[1];
        } while (d > 1);
        (*data).vertex[2] = 1;
    
        (*data).normal[0] = 0;
        (*data).normal[1] = 0;
        (*data).normal[2] = 1;
        data++;
        
        
        /*cercle dessous*/
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
        
        /*bandeau*/
        do {
            (*data).vertex[0] = g3x_Rand_Delta(0, +1);
            (*data).vertex[1] = g3x_Rand_Delta(0, +1);
            
            d = (*data).vertex[0] * (*data).vertex[0] + (*data).vertex[1] * (*data).vertex[1];
        } while (d > 1);
        d = sqrt(d);
        (*data).vertex[0] = (*data).vertex[0] / d;
        (*data).vertex[1] = (*data).vertex[1] / d;
        
        (*data).normal[0] = (*data).vertex[0] / d;
        (*data).normal[1] = (*data).vertex[1] / d;
        (*data).normal[2] = 0;
        
        (*data).vertex[2] = g3x_Rand_Delta(0, +1);
        data++;
    }
    
    return cylinder;
}
