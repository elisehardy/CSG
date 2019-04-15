#include "../include/torus.h"


Torus *buildRegularTorus(int n, int p) {
    Torus *torus = (Object *) malloc(sizeof(Object));
    if (torus == NULL) {
        errno = ENOMEM;
        perror("Error - buildRegularTorus ");
        exit(1);
    }
    
    double idouble, jdouble, cosa, sina, torusN, torusP;
    int i, j;
    
    torus->n = n;
    torus->p = p;
    torus->size = n * p;
    torus->shape = SHP_TORUS;
    torus->vertex = (G3Xpoint *) calloc(torus->size, sizeof(G3Xpoint));
    torus->normal = (G3Xvector *) calloc(torus->size, sizeof(G3Xvector));
    if (!(torus->vertex && torus->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularTorus ");
        exit(1);
    }
    
    torusN = (double) torus->n;
    torusP = (double) torus->p;
    
    for (i = 0; i < torus->p; i++) {
        idouble = (double) i;
        cosa = cos(2. * idouble * PI / torusP);
        sina = sin(2. * idouble * PI / torusP);
        
        for (j = 0; j < torus->n; j++) {
            jdouble = (double) j;
            torus->vertex[i * (torus->n) + j][0] = (3. + cos(2. * jdouble * PI / torusN)) * cosa;
            torus->vertex[i * (torus->n) + j][1] = (3. + cos(2. * jdouble * PI / torusN)) * sina;
            torus->vertex[i * (torus->n) + j][2] = sin(2. * jdouble * PI / torusN);
            
            torus->normal[i * (torus->n) + j][0] = cos(2. * jdouble * PI / torusN) * cosa;
            torus->normal[i * (torus->n) + j][1] = cos(2. * jdouble * PI / torusN) * sina;
            torus->normal[i * (torus->n) + j][2] = sin(2. * jdouble * PI / torusN);
        }
    }
    
    return torus;
}


/* TODO : Normals not done yet */
Torus *buildRandomTorus(int n, int p, int innerRadius, int outerRadius) {
    Torus *torus = (Object *) malloc(sizeof(Object));
    if (torus == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomorus ");
        exit(1);
    }
    
    int i;
    double theta, phi;
    
    torus->n = n;
    torus->p = p;
    torus->size = n * p;
    torus->shape = SHP_TORUS;
    torus->vertex = (G3Xpoint *) calloc(torus->size, sizeof(G3Xpoint));
    torus->normal = (G3Xvector *) calloc(torus->size, sizeof(G3Xvector));
    if (!(torus->vertex && torus->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomTorus ");
        exit(1);
    }
    
    G3Xpoint *vertices = torus->vertex;
    
    for (i = 0; i < torus->size; i++) {
        theta = g3x_Rand_Delta(0, 0.5) * 2 * PI;
        phi = g3x_Rand_Delta(0, 0.5) * 2 * PI;
        
        (*vertices)[0] = (outerRadius + innerRadius * cos(phi)) * cos(theta);
        (*vertices)[1] = (outerRadius + innerRadius * cos(phi)) * sin(theta);
        
        (*vertices)[2] = innerRadius * sin(phi);
        
        vertices++;
    }
    
    return torus;
}


void drawTorus(Torus *torus, int cam) {
    if (torus == NULL) {
        errno = EFAULT;
        perror("Error - drawTorus ");
        exit(1);
    }
    
    G3Xvector *n = torus->normal;
    G3Xpoint *v = torus->vertex;
    int i, j;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    
    for (i = 0; i < torus->p; i += cam) {
        for (j = 0; j < torus->n; j += cam) {
            glNormal3dv(n[i * (torus->n) + j]);
            glVertex3dv(v[i * (torus->n) + j]);
        }
    }
    
    glEnd();
}


bool insideTorus( G3Xpoint p) {
   
    
    return (sqrt(p[0] * p[0] + p[1] * p[1]) - 2) * (sqrt(p[0] * p[0] + p[1] * p[1]) - 2) + p[2] * p[2] < 1;
}
