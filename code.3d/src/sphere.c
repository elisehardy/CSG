#include "../include/sphere.h"


Object *buildRegularSphere(int n, int p) {
    Object *obj = (Object *) malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - buildRegularSphere ");
        exit(1);
    }
    
    double a = 2 * PI / n;
    double cosa, sina;
    int i, j;
    
    obj->n = n;
    obj->p = p;
    obj->size = p * n;
    obj->shape = SHP_SPHERE;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularSphere ");
        exit(1);
    }
    
    for (i = 0; i < obj->n; i++) {
        cosa = cos(i * a);
        sina = sin(i * a);
        for (j = 0; j < obj->p; j++) {
            obj->vertex[i * obj->p + j][0] = cosa * sin(j * a);
            obj->vertex[i * obj->p + j][1] = sina * sin(j * a);
            obj->vertex[i * obj->p + j][2] = cos(j * a);
        }
    }
    
    memcpy(obj->normal, obj->vertex, obj->n * obj->p * sizeof(G3Xvector));
    
    return obj;
}


Object *buildRandomSphere(int n, int p) {
    Object *obj = (Object *) malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomSphere ");
        exit(1);
    }
    
    G3Xpoint *vertices;
    double d;
    int i;
    
    obj->n = n;
    obj->p = p;
    obj->size = p * n;
    obj->shape = SHP_SPHERE;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomSphere ");
        exit(1);
    }
    
    vertices = obj->vertex;
    
    for (i = 0; i < obj->size; i++) {
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            (*vertices)[2] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1]
                + (*vertices)[2] * (*vertices)[2];
        } while (d > 1);
        
        d = sqrt(d);
        (*vertices)[0] = (*vertices)[0] / d;
        (*vertices)[1] = (*vertices)[1] / d;
        (*vertices)[2] = (*vertices)[2] / d;
        vertices++;
    }
    
    memcpy(obj->normal, obj->vertex, obj->n * obj->p * sizeof(G3Xvector));
    
    return obj;
}

bool insideSphere(Object *obj, G3Xpoint p){
    return (p[0]*p[0] + p[1]*p[1] + p[2]*p[2])<=1;
    }

