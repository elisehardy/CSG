#ifndef CSG_CONE_H
#define CSG_CONE_H

#include "object.h"


typedef Object Cone;


/**
 * Build a cone with a standard distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cone *buildRegularCone(int n, int p);

/**
 * Build a cone with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cone *buildRandomCone(int n, int p);

/**
 * Check if a point is inside or on a cone.
 *
 * @param cone The cone the point will be checked against.
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the cone, false otherwise.
 */
bool insideCone(G3Xpoint p);

/**
 * Draw a regular cone.
 *
 * @param cone The cone.
 * @param c ?
 */
void drawRegularCone(Cone *cone, int c);

#endif
