#include <errno.h>
#include "../include/queue.h"


/**
 * Create a new Queue from the given Object.
 *
 * @param obj First element of the Queue.
 *
 * @return The newly created queue containing obj.
 */
static Queue *newQueue(Object *obj) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - newQueue ");
        exit(1);
    }
    
    Queue *new = (Queue *) malloc(sizeof(Queue));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - newQueue ");
        exit(1);
    }
    
    new->obj = obj;
    new->tail = new;
    new->next = NULL;
    
    return new;
}


Object *popQueue(Queue *q) {
    if (q == NULL) {
        errno = EFAULT;
        perror("Error - popQueue ");
        exit(1);
    }
    
    Object *obj = q->obj;
    q->next->tail = q->tail;
    q = q->next;
    return obj;
}


void addQueue(Queue *q, Object *obj) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - addQueue ");
        exit(1);
    }
    
    if (q == NULL) {
        q = newQueue(obj);
        return;
    }
    
    Queue *new = (Queue *) malloc(sizeof(Queue));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - addQueue ");
        exit(1);
    }
    
    new->obj = obj;
    new->tail = new;
    new->next = NULL;
    
    q->tail->next = new;
    q->tail = new;
}
