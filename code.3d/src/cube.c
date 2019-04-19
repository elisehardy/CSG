#include <errno.h>
#include "../include/cube.h"


/**
 * Check if a point is inside or on a cube.
 *
 * @param cube The cube the point will be checked against.
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the cube, false otherwise.
 */
static bool insideCube(G3Xpoint p) {
    return MAX(abs(p[0]), MAX(abs(p[1]), abs(p[2]))) <= 1;
}


Cube *buildRandomCube(int n, int p) {
    Cube *cube = (Object *) malloc(sizeof(Object));
    if (cube == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCube ");
        exit(1);
    }
    
    G3Xvector *normals;
    G3Xpoint *vertices;
    int i;
    
    cube->n = n;
    cube->p = p;
    cube->size = n * p * 6;
    cube->shape = SHP_CUBE;
    cube->pt_in = insideCube;
    cube->color = malloc(sizeof(G3Xpoint) * cube->size);
    cube->vertex = (G3Xpoint *) calloc(cube->size, sizeof(G3Xpoint));
    cube->normal = (G3Xvector *) calloc(cube->size, sizeof(G3Xvector));
    if (!(cube->vertex && cube->normal && cube->color)) {
        errno = ENOMEM;
        perror("Error - buildRandomCube ");
        exit(1);
    }
    
    for (i = 0; i < cube->size; i++) {
        memcpy(cube->color[i], G3Xr, sizeof(float)*4);
    }
    
    vertices = cube->vertex;
    normals = cube->normal;
    
    for (i = 0; i < ((cube->size) / 6); i++) {
        (*vertices)[0] = g3x_Rand_Delta(0, 1);
        (*vertices)[1] = g3x_Rand_Delta(0, 1);
        (*vertices)[2] = +1.;
        vertices++;
        
        (*vertices)[0] = g3x_Rand_Delta(0, 1);
        (*vertices)[1] = g3x_Rand_Delta(0, 1);
        (*vertices)[2] = -1.;
        vertices++;
        
        (*vertices)[0] = g3x_Rand_Delta(0, 1);
        (*vertices)[1] = +1.;
        (*vertices)[2] = g3x_Rand_Delta(0, 1);
        vertices++;
        
        (*vertices)[0] = g3x_Rand_Delta(0, 1);
        (*vertices)[1] = -1.;
        (*vertices)[2] = g3x_Rand_Delta(0, 1);
        vertices++;
        
        (*vertices)[0] = +1.;
        (*vertices)[1] = g3x_Rand_Delta(0, 1);
        (*vertices)[2] = g3x_Rand_Delta(0, 1);
        vertices++;
        
        (*vertices)[0] = -1.;
        (*vertices)[1] = g3x_Rand_Delta(0, 1);
        (*vertices)[2] = g3x_Rand_Delta(0, 1);
        vertices++;
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = +1.;
        normals++;
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = -1.;
        normals++;
        
        (*normals)[0] = 0;
        (*normals)[1] = +1.;
        (*normals)[2] = 0;
        normals++;
        
        (*normals)[0] = 0;
        (*normals)[1] = -1.;
        (*normals)[2] = 0;
        normals++;
        
        (*normals)[0] = +1.;
        (*normals)[1] = 0;
        (*normals)[2] = 0;
        normals++;
        
        (*normals)[0] = -1.;
        (*normals)[1] = 0;
        (*normals)[2] = 0;
        normals++;
    }
    
    return cube;
}
