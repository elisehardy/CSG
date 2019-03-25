#include "../include/object.h"

#include "../include/cone.h"
#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"
#include "../include/matrix.h"


Object *sphere, *cube, *torus, *cone, *cylinder;


void init(void) {
    sphere = buildRandomSphere(1000, 1000);
    homothate(sphere, 0.5, 0.5, 0.5);
    
    cube = buildRandomCube(1000, 1000);
    /*rotate(&cube, PI/4, 0, 0);*/
    /*translate(&cube, 1, 1, 1);*/
    
    torus = buildRegularTorus(1000, 400);
    
    cone = buildRegularCone(1000, 400);
}


void draw(void) {
    g3x_Material(G3Xr, 0.25, 0.5, 0.5, 0.5, 1.);
    drawSphere(sphere, 1);
    /*drawCube(&cube, 1);*/
    /*drawTorus(&torus, 1);*/
    /*drawCone(&cone, 1);*/
}


void drawObject(Object *obj, int c) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - drawObject ");
        exit(1);
    }
    
    G3Xvector *n = obj->normal;
    G3Xpoint *v = obj->vertex;
    
    glPointSize(1);
    glBegin(GL_POINTS);
    
    while (v < obj->vertex + obj->size) {
        glNormal3dv(*n);
        n += c;
        glVertex3dv(*v);
        v += c;
    }
    
    glEnd();
}
