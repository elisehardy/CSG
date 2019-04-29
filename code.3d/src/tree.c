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


/**
 * Returns whether a point should be visible.
 *
 * @param tree Tree the point will be checked against.
 * @param p Point tested against the tree.
 * @param index Index of the point if it is known to be part of the Tree, -1 otherwise.
 *
 * @return True if the point should be visible, false otherwise.
 */
static bool isVisible(Tree *tree, G3Xpoint p, int index) {
    if ((tree->left == NULL) + (tree->right == NULL) == 1) {
        fprintf(stderr, "Error: isVisible - Invalid node, have only one son.\n");
        exit(1);
    }
    
    // This node is a leaf
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->mi == NULL) {
            return tree->obj->pt_in(p);
        }
        
        double *reversed = matrixCoordMult(tree->mi, p);
        bool b = tree->obj->pt_in(reversed);
        free(reversed);
        return b;
    }
    
    // p is a point of a primitive from this tree
    if (index >= 0) {
        bool left = index < tree->left->obj->size;
        switch (tree->op) {
            case OP_SUBTRACTION:
                if (left) {
                    return !isVisible(tree->right, p, -1);
                }
                else {
                    return isVisible(tree->left, p, -1);
                }
            case OP_UNION:
                if (left) {
                    return !isVisible(tree->right, p, -1);
                }
                else {
                    return !isVisible(tree->left, p, -1);
                }
            case OP_INTERSECTION:
                if (left) {
                    return isVisible(tree->right, p, -1);
                }
                else {
                    return isVisible(tree->left, p, -1);
                }
            default:
                return true;
        }
    }
    
    // p is a point from another tree
    switch (tree->op) {
        case OP_SUBTRACTION:
            return isVisible(tree->left, p, -1) && !isVisible(tree->right, p, -1);
        case OP_UNION:
            return isVisible(tree->left, p, -1) || isVisible(tree->right, p, -1);
        case OP_INTERSECTION:
            return isVisible(tree->left, p, -1) && isVisible(tree->right, p, -1);
        default:
            return isVisible(tree->left, p, -1) || isVisible(tree->right, p, -1);
    }
}


/**
 * @brief Recursively map pointer of sons to the right part of their parent's vertices, normal and color array.
 *
 * @param node Node containing pointer to be mapped.
 */
static void mapPointer(Tree *node) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - nodeString ");
        exit(1);
    }
    
    if ((node->left == NULL) + (node->right == NULL) == 1) {
        fprintf(stderr, "Error: mapPointer - Invalid node, have only one son.\n");
        exit(1);
    }
    
    if (node->left == NULL) {
        return;
    }
    
    node->left->obj->drawData = node->obj->drawData;
    node->right->obj->drawData = node->obj->drawData + node->left->obj->size;
    
    mapPointer(node->left);
    mapPointer(node->right);
}

static int colorCmp(const void *a, const void *b) {
    return memcmp(((DrawData*) a)->color, ((DrawData*) b)->color, sizeof(G3Xcolor));
}

static void sortArray(Tree *node) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - nodeString ");
        exit(1);
    }
    
    int start = 0, end = node->obj->size - 1;
    DrawData tmp;
    
    while (start < end) {
        if (!node->visible[start]) {
            while (!node->visible[end] && start < end) {
                end--;
            }
            
            tmp = node->obj->drawData[start];
            node->obj->drawData[start] = node->obj->drawData[end];
            node->obj->drawData[end] = tmp;
            
            node->visible[start] = 1;
            node->visible[end] = 0;
        }
        start++;
    }
    
    qsort(node->obj->drawData, --start, sizeof(DrawData), colorCmp);
}


/**
 * @brief Return a string corresponding to a node.
 *
 * @param node Node to be interpreted as a string.
 *
 * @return A string corresponding to the given node.
 */
static char *nodeString(Tree *node) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - nodeString ");
        exit(1);
    }
    
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
                fprintf(stderr, "Error: nodeString - composite without operator\n");
                exit(1);
        }
    }
    
    fprintf(stderr, "Error: nodeString - Invalid node\n");
    exit(1);
}


/**
 * @brief Free the memory allocated for a Tree.
 *
 * Ensure Object is only freed at root.
 *
 * @param node Tree to be freed.
 */
