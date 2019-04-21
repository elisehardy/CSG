/** @file cube.h
 *
 *  @brief Header for the **Cube** definition and functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */


#ifndef CSG_CUBE_H
#define CSG_CUBE_H

#include "object.h"


typedef Object Cube;


/**
 * @brief Build a cube with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cube *buildRandomCube(int n, int p);

#endif
