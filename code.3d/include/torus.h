/** @file torus.h
 *
 *  @brief Header for the **Torus** definition and functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */


#ifndef CSG_TORE_H
#define CSG_TORE_H

#include "object.h"


typedef Object Torus;


/**
 * @brief Build a torus with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Torus *buildRandomTorus(int n, int p, int innerRadius, int outerRadius);

#endif
