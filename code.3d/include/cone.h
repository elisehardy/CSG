#ifndef CSG_CONE_H
#define CSG_CONE_H

#include "object.h"


/**
 * Build a sphere with an uniform distribution of vertices.
 *
 * @param n Number of meridian.
 * @param p Number of parallels.
 */
Object *buildRegularCone(int n, int p);

Object *buildRandomCone(int n, int p);

bool insideCone(Object *obj, G3Xcoord);

void drawCone(Object *obj, int c);

#endif
