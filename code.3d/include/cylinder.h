#ifndef CSG_CYLINDER_H
#define CSG_CYLINDER_H

#include "object.h"


typedef Object Cylinder;


/**
 * Build a cylinder with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cylinder *buildRandomCylinder(int n, int p);

#endif
