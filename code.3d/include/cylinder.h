/** @file cylinder.h
 *
 *  @brief Header for the **Cylinder** definition and functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */


#ifndef CSG_CYLINDER_H
#define CSG_CYLINDER_H

#include "object.h"


typedef Object Cylinder;


/**
 * @brief  Build a cylinder with an uniform distribution of vertices.
 *
 * @param n ?
 * @param p ?
 */
Cylinder *buildRandomCylinder(int n, int p);

#endif
