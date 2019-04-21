/** @file cone.h
 *
 *  @brief Header for the **Cone** definition and functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#ifndef CSG_CONE_H
#define CSG_CONE_H

#include "object.h"


typedef Object Cone;


/**
 * @brief Build a cone with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cone *buildRandomCone(int n, int p);

#endif
