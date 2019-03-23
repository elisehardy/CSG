#include "../include/cube.h"


void buildRegularCube(Object *obj) { /*a changer car faire une normal pour chaque point*/
    double objN = (double) obj->n;
    double objP = (double) obj->p;
    double idouble, jdouble;
    int i, j;
    
    obj->shape = SHP_CUBE;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        perror("Could not allocate object");
        exit(1);
    }
    
    obj->normal[0][X] = 0.;
    obj->normal[0][Y] = 0.;
    obj->normal[0][Z] = 1.;
    
    obj->normal[1][X] = 0.;
    obj->normal[1][Y] = 0.;
    obj->normal[1][Z] = -1.;
    
    obj->normal[2][X] = 0.;
    obj->normal[2][Y] = 1.;
    obj->normal[2][Z] = 0.;
    
    obj->normal[3][X] = 0.;
    obj->normal[3][Y] = -1.;
    obj->normal[3][Z] = 0.;
    
    obj->normal[4][X] = 1.;
    obj->normal[4][Y] = 0.;
    obj->normal[4][Z] = 0.;
    
    obj->normal[5][X] = -1.;
    obj->normal[5][Y] = 0.;
    obj->normal[5][Z] = 0.;
    
    for (i = 0; i < obj->n; i++) {
        idouble = (double) i;
        for (j = 0; j < obj->p; j++) {
            jdouble = (double) j;
            obj->vertex[i * (obj->p) + j][0] = 2 * idouble / objN - 1;
            obj->vertex[i * (obj->p) + j][1] = 2 * jdouble / objP - 1;
            obj->vertex[i * (obj->p) + j][2] = 1.;
            
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 1 + j][0] = 2 * idouble / objN - 1;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 1 + j][1] = 2 * jdouble / objP - 1;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 1 + j][2] = -1.;
            
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 2 + j][0] = 2 * idouble / objN - 1;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 2 + j][1] = 1.;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 2 + j][2] = 2 * jdouble / objP - 1;
            
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 3 + j][0] = 2 * idouble / objN - 1;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 3 + j][1] = -1.;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 3 + j][2] = 2 * jdouble / objP - 1;
            
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 4 + j][0] = 1.;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 4 + j][1] = 2 * idouble / objN - 1;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 4 + j][2] = 2 * jdouble / objP - 1;
            
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 5 + j][0] = -1.;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 5 + j][1] = 2 * idouble / objN - 1;
            obj->vertex[i * (obj->p) + (obj->p) * (obj->n) * 5 + j][2] = 2 * jdouble / objP - 1;
        }
    }
}


void buildRandomCube(Object *obj) {
    G3Xvector *n;
    G3Xpoint *v;
    int i;
    
    obj->shape = SHP_CUBE;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        perror("Could not allocate object");
        exit(1);
    }
    
    v = obj->vertex;
    n = obj->normal;
    
    for (i = 0; i < ((obj->size) / 6); i++) {
        (*v)[0] = g3x_Rand_Delta(0, 1);
        (*v)[1] = g3x_Rand_Delta(0, 1);
        (*v)[2] = +1;
        v++;
        
        (*v)[0] = g3x_Rand_Delta(0, 1);
        (*v)[1] = g3x_Rand_Delta(0, 1);
        (*v)[2] = -1;
        v++;
        
        (*v)[0] = g3x_Rand_Delta(0, 1);
        (*v)[1] = +1;
        (*v)[2] = g3x_Rand_Delta(0, 1);
        v++;
        
        (*v)[0] = g3x_Rand_Delta(0, 1);
        (*v)[1] = -1;
        (*v)[2] = g3x_Rand_Delta(0, 1);
        v++;
        
        (*v)[0] = +1;
        (*v)[1] = g3x_Rand_Delta(0, 1);
        (*v)[2] = g3x_Rand_Delta(0, 1);
        v++;
        
        (*v)[0] = -1;
        (*v)[1] = g3x_Rand_Delta(0, 1);
        (*v)[2] = g3x_Rand_Delta(0, 1);
        v++;
        
        (*n)[0] = 0;
        (*n)[1] = 0;
        (*n)[2] = +1;
        n++;
        
        (*n)[0] = 0;
        (*n)[1] = 0;
        (*n)[2] = -1;
        n++;
        
        (*n)[0] = 0;
        (*n)[1] = +1;
        (*n)[2] = 0;
        n++;
        
        (*n)[0] = 0;
        (*n)[1] = -1;
        (*n)[2] = 0;
        n++;
        
        (*n)[0] = +1;
        (*n)[1] = 0;
        (*n)[2] = 0;
        n++;
        
        (*n)[0] = -1;
        (*n)[1] = 0;
        (*n)[2] = 0;
        n++;
    }
}


void drawCube(Object *obj, int c) {
    G3Xvector *n = obj->normal;
    G3Xpoint *v = obj->vertex;
    int cote, face, i, j;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    
    for (face = 0; face < 6; face++) {
        for (i = 0; i < obj->n; i += c) {
            for (j = 0; j < obj->p; j += c) {
                glNormal3dv(n[face]);
                glVertex3dv(v[face * (obj->n) * (obj->p) + j + i * (obj->p)]);
            }
            
            glNormal3dv(n[face]);
            glVertex3dv(v[face * (obj->n) * (obj->p) + i * (obj->p) + (obj->p - 1)]);
        }
        
        for (cote = 0; cote < obj->p; cote += c) {
            glNormal3dv(n[face]);
            glVertex3dv(v[face * (obj->n) * (obj->p) + (obj->p) * (obj->n - 1) + cote]);
        }
        
        glNormal3dv(n[face]);
        glVertex3dv(v[face * (obj->n) * (obj->p) + (obj->p) * (obj->n - 1) + (obj->p - 1)]);
    }
    
    glEnd();
}
