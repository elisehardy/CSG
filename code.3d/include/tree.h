/** @file tree.h
 *
 *  @brief Header for the **CSG tree** definition and functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#ifndef CSG_TREE_H
#define CSG_TREE_H

#include "object.h"


typedef enum {
    UNION, INTERSECTION, SUBTRACTION, EQUAL, NONE
} Operator;


/**
 * @brief  CSG Tree used to represents composite Objects.
 */
typedef struct _node {
    Operator op;                /**< Operator used by this node.*/
    Object *obj;                /**< Object used by this node. */
    bool *visible;              /**< Boolean array telling whether a point I should be drawn. */
    bool neg;                   /**< ? */
    double *md;                 /**< ? */
    double *mi;                 /**< ? */
    double *mn;                 /**< ? */
    struct _node *left, *right; /**< Sons of this node */
} Tree;


/**
 * @brief  Create a new leaf from the given object.
 *
 * @param obj Object of this node.
 *
 * @return The newly created node.
 */
Tree *newLeaf(Object *obj);

/**
 * @brief  Return a new node linking left and right with op.
 *
 * @param left The left operand of the operation.
 * @param right The right operand of the operation.
 * @param op The operator of the operation.
 *
 * @return The newly created node.
 */
Tree *newNode(Tree *left, Tree *right, Operator op);

/**
 * @brief  Draw a node.
 *
 * @param node Node to be drawn.
 * @param c ?
 */
void drawNode(Tree *node, int c);

/**
 * @brief  Print a Tree.
 *
 * @param root Root of the tree.
 */
void printTree(Tree *root);

#endif
