/** @file cube.c
 *
 *  @brief Contains the definition of the **Cube**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */


#include <errno.h>
#include "../include/cube.h"


/**
 * @brief Check if a point is inside or on a cube.
 *
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the cube, false otherwise.
 */
static bool insideCube(G3Xpoint p) {
    return p[0] <= 1 && p[0] >= -1 && p[1] <= 1 && p[1] >= -1 && p[2] <= 1 && p[2] >= -1;
}


Cube *buildRandomCube(int n, int p) {
    Cube *cube = malloc(sizeof(Object));
    if (cube == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCube ");
        exit(1);
    }
    
    DrawData *data;
    int i;
    
    cube->n = n;
    cube->p = p;
    cube->size = n * p * 6;
    cube->shape = SHP_CUBE;
    cube->pt_in = insideCube;
    cube->drawData = calloc(cube->size, sizeof(DrawData));
    if (cube->drawData == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCube ");
        exit(1);
    }
    
    for (i = 0; i < cube->size; i++) {
        memcpy(cube->drawData[i].color, G3Xr, sizeof(G3Xcolor));
    }
    
    data = cube->drawData;
    
    for (i = 0; i < (cube->size / 6); i++) {
        (*data).vertex[0] = g3x_Rand_Delta(0, 1);
        (*data).vertex[1] = g3x_Rand_Delta(0, 1);
        (*data).vertex[2] = +1.;
        (*data).normal[0] = 0;
        (*data).normal[1] = 0;
        (*data).normal[2] = +1.;
        data++;
        
        (*data).vertex[0] = g3x_Rand_Delta(0, 1);
        (*data).vertex[1] = g3x_Rand_Delta(0, 1);
        (*data).vertex[2] = -1.;
        (*data).normal[0] = 0;
        (*data).normal[1] = 0;
        (*data).normal[2] = -1.;
        data++;
        
        (*data).vertex[0] = g3x_Rand_Delta(0, 1);
        (*data).vertex[1] = +1.;
        (*data).vertex[2] = g3x_Rand_Delta(0, 1);
        (*data).normal[0] = 0;
        (*data).normal[1] = +1.;
        (*data).normal[2] = 0;
        data++;
        
        (*data).vertex[0] = g3x_Rand_Delta(0, 1);
        (*data).vertex[1] = -1.;
        (*data).vertex[2] = g3x_Rand_Delta(0, 1);
        (*data).normal[0] = 0;
        (*data).normal[1] = -1.;
        (*data).normal[2] = 0;
        data++;
        
        (*data).vertex[0] = +1.;
        (*data).vertex[1] = g3x_Rand_Delta(0, 1);
        (*data).vertex[2] = g3x_Rand_Delta(0, 1);
        (*data).normal[0] = +1.;
        (*data).normal[1] = 0;
        (*data).normal[2] = 0;
        data++;
        
        (*data).vertex[0] = -1.;
        (*data).vertex[1] = g3x_Rand_Delta(0, 1);
        (*data).vertex[2] = g3x_Rand_Delta(0, 1);
        (*data).normal[0] = -1.;
        (*data).normal[1] = 0;
        (*data).normal[2] = 0;
        data++;
    }
    
    return cube;
}
