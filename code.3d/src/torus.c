#include "../include/torus.h"


Object *buildRegularTorus(int n, int p) {
    Object *obj = (Object *) malloc(sizeof(Object));
    if (obj == NULL) {
        errno = ENOMEM;
        perror("Error - buildRegularTorus ");
        exit(1);
    }
    
    double idouble, jdouble, cosa, sina, objN, objP;
    int i, j;
    
    obj->n = n;
    obj->p = p;
    obj->size = n * p;
    obj->shape = SHP_TORUS;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularTorus ");
        exit(1);
    }
    
    objN = (double) obj->n;
    objP = (double) obj->p;
    
    for (i = 0; i < obj->p; i++) {
        idouble = (double) i;
        cosa = cos(2. * idouble * PI / objP);
        sina = sin(2. * idouble * PI / objP);
        
        for (j = 0; j < obj->n; j++) {
            jdouble = (double) j;
            obj->vertex[i * (obj->n) + j][0] = (3. + cos(2. * jdouble * PI / objN)) * cosa;
            obj->vertex[i * (obj->n) + j][1] = (3. + cos(2. * jdouble * PI / objN)) * sina;
            obj->vertex[i * (obj->n) + j][2] = sin(2. * jdouble * PI / objN);
            
            obj->normal[i * (obj->n) + j][0] = cos(2. * jdouble * PI / objN) * cosa;
            obj->normal[i * (obj->n) + j][1] = cos(2. * jdouble * PI / objN) * sina;
            obj->normal[i * (obj->n) + j][2] = sin(2. * jdouble * PI / objN);
        }
    }
    
    return obj;
}


void drawTorus(Object *obj, int cam) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - drawTorus ");
        exit(1);
    }
    
    G3Xvector *n = obj->normal;
    G3Xpoint *v = obj->vertex;
    int i, j;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    
    for (i = 0; i < obj->p; i += cam) {
        for (j = 0; j < obj->n; j += cam) {
            glNormal3dv(n[i * (obj->n) + j]);
            glVertex3dv(v[i * (obj->n) + j]);
        }
    }
    
    glEnd();
}
