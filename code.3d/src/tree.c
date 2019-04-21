/** @file tree.c
 *
 *  @brief Contains the definition of the **Tree**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */


#include <errno.h>

#include "../include/tree.h"
#include "../include/matrix.h"


static bool insideNode(Tree *tree, G3Xpoint p, int index) {
    if ((tree->left == NULL) + (tree->right == NULL) == 1) {
        fprintf(stderr, "Error: insideNode - Invalid node.\n");
        exit(1);
    }
    
    // This node is a leaf
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->mi == NULL) {
            return tree->obj->pt_in(p);
        }
        
        return tree->obj->pt_in(matrixCoordMult(tree->mi, p));
    }
    
    // p is a point of a primitive from this tree
    if (index >= 0) {
        bool left = index < tree->left->obj->size;
        switch (tree->op) {
            case SUBTRACTION:
                if (left) {
                    return !insideNode(tree->right, p, -1);
                }
                else {
                    return insideNode(tree->left, p, -1);
                }
            case UNION:
                if (left) {
                    return !insideNode(tree->right, p, -1);
                }
                else {
                    return !insideNode(tree->left, p, -1);
                }
            case INTERSECTION:
                if (left) {
                    return insideNode(tree->right, p, -1);
                }
                else {
                    return insideNode(tree->left, p, -1);
                }
            default:
                return true;
        }
    }
    
    // p is a point from another tree
    switch (tree->op) {
        case SUBTRACTION:
            return insideNode(tree->left, p, -1) && !insideNode(tree->right, p, -1);
        case UNION:
            return insideNode(tree->left, p, -1) || insideNode(tree->right, p, -1);
        case INTERSECTION:
            return insideNode(tree->left, p, -1) && insideNode(tree->right, p, -1);
        default:
            return insideNode(tree->left, p, -1) || insideNode(tree->right, p, -1);
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
                fprintf(stderr, "Error: printTreeData - composite without operator\n");
                exit(1);
        }
    }
    
    fprintf(stderr, "Error: printTreeData - Invalid node\n");
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
    if (op == SUBTRACTION) {
        for (int i = left->obj->size; i < new->obj->size; i++) {
            new->obj->normal[i][0] *= -1;
            new->obj->normal[i][1] *= -1;
            new->obj->normal[i][2] *= -1;
        }
    }
    
    new->visible = malloc(sizeof(bool) * new->obj->size);
    memcpy(new->visible, left->visible, left->obj->size * sizeof(bool));
    memcpy(new->visible + left->obj->size, right->visible, right->obj->size * sizeof(bool));
    for (int i = 0; i < new->obj->size; i++) {
        if (new->visible[i]) {
            new->visible[i] = insideNode(new, new->obj->vertex[i], i);
        }
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
    G3Xcolor previous;
    
    memcpy(previous, G3Xr, sizeof(G3Xcolor));
    
    glPointSize(1);
    glBegin(GL_POINTS);
    g3x_Material(previous, 0.25, 0.5, 0.5, 0.5, 1.);
    
    if (!node->neg) {
        for (i = 0; i < size; i += c) {
            if (memcmp(previous, node->obj->color[i], sizeof(G3Xcolor))) {
                memcpy(previous, node->obj->color[i], sizeof(G3Xcolor));
                g3x_Material(previous, 0.25, 0.5, 0.5, 0.5, 1.);
            }
            
            if (node->visible[i]) {
                glNormal3dv(n[i]);
                glVertex3dv(v[i]);
            }
        }
    }
    
    glEnd();
}
