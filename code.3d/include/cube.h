#ifndef CSG_CUBE_H
#define CSG_CUBE_H

#include "object.h"


typedef Object Cube;


/**
 * Build a cube with a standard distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cube *buildRegularCube(int n, int p);

/**
 * Build a cube with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cube *buildRandomCube(int n, int p);

/**
 * Check if a point is inside or on a cube.
 *
 * @param cube The cube the point will be checked against.
 * @param p The point being checked.
 *
 * @return true if the point is inside or on the cube, false otherwise.
 */
bool insideCube( G3Xpoint p);

/**
 * Draw a regular cube.
 *
 * @param cube The cube.
 * @param c ?
 */
void drawCube(Cube *cube, int c);

#endif
