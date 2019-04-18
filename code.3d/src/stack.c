#include <errno.h>
#include "../include/stack.h"


static char *cellString(Stack *stack) {
    if (stack == NULL) {
        errno = EFAULT;
        perror("Error - cellString ");
        exit(1);
    }
    
    Tree *node = stack->node;
    
    switch (node->op) {
        case UNION:
            return "∪";
        case INTERSECTION:
            return "∩";
        case SUBTRACTION:
            return "-";
        case EQUAL:
            return "=";
        case NONE:
            break;
    }
    if (node->obj != NULL) {
        switch (node->obj->shape) {
            case SHP_CUBE:
                return "CUBE";
            case SHP_CONE:
                return "CONE";
            case SHP_CYLINDER:
                return "CYLINDER";
            case SHP_SPHERE:
                return "SPHERE";
            case SHP_TORUS:
                return "TORUS";
            case SHP_COMPOSITE:
                fprintf(stderr, "Error: cellString - composite without operator");
                exit(1);
        }
    }
    
    fprintf(stderr, "Error: cellString - Invalid stack");
    exit(1);
}


Stack *newStack(Tree *node) {
    if (node == NULL) {
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
    new->node = node;
    
    return new;
}


Tree *popStack(Stack **stack) {
    if (stack == NULL || *stack == NULL) {
        errno = EFAULT;
        perror("Error - popStack ");
        exit(1);
    }
    
    Tree *node = (*stack)->node;
    *stack = (*stack)->next;
    return node;
}


Stack *addStack(Stack *stack, Tree *node) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - addStack ");
        exit(1);
    }
    
    if (stack == NULL) {
        return newStack(node);
    }
    
    Stack *new = (Stack *) malloc(sizeof(Stack));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - addStack ");
        exit(1);
    }
    
    new->node = node;
    new->next = stack;
    return new;
}


void printStack(Stack *stack) {
    Stack *current;
    
    for (current = stack; current != NULL; current = current->next) {
        printf("%s -> ", cellString(current));
    }
    
    printf("[]\n");
}
