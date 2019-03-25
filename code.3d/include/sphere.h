#ifndef CSG_SPHERE_H
#define CSG_SPHERE_H

#include "object.h"


/**
 * Build a sphere with regular positionning of vertices.
 *
 * @param n Number of meridian.
 * @param p Number of parallels.
 */
Object *buildRegularSphere(int n, int p);

/**
 * Build a sphere with an uniform distribution of vertices.
 *
 * @param n Number of meridian.
 * @param p Number of parallels.
 */
Object *buildRandomSphere(int n, int p);

/**
 * Draw a sphere.
 *
 * @param obj The sphere which will be drawn.
 * @param c ?
 */
void drawSphere(Object *obj, int c);

#endif
