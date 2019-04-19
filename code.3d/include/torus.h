#ifndef CSG_TORE_H
#define CSG_TORE_H

#include "object.h"


typedef Object Torus;


/**
 * Build a torus with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Torus *buildRandomTorus(int n, int p, int innerRadius, int outerRadius);

#endif
