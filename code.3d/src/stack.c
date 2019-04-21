/** @file stack.c
 *
 *  @brief Contains the definition of the **Stack**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#include <errno.h>
#include "../include/stack.h"


/**
 * @brief Return a string corresponding to a Stack's cell.
 *
 *
 * @param cell Cell to be interpreted as a string.
 *
 * @return A string corresponding to the given cell.
 */
static char *cellString(Stack *cell) {
    if (cell == NULL) {
        errno = EFAULT;
        perror("Error - cellString ");
        exit(1);
    }
    
    Tree *node = cell->node;
    
    switch (node->op) {
        case OP_UNION:
            return "∪";
        case OP_INTERSECTION:
            return "∩";
        case OP_SUBTRACTION:
            return "-";
        case OP_EQUAL:
            return "=";
        case OP_NONE:
            fprintf(stderr, "Error: cellString - Invalid stack (Node with OP_NONE operator).\n");
            exit(1);;
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
                fprintf(stderr, "Error: cellString - composite without operator.\n");
                exit(1);
        }
    }
    
    fprintf(stderr, "Error: cellString - Invalid stack.\n");
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
    
    Stack *toFree = *stack;
    
    Tree *node = (*stack)->node;
    *stack = (*stack)->next;
    
    free(toFree);
    
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


int sizeStack(Stack *stack) {
    if (stack == NULL) {
        return 0;
    }
    
    Stack *current;
    int size = 0;
    
    for (current = stack; current != NULL; current = current->next) {
        size++;
    }
    
    return size;
}


void printStack(Stack *stack) {
    Stack *current;
    
    for (current = stack; current != NULL; current = current->next) {
        printf("%s -> ", cellString(current));
    }
    
    printf("[]\n");
}
