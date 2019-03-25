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
    int i;
    
    obj->size = n*p;
    obj->n = n;
    obj->p=p;
    obj->vertex = (G3Xpoint *) calloc(obj->size, sizeof(G3Xpoint));
    obj->normal = (G3Xvector *) calloc(obj->size, sizeof(G3Xvector));
    if (!(obj->vertex && obj->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomCone vertex normal");
        exit(1);
    }
    G3Xpoint *vertices = obj->vertex;
    G3Xvector *normals = obj->normal;
    double d;
    for (i = 0; i < obj->size/2; i++) {
        
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
        
             do{
            (*vertices)[0] = g3x_Rand_Delta(0, +1);
            (*vertices)[1] = g3x_Rand_Delta(0, +1);
           
            d = (*vertices)[0] * (*vertices)[0] + (*vertices)[1] * (*vertices)[1];
        }while(d>1); 
            
            (*normals)[0] = 0;
            (*normals)[1]=0;
            (*normals)[2]=-1;
            
             (*vertices)[2] = -1;
            vertices++;
            normals++;
            
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
