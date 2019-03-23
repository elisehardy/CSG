#ifndef CSG_SPHERE_H
#define CSG_SPHERE_H

#include "object.h"


/**
 * Build a sphere with regular alignment of vertices.
 *
 * @param obj The Object in which the Sphere will be placed.
 */
void buildRegularSphere(Object *obj);

/**
 * Build a sphere with randomly distributed vertices.
 *
 * @param obj The Object in which the Sphere will be placed.
 */
void buildRandomSphere(Object *obj);

/**
 * Draw a sphere.
 *
 * @param obj The sphere which will be drawn.
 * @param c ?
 */
void drawSphere(Object *obj, int c);

#endif