static void _freeTree(Tree *node, bool freeObj) {
    if (node == NULL) {
        return;
    }
    
    _freeTree(node->left, false);
    _freeTree(node->right, false);
    
    free(node->visible);
    
    if (freeObj) {
        freeObject(node->obj);
    }
    else {
        free(node->obj);
    }
    if (node->mi != NULL) {
        free(node->mi);
    }
    
    free(node);
}


/**
 * Print the tree recursively.
 *
 * @param node Tree to be printed.
 * @param space Number of space between son and father.
 */
static void _printTree(Tree *node, int space) {
    if (node == NULL) {
        return;
    }
    
    _printTree(node->right, space + 8);
    printf("\n");
    for (int i = 0; i < space; i++) {
        printf(" ");
    }
    printf("%s\n", nodeString(node));
    _printTree(node->left, space + 8);
}


void printTree(Tree *root) {
    if (root == NULL) {
        errno = EFAULT;
        perror("Error - printTree ");
        exit(1);
    }
    
    _printTree(root, 0);
}


Tree *newLeaf(Object *obj) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - newLeaf ");
        exit(1);
    }
    
    Tree *new = malloc(sizeof(Tree));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - newLeaf ");
        exit(1);
    }
    
    new->op = OP_NONE;
    new->obj = obj;
    new->mi = NULL;
    new->neg = false;
    new->left = NULL;
    new->right = NULL;
    new->visible = malloc(sizeof(bool) * obj->size);
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - newLeaf ");
        exit(1);
    }
    
    memset(new->visible, 1, sizeof(bool) * obj->size);
    
    return new;
}


Tree *newNode(Tree *left, Tree *right, Operator op) {
    if (left == NULL || right == NULL) {
        errno = EFAULT;
        perror("Error - newNode ");
        exit(1);
    }
    
    Tree *new = malloc(sizeof(Tree));
    if (new == NULL) {
        errno = ENOMEM;
        perror("Error - newNode ");
        exit(1);
    }
    
    new->op = op;
    new->mi = NULL;
    new->neg = false;
    new->left = left;
    new->right = right;
    
    new->obj = mergeObject(left->obj, right->obj);
    if (op == OP_SUBTRACTION) {
        for (int i = left->obj->size; i < new->obj->size; i++) {
            new->obj->drawData[i].normal[0] *= -1;
            new->obj->drawData[i].normal[1] *= -1;
            new->obj->drawData[i].normal[2] *= -1;
        }
    }
    
    new->visible = malloc(sizeof(bool) * new->obj->size);
    if (!new->visible) {
        errno = ENOMEM;
        perror("Error - newNode ");
        exit(1);
    }
    
    memcpy(new->visible, left->visible, left->obj->size * sizeof(bool));
    memcpy(new->visible + left->obj->size, right->visible, right->obj->size * sizeof(bool));
    for (int i = 0; i < new->obj->size; i++) {
        if (new->visible[i]) {
            new->visible[i] = isVisible(new, new->obj->drawData[i].vertex, i);
        }
    }
    
    sortArray(new);
    mapPointer(new);
    
    return new;
}


void drawNode(Tree *node, int c) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - drawObject ");
        exit(1);
    }
    
    G3Xcolor previous = {0};
    int i;
    
    memcpy(previous, G3Xr, sizeof(G3Xcolor));
    
    glPointSize(1);
    glBegin(GL_POINTS);
    g3x_Material(previous, 0.25, 0.5, 0.5, 0.5, 1.);
    
    if (!node->neg) {
        for (i = 0; i < node->obj->size && node->visible[i]; i += c) {
            if (memcmp(previous, node->obj->drawData[i].color, sizeof(G3Xcolor))) {
                memcpy(previous, node->obj->drawData[i].color, sizeof(G3Xcolor));
                g3x_Material(previous, 0.25, 0.5, 0.5, 0.5, 1.);
            }
            
            glNormal3dv(node->obj->drawData[i].normal);
            glVertex3dv(node->obj->drawData[i].vertex);
        }
    }
    
    glEnd();
}


void freeTree(Tree *node) {
    _freeTree(node, true);
}
