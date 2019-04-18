#ifndef CSG_STACK_H
#define CSG_STACK_H

#include "object.h"


/**
 * A queue of Object.
 */
typedef struct _cell {
    Object *obj;        /**< An Object. */
    struct _cell *next; /**< The next element of this cell. */
} Stack;


/**
 * Create a new Stack from the given Object.
 *
 * @param obj First element of the Stack.
 *
 * @return The newly created queue containing obj.
 */
Stack *newStack(Object *obj);

/**
 * Remove the first Object from the stack and return it.
 *
 * @param q A non-NULL stack.
 *
 * @return The first Object of the stack.
 */
Object *popStack(Stack *q);

/**
 * Add a new Object to the stack. If q is NULL, create a new stack.
 *
 * @param q A queue, NULL to create a new stack.
 * @param obj The object to be added to the stack.
 */
void addStack(Stack *q, Object *obj);

#endif
