#include "../include/sphere.h"


Sphere *buildRegularSphere(int n, int p) {
    Sphere *sphere = (Object *) malloc(sizeof(Object));
    if (sphere == NULL) {
        errno = ENOMEM;
        perror("Error - buildRegularSphere ");
        exit(1);
    }
    
    double a = 2 * PI / n;
    double cosa, sina;
    int i, j;
    
    sphere->n = n;
    sphere->p = p;
    sphere->size = p * n;
    sphere->shape = SHP_SPHERE;
    sphere->vertex = (G3Xpoint *) calloc(sphere->size, sizeof(G3Xpoint));
    sphere->normal = (G3Xvector *) calloc(sphere->size, sizeof(G3Xvector));
    if (!(sphere->vertex && sphere->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularSphere ");
        exit(1);
    }
    
    for (i = 0; i < sphere->n; i++) {
        cosa = cos(i * a);
        sina = sin(i * a);
        for (j = 0; j < sphere->p; j++) {
            sphere->vertex[i * sphere->p + j][0] = cosa * sin(j * a);
            sphere->vertex[i * sphere->p + j][1] = sina * sin(j * a);
            sphere->vertex[i * sphere->p + j][2] = cos(j * a);
        }
    }
    
    memcpy(sphere->normal, sphere->vertex, sphere->n * sphere->p * sizeof(G3Xvector));
    
    return sphere;
}


Sphere *buildRandomSphere(int n, int p) {
    Sphere *sphere = (Object *) malloc(sizeof(Object));
    if (sphere == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomSphere ");
        exit(1);
    }
    
    G3Xpoint *vertices;
    double d;
    int i;
    
    sphere->n = n;
    sphere->p = p;
    sphere->size = p * n;
    sphere->shape = SHP_SPHERE;
    sphere->vertex = (G3Xpoint *) calloc(sphere->size, sizeof(G3Xpoint));
    sphere->normal = (G3Xvector *) calloc(sphere->size, sizeof(G3Xvector));
    if (!(sphere->vertex && sphere->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomSphere ");
        exit(1);
    }
    
    vertices = sphere->vertex;
    
    for (i = 0; i < sphere->size; i++) {
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            (*vertices)[2] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1] + (*vertices)[2] * (*vertices)[2];
        } while (d > 1);
        
        d = sqrt(d);
        (*vertices)[0] = (*vertices)[0] / d;
        (*vertices)[1] = (*vertices)[1] / d;
        (*vertices)[2] = (*vertices)[2] / d;
        vertices++;
    }
    
    memcpy(sphere->normal, sphere->vertex, sphere->n * sphere->p * sizeof(G3Xvector));
    
    return sphere;
}


bool insideSphere(Sphere *sphere, G3Xpoint p) {
    if (sphere == NULL) {
        errno = EFAULT;
        perror("Error - insideSphere ");
        exit(1);
    }
    
    return (p[0] * p[0] + p[1] * p[1] + p[2] * p[2]) <= 1;
}

