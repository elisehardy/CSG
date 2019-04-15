#include "../include/cube.h"


Cube *buildRegularCube(int n, int p) { /*a changer car faire une normal pour chaque point*/
    Cube *cube = (Object *) malloc(sizeof(Object));
    if (cube == NULL) {
        errno = ENOMEM;
        perror("Error - buildRegularCube ");
        exit(1);
    }
    
    double cubeN, cubeP, idouble, jdouble;
    int i, j;
    
    cube->n = n;
    cube->p = p;
    cube->size = n * p * 6;
    cube->shape = SHP_CUBE;
    cube->vertex = (G3Xpoint *) calloc(cube->size, sizeof(G3Xpoint));
    cube->normal = (G3Xvector *) calloc(cube->size, sizeof(G3Xvector));
    if (!(cube->vertex && cube->normal)) {
        errno = ENOMEM;
        perror("Error - buildRegularCube ");
        exit(1);
    }
    
    cubeN = (double) cube->n;
    cubeP = (double) cube->p;
    
    cube->normal[0][X] = 0.;
    cube->normal[0][Y] = 0.;
    cube->normal[0][Z] = 1.;
    
    cube->normal[1][X] = 0.;
    cube->normal[1][Y] = 0.;
    cube->normal[1][Z] = -1.;
    
    cube->normal[2][X] = 0.;
    cube->normal[2][Y] = 1.;
    cube->normal[2][Z] = 0.;
    
    cube->normal[3][X] = 0.;
    cube->normal[3][Y] = -1.;
    cube->normal[3][Z] = 0.;
    
    cube->normal[4][X] = 1.;
    cube->normal[4][Y] = 0.;
    cube->normal[4][Z] = 0.;
    
    cube->normal[5][X] = -1.;
    cube->normal[5][Y] = 0.;
    cube->normal[5][Z] = 0.;
    
    for (i = 0; i < cube->n; i++) {
        idouble = (double) i;
        for (j = 0; j < cube->p; j++) {
            jdouble = (double) j;
            cube->vertex[i * (cube->p) + j][0] = 2 * idouble / cubeN - 1;
            cube->vertex[i * (cube->p) + j][1] = 2 * jdouble / cubeP - 1;
            cube->vertex[i * (cube->p) + j][2] = 1.;
            
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 1 + j][0] = 2 * idouble / cubeN - 1;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 1 + j][1] = 2 * jdouble / cubeP - 1;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 1 + j][2] = -1.;
            
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 2 + j][0] = 2 * idouble / cubeN - 1;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 2 + j][1] = 1.;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 2 + j][2] = 2 * jdouble / cubeP - 1;
            
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 3 + j][0] = 2 * idouble / cubeN - 1;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 3 + j][1] = -1.;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 3 + j][2] = 2 * jdouble / cubeP - 1;
            
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 4 + j][0] = 1.;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 4 + j][1] = 2 * idouble / cubeN - 1;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 4 + j][2] = 2 * jdouble / cubeP - 1;
            
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 5 + j][0] = -1.;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 5 + j][1] = 2 * idouble / cubeN - 1;
            cube->vertex[i * (cube->p) + (cube->p) * (cube->n) * 5 + j][2] = 2 * jdouble / cubeP - 1;
        }
    }
    
    return cube;
}


Cube *buildRandomCube(int n, int p) {
    Cube *cube = (Object *) malloc(sizeof(Object));
    if (cube == NULL) {
        errno = ENOMEM;
        perror("Error - buildRandomCube ");
        exit(1);
    }
    
    G3Xvector *normals;
    G3Xpoint *vertices;
    int i;
    
    cube->n = n;
    cube->p = p;
    cube->size = n * p * 6;
    cube->shape = SHP_CUBE;
    cube->vertex = (G3Xpoint *) calloc(cube->size, sizeof(G3Xpoint));
    cube->normal = (G3Xvector *) calloc(cube->size, sizeof(G3Xvector));
    if (!(cube->vertex && cube->normal)) {
        errno = ENOMEM;
        perror("Error - buildRandomCube ");
        exit(1);
    }
    
    vertices = cube->vertex;
    normals = cube->normal;
    
    for (i = 0; i < ((cube->size) / 6); i++) {
        (*vertices)[0] = g3x_Rand_Delta(0, 1);
        (*vertices)[1] = g3x_Rand_Delta(0, 1);
        (*vertices)[2] = +1.;
        vertices++;
        
        (*vertices)[0] = g3x_Rand_Delta(0, 1);
        (*vertices)[1] = g3x_Rand_Delta(0, 1);
        (*vertices)[2] = -1.;
        vertices++;
        
        (*vertices)[0] = g3x_Rand_Delta(0, 1);
        (*vertices)[1] = +1.;
        (*vertices)[2] = g3x_Rand_Delta(0, 1);
        vertices++;
        
        (*vertices)[0] = g3x_Rand_Delta(0, 1);
        (*vertices)[1] = -1.;
        (*vertices)[2] = g3x_Rand_Delta(0, 1);
        vertices++;
        
        (*vertices)[0] = +1.;
        (*vertices)[1] = g3x_Rand_Delta(0, 1);
        (*vertices)[2] = g3x_Rand_Delta(0, 1);
        vertices++;
        
        (*vertices)[0] = -1.;
        (*vertices)[1] = g3x_Rand_Delta(0, 1);
        (*vertices)[2] = g3x_Rand_Delta(0, 1);
        vertices++;
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = +1.;
        normals++;
        
        (*normals)[0] = 0;
        (*normals)[1] = 0;
        (*normals)[2] = -1.;
        normals++;
        
        (*normals)[0] = 0;
        (*normals)[1] = +1.;
        (*normals)[2] = 0;
        normals++;
        
        (*normals)[0] = 0;
        (*normals)[1] = -1.;
        (*normals)[2] = 0;
        normals++;
        
        (*normals)[0] = +1.;
        (*normals)[1] = 0;
        (*normals)[2] = 0;
        normals++;
        
        (*normals)[0] = -1.;
        (*normals)[1] = 0;
        (*normals)[2] = 0;
        normals++;
    }
    
    return cube;
}


void drawCube(Cube *cube, int c) {
    if (cube == NULL) {
        errno = EFAULT;
        perror("Error - drawCube ");
        exit(1);
    }
    
    G3Xvector *n = cube->normal;
    G3Xpoint *v = cube->vertex;
    int cote, face, i, j;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    
    for (face = 0; face < 6; face++) {
        for (i = 0; i < cube->n; i += c) {
            for (j = 0; j < cube->p; j += c) {
                glNormal3dv(n[face]);
                glVertex3dv(v[face * (cube->n) * (cube->p) + j + i * (cube->p)]);
            }
            
            glNormal3dv(n[face]);
            glVertex3dv(v[face * (cube->n) * (cube->p) + i * (cube->p) + (cube->p - 1)]);
        }
        
        for (cote = 0; cote < cube->p; cote += c) {
            glNormal3dv(n[face]);
            glVertex3dv(v[face * (cube->n) * (cube->p) + (cube->p) * (cube->n - 1) + cote]);
        }
        
        glNormal3dv(n[face]);
        glVertex3dv(v[face * (cube->n) * (cube->p) + (cube->p) * (cube->n - 1) + (cube->p - 1)]);
    }
    
    glEnd();
}


bool insideCube( G3Xpoint p) {
  
    
    return MAX(abs(p[0]), MAX(abs(p[1]), abs(p[2]))) <= 1;
}




