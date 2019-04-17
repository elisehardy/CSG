#include "../include/tree.h"

#include "../include/matrix.h"

static bool insideNode(Tree *tree, G3Xpoint p) {
    if (tree->left != NULL && tree->right != NULL) {
        switch (tree->op) {
            case SOUSTRACTION:
                return insideNode(tree->left, p) && !insideNode(tree->right, p);
            case UNION:
                return insideNode(tree->left, p) != insideNode(tree->right, p);
            case INTERSECTION:
                return insideNode(tree->left, p) && insideNode(tree->right, p);
            default:
                return insideNode(tree->left, p) || insideNode(tree->right, p);
        }
    } else if (tree->left != NULL || tree->right != NULL) {
        fprintf(stderr, " insideNode : Invalid node - only one son");
        exit(1);
    }
    
    G3Xpoint *reversed = matrixCoordMult(tree->mi, p);
    
    return tree->obj->pt_in(*reversed);
}



Tree *newLeaf(Object *obj) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - newLeaf ");
        exit(1);
    }
    
    Tree *new = (Tree *) malloc(sizeof(Tree));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - newLeaf ");
        exit(1);
    }
    
    new->op = NONE;
    new->obj = obj;
    new->md = NULL;
    new->mi = NULL;
    new->mn = NULL;
    new->neg = false;
    new->left = NULL;
    new->right = NULL;
    new->visible = malloc(sizeof(bool) * obj->size);
    
    memset(new->visible, 1, sizeof(bool) * obj->size);
    
    return new;
}


Tree *newNode(Tree *left, Tree *right, Operator op) {
    if (left == NULL || right == NULL) {
        errno = EFAULT;
        perror("Error - newNode ");
        exit(1);
    }
    
    Tree *new = (Tree *) malloc(sizeof(Tree));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - newNode ");
        exit(1);
    }
    
    
    
    new->op = op;int
    new->md = NULL;
    new->mi = NULL;
    new->mn = NULL;
    new->neg = false;
    new->left = left;
    new->right = right;
    new->obj = merge(left->obj, right->obj);
    new->visible = malloc(sizeof(bool) * new->obj->size);
    
    int i;
    for (i = 0; i < new->obj->size; i++) {
        new->visible[i] = insideNode(new, new->obj->vertex[i]);
    }
    
    return new;
}

/*
void unionTree(Object *objA, Object *objB) {
    int i;
    int v;
    //make transforme de l'union
    //make inverse pour les deux objet pour A applique inverse de B et pour B applique inverse de A
    for (i = 0; i < objA->size; i++) {
        if (objA->pt_in(objA, objB->vertex)) {
            objA->visible[i] = 0;
        } else {
            objA->visible[i] = 1;
        }
    }
    for (i = 0; i < objB->size; i++) {
        if (objB->pt_in(objB, objA->vertex)) {
            objB->visible[i] = 0;
        } else {
            objB->visible[i] = 1;
        }
    }
}


void intersectionTree(Object *objA, Object *objB) {
    int i;
    int v;
    //make transforme de l'inter
    //make inverse pour les deux objet pour A applique inverse de B et pour B applique inverse de A
    for (i = 0; i < objA->size; i++) {
        if (objA->pt_in(objA, objB->vertex)) {
            objA->visible[i] = 1;
        } else {
            objA->visible[i] = 0;
        }
    }
    for (i = 0; i < objB->size; i++) {
        if (objB->pt_in(objB, objA->vertex)) {
            objB->visible[i] = 1;
        } else {
            objB->visible[i] = 0;
        }
    }
}


void soustractionTree(Object *objA, Object *objB) {
    int i;
    int v;
    //make transforme de la soustraction
    //make inverse pour les deux objet pour A applique inverse de B et pour B applique inverse de A
    for (i = 0; i < objA->size; i++) {
        if (objA->pt_in(objA, objB->vertex)) {
            objA->visible[i] = 0;
        } else {
            objA->visible[i] = 1;
        }
    }
    for (i = 0; i < objB->size; i++) {
        if (objB->pt_in(objB, objA->vertex)) {
            objB->visible[i] = 1;
        } else {
            objB->visible[i] = 0;
        }
    }
}*/
