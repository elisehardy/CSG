#include <errno.h>
#include "../include/object.h"


Object *merge(Object *a, Object *b) {
    if (a == NULL || b == NULL) {
        errno = EFAULT;
        perror("Error - merge ");
        exit(1);
    }
    
    Object *obj = (Object *) malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - merge ");
        exit(1);
    }
    
    obj->n = 0;
    obj->p = 0;
    obj->shape = SHP_COMPOSITE;
    obj->size = a->size + b->size;
    obj->color = malloc(sizeof(G3Xpoint) * obj->size);
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal && obj->color)) {
        errno = ENOMEM;
        perror("Error - merge ");
        exit(1);
    }
    
    memcpy(obj->vertex, a->vertex, a->size * sizeof(G3Xpoint));
    memcpy(obj->vertex + a->size, b->vertex, b->size * sizeof(G3Xpoint));
    
    memcpy(obj->normal, a->normal, a->size * sizeof(G3Xvector));
    memcpy(obj->normal + a->size, b->normal, b->size * sizeof(G3Xvector));
    
    memcpy(obj->color, a->color, a->size * sizeof(G3Xcolor));
    memcpy(obj->color + a->size, b->color, b->size * sizeof(G3Xcolor));
    
    return obj;
}






