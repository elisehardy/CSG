#ifndef CSG_SPHERE_H
#define CSG_SPHERE_H

#include "object.h"


typedef Object Sphere;


/**
 * Build a sphere with a standard distribution of vertices.
 *
 * @param n Number of meridian.
 * @param p Number of parallels.
 */
Sphere *buildRegularSphere(int n, int p);

/**
 * Build a sphere with an uniform distribution of vertices.
 *
 * @param n Number of meridian.
 * @param p Number of parallels.
 */
Sphere *buildRandomSphere(int n, int p);

/**
 * Check if a point is inside or on a sphere.
 *
 * @param sphere The sphere the point will be checked against.
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the sphere, false otherwise.
 */
bool insideSphere( G3Xpoint p);

#endif
