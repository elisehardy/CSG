/** @file stack.h
 *
 *  @brief Header for the **Stack** definition and functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#ifndef CSG_STACK_H
#define CSG_STACK_H

#include "tree.h"


/**
 * @brief A queue of Object.
 */
typedef struct _cell {
    Tree *node;        /**< An Object. */
    struct _cell *next; /**< The next element of this cell. */
} Stack;


/**
 * @brief Create a new Stack from the given Object.
 *
 * @param node First element of the Stack.
 *
 * @return The newly created queue containing obj.
 */
Stack *newStack(Tree *node);

/**
 * @brief Remove the first Object from the stack and return it.
 *
 * @param stack A non-NULL stack.
 *
 * @return The first Object of the stack.
 */
Tree *popStack(Stack **stack);

/**
 * @brief Add a new node to the stack. If stack is NULL, create a new stack.
 *
 * @param stack A stack, NULL to create a new stack.
 * @param node The node to be added to the stack.
 */
Stack *addStack(Stack *stack, Tree *node);

/**
 * @brief Returns the size of the given stack.
 *
 * @param stack Stack to be analyzed.
 *
 * @return The size of the given stack.
 */
int sizeStack(Stack *stack);

/**
 * @brief Print a stack on stdout.
 *
 * @param stack Stack to be printed
 */
void printStack(Stack *stack);

#endif
