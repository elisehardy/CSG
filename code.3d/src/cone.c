#include <errno.h>
#include "../include/cone.h"




Cone *buildRandomCone(int n, int p) {
    Cone *cone = (Object *) malloc(sizeof(Object));
    if (cone == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCone ");
        exit(1);
    }
    
    double theta, z;
    int i;
    
    cone->n = n;
    cone->p = p;
    cone->size = n * p;
    cone->shape = SHP_CONE;
    cone->pt_in = NULL;
    cone->vertex = (G3Xpoint *) calloc(cone->size, sizeof(G3Xpoint));
    cone->normal = (G3Xvector *) calloc(cone->size, sizeof(G3Xvector));
    if (!(cone->vertex && cone->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomCone ");
        exit(1);
    }
    G3Xpoint *vertices = cone->vertex;
    G3Xvector *normals = cone->normal;
    double d;
    for (i = 0; i < cone->size / 2; i++) {
        
        z = -sqrt(g3x_Rand_Delta(0, 1));
        theta = g3x_Rand_Delta(0, 2 * PI);
        (*vertices)[0] = z * cos(theta);
        (*vertices)[1] = z * sin(theta);
        (*vertices)[2] = z;
        
        (*normals)[0] = cos(theta);
        (*normals)[1] = sin(theta);
        (*normals)[2] = 1;
        vertices++;
        normals++;
        
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        } while (d > 1);
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = -1;
        
        (*vertices)[2] = -1;
        vertices++;
        normals++;
    }
    
    return cone;
}


bool insideCone(G3Xpoint p){
    return (p[2]>-1 && p[2]<0) && (p[0]*p[0]+p[1]*p[1]) < (p[2]*p[2]);
    }

