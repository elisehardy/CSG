#include "../include/cone.h"


void buildRegularCone(Object *obj) {
    if (!obj) {
        errno = EFAULT;
        perror("Error - buildRegularCone ");
        exit(1);
    }
    
    double objN = (double) obj->n;
    double objP = (double) obj->p;
    double idouble;
    int i, j;
    
    obj->shape = SHP_CONE;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularCone ");
        exit(1);
    }
    
    for (i = 2; i < obj->p; i++) {
        idouble = (double) i;
        for (j = 0; j < obj->n; j++) {
            obj->vertex[i * (obj->n) + j][0] =
                    cos(PI * 2 * idouble / objN) * ((idouble + 1.) / objP);
            obj->vertex[i * (obj->n) + j][1] =
                    sin(PI * 2 * idouble / objN) * ((idouble + 1.) / objP);
            obj->vertex[i * (obj->n) + j][2] = -1;
            
            obj->normal[i * (obj->n) + j][0] = obj->vertex[i * (obj->n) + j][0];
            obj->normal[i * (obj->n) + j][1] = obj->vertex[i * (obj->n) + j][1];
            obj->normal[i * (obj->n) + j][2] = 1;
        }
    }
}


void drawCone(Object *obj, int c) {
    if (!obj) {
        errno = EFAULT;
        perror("Error - drawCone ");
        exit(1);
    }
    
    G3Xpoint *v = obj->vertex;
    int i, j;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    
    glVertex3dv(obj->vertex[0]);
    glVertex3dv(obj->vertex[1]);
    
    glNormal3dv(obj->normal[0]);
    glNormal3dv(obj->normal[1]);
    
    for (i = 0; i < obj->p; i += c) {
        for (j = 0; j < obj->n; j += c) {
            glVertex3dv(v[i * (obj->n) + j]);
        }
    }
    
    glEnd();
}
