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

#endif
