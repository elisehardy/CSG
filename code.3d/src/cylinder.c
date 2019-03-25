#include "../include/cylinder.h"


Object *buildRegularCylinder(Object *obj) {
    
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    
    double theta, z;
    int i, j;
    
    for (i = 0; i < obj->p; i++) {
        for (j = 0; j < obj->n; j++) {
            z = sqrt(g3x_Rand_Delta(0, 1));
            theta = g3x_Rand_Delta(0, 2 * PI);
            obj->vertex[i * (obj->n) + j][0] = z * cos(theta);
            obj->vertex[i * (obj->n) + j][1] = z * sin(theta);
            obj->vertex[i * (obj->n) + j][2] = z;
            
            obj->normal[i * (obj->n) + j][0] = cos(theta);
            obj->normal[i * (obj->n) + j][1] = sin(theta);
            obj->normal[i * (obj->n) + j][2] = 1;
        }
    }
    
    return obj;
}
