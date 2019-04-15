#include "../include/object.h"





void drawObject(Object *obj, int c) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - drawObject ");
        exit(1);
    }
    
    G3Xvector *n = obj->normal;
    G3Xpoint *v = obj->vertex;
    int bit=0;
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






