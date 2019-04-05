#ifndef CSG_CUBE_H
#define CSG_CUBE_H

#include "object.h"


/**
 * Build a cube using regular vertex positionning.
 *
 * @param obj
 */
Object *buildRegularCube(int n, int p);

Object *buildRandomCube(int n, int p);

bool insideCube(Object *obj, G3Xpoint p);

void drawCube(Object *obj, int c);

#endif
