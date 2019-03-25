#include "../include/cone.h"


Object *buildRegularCone(int n, int p) {
    Object *obj = (Object *) malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - buildRegularCone ");
        exit(1);
    }
    
    double idouble, jdouble, objN, objP;
    int i, j;
    
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(2 + obj->n, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularCone ");
        exit(1);
    }
    
    objN = (double) obj->n;
    objP = (double) obj->p;
    
    obj->vertex[0][X] = 0.;
    obj->vertex[0][Y] = 0.;
    obj->vertex[0][Z] = 1.;
    
    obj->vertex[1][X] = 0.;
    obj->vertex[1][Y] = 0.;
    obj->vertex[1][Z] = 0.;
    
    obj->normal[0][X] = 0.;
    obj->normal[0][Y] = 0.;
    obj->normal[0][Z] = 1.;
    
    obj->normal[1][X] = 0.;
    obj->normal[1][Y] = 0.;
    obj->normal[1][Z] = -1.;
    
    for (i = 2; i < obj->p; i++) {
        idouble = (double) i;
        for (j = 0; j < obj->n; j++) {
            jdouble = (double) j;
            obj->vertex[i * (obj->n) + j][0] =
                    cos(PI * 2 * jdouble / objN) * ((idouble + 1.) / objP);
            obj->vertex[i * (obj->n) + j][1] =
                    sin(PI * 2 * jdouble / objN) * ((idouble + 1.) / objP);
            obj->vertex[i * (obj->n) + j][2] = -1;
        }
    }
    
    return obj;
}


Object *buildRandomCone(int n, int p) {
    Object *obj = (Object *) malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCone ");
        exit(1);
    }
    
    double theta, z;
    int i, j;
    
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(2 + obj->n, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularCone ");
        exit(1);
    }
    
    for (i = 0; i < obj->p; i++) {
        for (j = 0; j < obj->n; j++) {
            z = -sqrt(g3x_Rand_Delta(0, 1));
            theta = g3x_Rand_Delta(0, 2 * PI);
            obj->vertex[i * (obj->n) + j][0] = z * cos(theta);
            obj->vertex[i * (obj->n) + j][1] = z * sin(theta);
            obj->vertex[i * (obj->n) + j][2] = z;
            
            obj->normal[i * (obj->n) + j][0] = cos(theta);
            obj->normal[i * (obj->n) + j][1] = sin(theta);
            obj->normal[i * (obj->n) + j][2] = 1;
        }
    }
    
    return obj;
}


void drawCone(Object *obj, int c) {
    if (obj == NULL) {
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
