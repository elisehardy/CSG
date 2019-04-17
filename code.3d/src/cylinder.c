#include <errno.h>
#include "../include/cylinder.h"


Cylinder *buildRegularCylinder(int n, int p) {
    Cylinder *cylinder = (Object *) malloc(sizeof(Object));
    if (cylinder == NULL) {
        errno = ENOMEM;
        perror("Error - buildRegularCylinder ");
        exit(1);
    }
    
    cylinder->n = n;
    cylinder->p = p;
    cylinder->size = n * p;
    cylinder->shape = SHP_CYLINDER;
    cylinder->vertex = (G3Xpoint *) calloc(cylinder->size, sizeof(G3Xpoint));
    cylinder->normal = (G3Xvector *) calloc(cylinder->size, sizeof(G3Xvector));
    if (!(cylinder->vertex && cylinder->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularCylinder ");
        exit(1);
    }
    
    double theta, z;
    int i, j;
    
    for (i = 0; i < cylinder->p; i++) {
        for (j = 0; j < cylinder->n; j++) {
            z = sqrt(g3x_Rand_Delta(0, 1));
            theta = g3x_Rand_Delta(0, 2 * PI);
            cylinder->vertex[i * (cylinder->n) + j][0] = z * cos(theta);
            cylinder->vertex[i * (cylinder->n) + j][1] = z * sin(theta);
            cylinder->vertex[i * (cylinder->n) + j][2] = z;
            
            cylinder->normal[i * (cylinder->n) + j][0] = cos(theta);
            cylinder->normal[i * (cylinder->n) + j][1] = sin(theta);
            cylinder->normal[i * (cylinder->n) + j][2] = 1;
        }
    }
    
    return cylinder;
}


Cylinder *buildRandomCylinder(int n, int p) {
    Cylinder *cylinder = (Object *) malloc(sizeof(Object));
    if (cylinder == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCylinder ");
        exit(1);
    }
    
    cylinder->n = n;
    cylinder->p = p;
    cylinder->size = n * p;
    cylinder->shape = SHP_CYLINDER;
    cylinder->vertex = (G3Xpoint *) calloc(cylinder->size, sizeof(G3Xpoint));
    cylinder->normal = (G3Xvector *) calloc(cylinder->size, sizeof(G3Xvector));
    if (!(cylinder->vertex && cylinder->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomCylinder ");
        exit(1);
    }
    
    int i;
    double d;
    G3Xpoint *vertices = cylinder->vertex;
    G3Xvector *normals = cylinder->normal;
    
    for (i = 0; i < cylinder->size / 3; i++) {
        /*cercle dessus*/
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        } while (d > 1);
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = 1;
        
        (*vertices)[2] = 1;
        vertices++;
        normals++;
        
        
        /*cercle dessous*/
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
        
        /*bandeau*/
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        } while (d > 1);
        d = sqrt(d);
        (*vertices)[0] = (*vertices)[0] / d;
        (*vertices)[1] = (*vertices)[1] / d;
        
        (*normals)[0] = (*vertices)[0] / d;
        (*normals)[1] = (*vertices)[1] / d;
        (*normals)[2] = 0;
        
        (*vertices)[2] = g3x_Rand_Delta(0, +1);
        vertices++;
        normals++;
    }
    
    return cylinder;
}


bool insideCylinder(G3Xpoint p) {
    
    return abs(p[2]) < 1 && p[0] * p[0] + p[1] * p[1] < 1;
}
