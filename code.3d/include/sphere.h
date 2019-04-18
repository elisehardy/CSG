#ifndef CSG_SPHERE_H
#define CSG_SPHERE_H

#include "object.h"


typedef Object Sphere;


/**
 * Build a sphere with an uniform distribution of vertices.
 *
 * @param n Number of meridian.
 * @param p Number of parallels.
 */
Sphere *buildRandomSphere(int n, int p);

#endif
