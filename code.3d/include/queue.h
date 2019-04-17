#ifndef CSG_QUEUE_H
#define CSG_QUEUE_H

#include "object.h"


/**
 * A queue of Object.
 */
typedef struct _cell {
    Object *obj;        /**< An Object. */
    struct _cell *tail; /**< The last element of the Queue. */
    struct _cell *next; /**< The next element of this cell. */
} Queue;


/**
 * Remove the first Object from the queue and return it.
 *Object
 * @param q A non-NULL queue.
 *
 * @return The first Object of the queue.
 */
Object *popQueue(Queue *q);

/**
 * Add a new Object to the queue. If q is NULL, create a new queue.
 *
 * @param q A queue, NULL to create a new queue.
 * @param obj The object to be added to the queue.
 */
void addQueue(Queue *q, Object *obj);

#endif
