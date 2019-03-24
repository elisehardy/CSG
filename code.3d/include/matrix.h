#ifndef CSG_MATRIX_H
#define CSG_MATRIX_H

#include "object.h"


/**
 * Compute the multiplication m = factor * m.
 *
 * Both matrix must be 4x4 and represented as an array of 16 doubles.
 *
 * @param m The matrix being multiplied.
 * @param factor The matrix by which m will be multiplied.
 */
void matrixMatrixMult(double *m, double *factor);

/**
 * Compute the multiplication p = factor * p.
 *
 * @param p The point being multiplied.
 * @param factor The matrix by which p will be multiplied. Must be 4x4 and represented as an array
 * of 16 doubles.
 */
void matrixCoordMult(double *factor, G3Xpoint p);

/**
 * Rotate the given object around each axis by the angles given.
 *
 * @param obj The object being rotated.
 * @param x Angle (in radian) of rotation around the X axis.
 * @param y Angle (in radian) of rotation around the Y axis.
 * @param z Angle (in radian) of rotation around the Z axis.
 */
void rotate(Object *obj, double x, double y, double z);

/**
 * Translate the given object alongside each axis by the distance given.
 *
 * @param obj The object being translated.
 * @param x Distance the object will be moved alongside the X.
 * @param y Distance the object will be moved alongside the Y.
 * @param z Distance the object will be moved alongside the Z.
 */
void translate(Object *obj, double x, double y, double z);

#endif

