#include "../include/torus.h"


void buildRegularTorus(Object *obj) {
    double idouble, jdouble, cosa, sina;
    double objN = (double) obj->n;
    double objP = (double) obj->p;
    int i, j;
    
    obj->shape = SHP_TORUS;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        perror("Could not allocate object");
        exit(1);
    }
    
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
}


void drawTorus(Object *obj, int cam) {
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
