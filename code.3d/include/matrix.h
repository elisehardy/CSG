/** @file matrix.h
 *
 *  @brief Header for the **Matrix** functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#ifndef CSG_MATRIX_H
#define CSG_MATRIX_H

#include "tree.h"


/**
 * @brief Compute the multiplication factor * m.
 *
 * Both matrix must be 4x4 and represented as an array of 16 doubles.
 *
 * @param m The matrix being multiplied.
 * @param factor The matrix by which m will be multiplied.
 *
 * @return The computed matrix.
 */
double *matrixMatrixMult(double *m, double *factor);

/**
 * @brief Compute the multiplication factor * p.
 *
 * @param p The point being multiplied.
 * @param factor The matrix by which p will be multiplied. Must be 4x4 and represented as an array
 * of 16 doubles.
 *
 * @return The computed point.
 */
double *matrixCoordMult(double *factor, G3Xpoint p);

/**
 * @brief Rotate the given node around each axis by the angles given.
 *
 * @param node The node being rotated.
 * @param x Angle (in radian) of rotation around the X axis.
 * @param y Angle (in radian) of rotation around the Y axis.
 * @param z Angle (in radian) of rotation around the Z axis.
 */
void rotate(Tree *node, double x, double y, double z);

/**
 * @brief Translate the given node alongside each axis by the distance given.
 *
 * @param node The node being rotated.
 * @param x Distance the object will be moved alongside the X.
 * @param y Distance the object will be moved alongside the Y.
 * @param z Distance the object will be moved alongside the Z.
 */
void translate(Tree *node, double x, double y, double z);

/**
 * @brief Apply an homothety the given node alongside each axis by the given ratio.
 *
 * @param node The node being dilated.
 * @param x Ratio the object will be dilated alongside the X.
 * @param y Ratio the object will be dilated alongside the Y.
 * @param z Ratio the object will be dilated alongside the Z.
 */
void homothate(Tree *node, double x, double y, double z);

/**
 * @brief Print the given matrix.
 *
 * @param m Matrix (4x4) to be printed.
 */
void printMatrix(double *m);

/**
 * @brief Print the given point/vector.
 *
 * @param c Point/vector be printed.
 */
void printCoord(G3Xcoord c);

#endif

