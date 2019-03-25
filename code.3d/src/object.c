#include "../include/object.h"

#include "../include/cone.h"
#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"
#include "../include/matrix.h"


Object *sphere, *cube, *torus, *cone, *cylinder;







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


void init(void) {
   /* sphere = buildRandomSphere(1000, 1000);
    cube = buildRandomCube(1000, 1000);
    torus = buildRegularTorus(1000, 400);*/
    cone = buildRandomCone(400, 400);
    /*cylinder = buildRandomCylinder(400,400);*/
}


void draw(void) {
    g3x_Material(G3Xr, 0.25, 0.5, 0.5, 0.5, 1.);
    /*drawObject(sphere, 1);*/
    drawObject(cone, 1);
    /*drawObject(cylinder,1);*/
}
