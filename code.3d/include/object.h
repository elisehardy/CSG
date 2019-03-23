#ifndef CSG_OBJECT_H
#define CSG_OBJECT_H

#include <g3x.h>
#include <g3x_basix.h>


/**
 * Canonical shapes.
 */
typedef enum {
    SHP_SPHERE, SHP_CUBE, SHP_CYLINDER, SHP_CONE, SHP_TORUS
} Shape;


/**
 * Represents a 3D canonic object.
 */
typedef struct _obj {
    Shape shape; /**< Shape of the Object */
    G3Xpoint *vertex; /**< Vertexes of the Object */
    G3Xvector *normal; /**< Normals of the Object */
    bool (*pt_in)(struct _obj *, G3Xpoint); /**< ? */
    bool (*build)(struct _obj *); /**< ? */
    int n, p, size; /**< Custom parameters */
    
} Object;


void init(void);

void draw(void);

void drawObject(Object *s, int c);

#endif
