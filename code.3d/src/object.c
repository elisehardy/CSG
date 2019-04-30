/** @file object.c
 *
 *  @brief Contains the definition of the **Object**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#include <errno.h>
#include "../include/object.h"


Object *mergeObject(Object *a, Object *b) {
    if (a == NULL || b == NULL) {
        errno = EFAULT;
        perror("Error - mergeObject ");
        exit(1);
    }
    
    Object *obj = malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - mergeObject ");
        exit(1);
    }
    
    obj->n = 0;
    obj->p = 0;
    obj->shape = SHP_COMPOSITE;
    obj->size = a->size + b->size;
    obj->drawData = malloc(sizeof(DrawData) * obj->size);
    if (obj->drawData == NULL) {
        errno = ENOMEM;
        perror("Error - mergeObject ");
        exit(1);
    }
    
    memcpy(obj->drawData, a->drawData, a->size * sizeof(DrawData));
    memcpy(obj->drawData + a->size, b->drawData, b->size * sizeof(DrawData));
    free(a->drawData);
    free(b->drawData);
    
    return obj;
}


void freeObject(Object *obj) {
    if (obj == NULL) {
        return;
    }
    
    free(obj->drawData);
    free(obj);
}



