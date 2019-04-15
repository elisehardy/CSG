#ifndef CSG_TORE_H
#define CSG_TORE_H

#include "object.h"


typedef Object Torus;


/**
 * Build a torus with a standard distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Torus *buildRegularTorus(int n, int p);

/**
 * Build a torus with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Torus *buildRandomTorus(int n, int p, int innerRadius, int outerRadius);

/**
 * Check if a point is inside or on a torus.
 *
 * @param torus The torus the point will be checked against.
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the torus, false otherwise.
 */
bool insideTorus( G3Xpoint p);

/**
 * Draw a regular torus.
 *
 * @param torus The torus.
 * @param c ?
 */
void drawTorus(Torus *torus, int cam);

#endif
