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
 * @param obj The object being rotated.
 * @param x Distance the object will be moved alongside the X.
 * @param y Distance the object will be moved alongside the Y.
 * @param z Distance the object will be moved alongside the Z.
 */
void translate(Object *obj, double x, double y, double z);

/**
 * Apply an homothety the given object alongside each axis by the given ratio.
 *
 * @param obj The object being dilated.
 * @param x Ratio the object will be dilated alongside the X.
 * @param y Ratio the object will be dilated alongside the Y.
 * @param z Ratio the object will be dilated alongside the Z.
 */
void homothate(Object *obj, double x, double y, double z);

/**
 * Print the given matrix.
 *
 * @param m Matrix (4x4) to be printed.
 */
void printMatrix(double *m);

/**
 * Print the given point/vector.
 *
 * @param c Point/vector be printed.
 */
void printCoord(G3Xcoord c);

#endif
