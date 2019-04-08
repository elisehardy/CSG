#ifndef CSG_CYLINDER_H
#define CSG_CYLINDER_H

#include "object.h"


typedef Object Cylinder;


/**
 * Build a cylinder with a standard distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cylinder *buildRegularCylinder(int n, int p);

/**
 * Build a cylinder with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cylinder *buildRandomCylinder(int n, int p);

/**
 * Check if a point is inside or on a cylinder.
 *
 * @param cylinder The cylinder the point will be checked against.
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the cylinder, false otherwise.
 */
bool insideCylinder(Cylinder *cylinder, G3Xpoint p);

#endif
