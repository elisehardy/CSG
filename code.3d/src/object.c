#include <errno.h>
#include "../include/object.h"


Object *merge(Object *a, Object *b) {
    Object *obj = (Object *) malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomobj ");
        exit(1);
    }
    
    obj->n = 0;
    obj->p = 0;
    obj->size = a->size + b->size;
    obj->shape = SHP_COMPOSITE;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    
    memcpy(obj->vertex, a->vertex, a->size);
    memcpy(obj->vertex + a->size, b->vertex, b->size);
    
    memcpy(obj->normal, a->normal, a->size);
    memcpy(obj->normal + a->size, b->normal, b->size);
    
    return obj;
}


void drawObject(Object *obj, int c) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - drawObject ");
        exit(1);
    }
    
    G3Xvector *n = obj->normal;
    G3Xpoint *v = obj->vertex;
    int bit = 0;
    glPointSize(1);
    glBegin(GL_POINTS);
    
    while (v < obj->vertex + obj->size) {
        glNormal3dv(*n);
        n += c;
        glVertex3dv(*v);
        v += c;
        
        bit++;
    }
    
    glEnd();
}






