#include <errno.h>
#include "../include/stack.h"


Stack *newStack(Object *obj) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - newStack ");
        exit(1);
    }
    
    Stack *new = (Stack *) malloc(sizeof(Stack));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - newStack ");
        exit(1);
    }
    
    new->next = NULL;
    new->obj = obj;
    
    return new;
}


Object *popStack(Stack *q) {
    if (q == NULL) {
        errno = EFAULT;
        perror("Error - popStack ");
        exit(1);
    }
    
    Object *obj = q->obj;
    q = q->next;
    return obj;
}


void addStack(Stack *stack, Stack *new) {
    if (new == NULL) {
        errno = EFAULT;
        perror("Error - addStack ");
        exit(1);
    }
    
    Stack *new = (Stack *) malloc(sizeof(Stack));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - addStack ");
        exit(1);
    }
    
    new->next = q;
    q = new;
}
