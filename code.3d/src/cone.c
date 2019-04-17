#include <errno.h>
#include "../include/cone.h"


Cone *buildRegularCone(int n, int p) {
    Cone *cone = (Object *) malloc(sizeof(Object));
    if (cone == NULL) {
        errno = ENOMEM;
        perror("Error - buildRegularCone ");
        exit(1);
    }
    
    double idouble, jdouble, coneN, coneP;
    int i, j;
    
    cone->n = n;
    cone->p = p;
    cone->size = n * p;
    cone->shape = SHP_CONE;
    cone->vertex = (G3Xpoint *) calloc(cone->size, sizeof(G3Xpoint));
    cone->normal = (G3Xvector *) calloc(2 + cone->n, sizeof(G3Xvector));
    if (!(cone->vertex && cone->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularCone ");
        exit(1);
    }
    
    coneN = (double) cone->n;
    coneP = (double) cone->p;
    
    cone->vertex[0][X] = 0.;
    cone->vertex[0][Y] = 0.;
    cone->vertex[0][Z] = 1.;
    
    cone->vertex[1][X] = 0.;
    cone->vertex[1][Y] = 0.;
    cone->vertex[1][Z] = 0.;
    
    cone->normal[0][X] = 0.;
    cone->normal[0][Y] = 0.;
    cone->normal[0][Z] = 1.;
    
    cone->normal[1][X] = 0.;
    cone->normal[1][Y] = 0.;
    cone->normal[1][Z] = -1.;
    
    for (i = 2; i < cone->p; i++) {
        idouble = (double) i;
        for (j = 0; j < cone->n; j++) {
            jdouble = (double) j;
            cone->vertex[i * (cone->n) + j][0] = cos(PI * 2 * jdouble / coneN) * ((idouble + 1.) / coneP);
            cone->vertex[i * (cone->n) + j][1] = sin(PI * 2 * jdouble / coneN) * ((idouble + 1.) / coneP);
            cone->vertex[i * (cone->n) + j][2] = -1;
        }
    }
    
    return cone;
}


Cone *buildRandomCone(int n, int p) {
    Cone *cone = (Object *) malloc(sizeof(Object));
    if (cone == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCone ");
        exit(1);
    }
    
    double theta, z;
    int i;
    
    cone->n = n;
    cone->p = p;
    cone->size = n * p;
    cone->shape = SHP_CONE;
    cone->vertex = (G3Xpoint *) calloc(cone->size, sizeof(G3Xpoint));
    cone->normal = (G3Xvector *) calloc(cone->size, sizeof(G3Xvector));
    if (!(cone->vertex && cone->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomCone ");
        exit(1);
    }
    G3Xpoint *vertices = cone->vertex;
    G3Xvector *normals = cone->normal;
    double d;
    for (i = 0; i < cone->size / 2; i++) {
        
        z = -sqrt(g3x_Rand_Delta(0, 1));
        theta = g3x_Rand_Delta(0, 2 * PI);
        (*vertices)[0] = z * cos(theta);
        (*vertices)[1] = z * sin(theta);
        (*vertices)[2] = z;
        
        (*normals)[0] = cos(theta);
        (*normals)[1] = sin(theta);
        (*normals)[2] = 1;
        vertices++;
        normals++;
        
        do {
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
            
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        } while (d > 1);
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = -1;
        
        (*vertices)[2] = -1;
        vertices++;
        normals++;
    }
    
    return cone;
}


void drawRegularCone(Cone *cone, int c) {
    if (cone == NULL) {
        errno = EFAULT;
        perror("Error - drawCone ");
        exit(1);
    }
    
    G3Xpoint *v = cone->vertex;
    int i, j;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    
    glVertex3dv(cone->vertex[0]);
    glVertex3dv(cone->vertex[1]);
    
    glNormal3dv(cone->normal[0]);
    glNormal3dv(cone->normal[1]);
    
    for (i = 0; i < cone->p; i += c) {
        for (j = 0; j < cone->n; j += c) {
            glVertex3dv(v[i * (cone->n) + j]);
        }
    }
    
    glEnd();
}
