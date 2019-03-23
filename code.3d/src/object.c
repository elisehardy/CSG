#include "../include/object.h"

#include "../include/cone.h"
#include "../include/cube.h"
#include "../include/cylinder.h"
#include "../include/sphere.h"
#include "../include/torus.h"
#include "../include/matrix.h"


Object sphere, cube, torus, cone, cylinder;


void init(void) {
    sphere.n = 1000;
    sphere.p = 1000;
    sphere.size = sphere.n * sphere.p;
    buildRandomSphere(&sphere);
    
    cube.n = 400;
    cube.p = 400;
    cube.size = 6 * cube.n * cube.p;
    buildRandomCube(&cube);
    
    torus.n = 1000;
    torus.p = 400;
    torus.size = torus.n * torus.p;
    buildRegularTorus(&torus);
    
    cone.n = 1000;
    cone.p = 400;
    cone.size = cone.n * cone.p;
    buildRegularCone(&cone);
}


void draw(void) {
    g3x_Material(G3Xr, 0.25, 0.5, 0.5, 0.5, 1.);
    /*drawSphere(&sphere,1);*/
    /*drawCube(&cube, 1);*/
    drawTorus(&torus, 1);
    /*drawCone(&cone, 1);*/
}


void drawObject(Object *obj, int c) {
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
