#ifndef CSG_CONE_H
#define CSG_CONE_H

#include "object.h"


typedef Object Cone;


/**
 * Build a cone with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cone *buildRandomCone(int n, int p);

#endif
