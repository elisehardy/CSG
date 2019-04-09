#ifndef CSG_TREE_H
#define CSG_TREE_H

#include "object.h"


typedef enum {
    UNION, INTERSECTION, SOUSTRACTION
} Operator;


/**
 * CSG Tree used to represents composite Objects.
 */
typedef struct _node {
    Operation op;               /**< Operator used by this node.*/
    Object *obj;                /**< Object used by this node. */
    bool neg;                   /**< ? */
    bool *visible;              /**< Boolean array telling whether a point I should be drawn */
    double *md;                 /**< ? */
    double *mi;                 /**< ? */
    double *mn;                 /**< ? */
    struct _node *right, *left; /**< Sons of this node */
} Tree;


/**
 * Create a new node.
 *
 * Field are initialized like this :
 * - neg is initialized to false.
 * - visible is allocated with obj->size cell and filled with 1.
 * - Every matrice are set to NULL.
 * - Both sons are set to NULL.
 *
 * @param op Operator of this node.
 * @param obj Object of this node.
 *
 * @return The newly created node.
 */
Tree *newNode(Operator op, Object *obj);

#endif
