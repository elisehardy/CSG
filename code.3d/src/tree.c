#include <errno.h>

#include "../include/tree.h"
#include "../include/matrix.h"


static bool insideNode(Tree *tree, G3Xpoint p) {
    if ((tree->left == NULL) + (tree->right == NULL) == 1) {
        fprintf(stderr, "Error: insideNode - Invalid node.");
        exit(1);
    }
    
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->mi == NULL) {
            return tree->obj->pt_in(p);
        }
        return tree->obj->pt_in(matrixCoordMult(tree->mi, p));
    }
    
    switch (tree->op) {
        case SUBTRACTION:
            return insideNode(tree->left, p) && !insideNode(tree->right, p);
        case UNION:
            return insideNode(tree->left, p) != insideNode(tree->right, p);
        case INTERSECTION:
            return insideNode(tree->left, p) && insideNode(tree->right, p);
        default:
            return insideNode(tree->left, p) || insideNode(tree->right, p);
    }
}


static char *getTreeData(Tree *node) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - getTreeData ");
        exit(1);
    }
    
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
                fprintf(stderr, "Error: printTreeData - composite without operator");
                exit(1);
        }
    }
    
    fprintf(stderr, "Error: printTreeData - Invalid node");
    exit(1);
}


static void printTreeRec(Tree *node, int space) {
    if (node == NULL) {
        return;
    }
    
    printTreeRec(node->right, space + 8);
    printf("\n");
    for (int i = 0; i < space; i++) {
        printf(" ");
    }
    printf("%s\n", getTreeData(node));
    printTreeRec(node->left, space + 8);
}


void printTree(Tree *root) {
    if (root == NULL) {
        errno = EFAULT;
        perror("Error - printTree ");
        exit(1);
    }
    
    printTreeRec(root, 0);
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
    
    new->op = op;
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


void drawNode(Tree *node, int c) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - drawObject ");
        exit(1);
    }
    
    
    G3Xvector *n = node->obj->normal;
    G3Xpoint *v = node->obj->vertex;
    int i, size = node->obj->size;
    glPointSize(1);
    glBegin(GL_POINTS);
    
    for (i = 0; i < size; i += c) {
        if (node->visible[i]) {
            g3x_Material(node->obj->color[i], 0.25, 0.5, 0.5, 0.5, 1.);
            glNormal3dv(n[i]);
            glVertex3dv(v[i]);
        }
    }
    
    glEnd();
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


void SUBTRACTIONTree(Object *objA, Object *objB) {
    int i;
    int v;
    //make transforme de la SUBTRACTION
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
