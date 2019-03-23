#include "../include/sphere.h"


void buildRegularSphere(Object *obj) {
    double a = 2 * PI / obj->n;
    double b = 2 * PI / obj->n;
    double cosa, sina;
    int i, j;
    
    obj->shape = SHP_SPHERE;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        perror("Could not allocate object");
        exit(1);
    }
    
    for (i = 0; i < obj->n; i++) {
        cosa = cos(i * a);
        sina = sin(i * a);
        for (j = 0; j < obj->p; j++) {
            obj->vertex[i * obj->p + j][0] = cosa * sin(j * b);
            obj->vertex[i * obj->p + j][1] = sina * sin(j * b);
            obj->vertex[i * obj->p + j][2] = cos(j * b);
        }
    }
    
    memcpy(obj->normal, obj->vertex, obj->n * obj->p * sizeof(G3Xvector));
}


void buildRandomSphere(Object *obj) {
    G3Xvector *n;
    G3Xpoint *v;
    double d;
    int i;
    
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        perror("Could not allocate object");
        exit(1);
    }
    
    v = obj->vertex;
    n = obj->normal;
    
    for (i = 0; i < obj->size; i++) {
        do {
            (*v)[0] = g3x_Rand_Delta(0, +1);
            (*v)[1] = g3x_Rand_Delta(0, +1);
            (*v)[2] = g3x_Rand_Delta(0, +1);
            
            d = (*v)[0] * (*v)[0] + (*v)[1] * (*v)[1] + (*v)[2] * (*v)[2];
        } while (d > 1);
        
        d = sqrt(d);
        (*v)[0] = (*v)[0] / d;
        (*v)[1] = (*v)[1] / d;
        (*v)[2] = (*v)[2] / d;
        v++;
        
        (*n)[0] = (*v)[0];
        (*n)[1] = (*v)[1];
        (*n)[2] = (*v)[2];
        n++;
    }
    
    memcpy(obj->normal, obj->vertex, obj->n * obj->p * sizeof(G3Xvector));
}


void drawSphere(Object *obj, int c) {
    G3Xvector *n;
    G3Xpoint *v;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    v = obj->vertex;
    n = obj->normal;
    while (v < obj->vertex + obj->size) {
        glNormal3dv(*n);
        n += c;
        glVertex3dv(*v);
        v += c;
    }
    
    glEnd();
}








