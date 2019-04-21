/** @file object.h
 *
 *  @brief Header for **Object** definition and functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#ifndef CSG_OBJECT_H
#define CSG_OBJECT_H

#include <g3x.h>
#include <g3x_basix.h>


/**
 * @brief  Canonical shapes.
 */
typedef enum {
    SHP_SPHERE, SHP_CUBE, SHP_CYLINDER, SHP_CONE, SHP_TORUS, SHP_COMPOSITE
} Shape;


/**
 * @brief  Represents a 3D canonic Object.
 */
typedef struct _obj {
    Shape shape;             /**< Shape of the Object. */
    G3Xpoint *vertex;        /**< Vertexes of the Object. */
    G3Xvector *normal;       /**< Normals of the Object. */
    G3Xcolor *color;         /**< Color of the Object. */
    bool (*pt_in)(G3Xpoint); /**< Function checking if a vertex is inside. */
    int size;                /**< Number of vertices/normals in this object. */
    int n, p;                /**< Custom parameters. */
} Object;


/**
 * @brief  Merge two Object into a composite object.
 *
 * @param a First Object.
 * @param b Second Object.
 *
 * @return The new composite Object.
 */
Object *merge(Object *a, Object *b);

#endif
