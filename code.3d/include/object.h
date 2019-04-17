#ifndef CSG_OBJECT_H
#define CSG_OBJECT_H

#include <g3x.h>
#include <g3x_basix.h>


/**
 * Canonical shapes.
 */
typedef enum {
    SHP_SPHERE, SHP_CUBE, SHP_CYLINDER, SHP_CONE, SHP_TORUS, SHP_COMPOSITE
} Shape;


/**
 * Represents a 3D canonic Object.
 */
typedef struct _obj {
    Shape shape;                            /**< Shape of the Object. */
    G3Xpoint *vertex;                       /**< Vertexes of the Object. */
    G3Xvector *normal;                      /**< Normals of the Object. */
    bool *visible;                          /**< Boolean array telling whether a point I should be drawn */
    bool (*pt_in)(G3Xpoint);               /**< Function checking if a vertex is inside. */
    bool (*build)(struct _obj *);           /**< ?. */
    int n, p, size;                         /**< Custom parameters. */
} Object;


/**
 * Merge two Object into a composite object.
 *
 * @param a First Object.
 * @param b Second Object.
 *
 * @return The new composite Object.
 */
Object *merge(Object *a, Object *b);

/**
 * Draw an object.
 *
 * @param obj Object to be drawn.
 * @param c ?
 */
void drawObject(Object *obj, int c);

#endif
