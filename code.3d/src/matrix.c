/** @file matrix.c
 *
 *  @brief Contains the definition of the **Matrix**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#include <errno.h>
#include "../include/matrix.h"


/**
 * @brief Return the matrix corresponding to a basic translation of the given factor.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param z Factor on the Z axis
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *translationMatrix(double x, double y, double z) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - translationMatrix ");
        exit(1);
    }
    
    matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.;
    matrix[3] = x;
    matrix[7] = y;
    matrix[11] = z;
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to the inverse of a basic translation of the given factor.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param z Factor on the Z axis
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *translationInvMatrix(double x, double y, double z) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - translationInvMatrix ");
        exit(1);
    }
    
    matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.;
    matrix[3] = -x;
    matrix[7] = -y;
    matrix[11] = -z;
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to a basic homothety of the given factor.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param z Factor on the Z axis
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *homothetyVertexMatrix(double x, double y, double z) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - homothetyMatrixPoint ");
        exit(1);
    }
    
    matrix[15] = 1.;
    matrix[0] = x;
    matrix[5] = y;
    matrix[10] = z;
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to the inverse of a basic homothety of the given factor on a vertex.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param z Factor on the Z axis
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *homothetyVertexInvMatrix(double x, double y, double z) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - homothetyVertexInvMatrix ");
        exit(1);
    }
    
    matrix[15] = 1.;
    matrix[0] = x ? 1 / x : 0;
    matrix[5] = y ? 1 / y : 0;
    matrix[10] = z ? 1 / z : 0;
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to a basic homothety of the given factor on a normal.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param z Factor on the Z axis
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *homothetyNormalMatrix(double x, double y, double z) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - homothetyNormalMatrix ");
        exit(1);
    }
    
    matrix[15] = 1.;
    matrix[0] = y * z;
    matrix[5] = x * z;
    matrix[10] = x * y;
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to a basic rotation on the X axis by an angle t.
 *
 * @param angle The angle in degree.
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *xRotationMatrix(double angle) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - xRotationMatrix ");
        exit(1);
    }
    
    matrix[0] = matrix[15] = 1.;
    matrix[5] = cos(angle * DegToRad);
    matrix[6] = -sin(angle * DegToRad);
    matrix[9] = sin(angle * DegToRad);
    matrix[10] = cos(angle * DegToRad);
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to the inverse of a basic rotation on the X axis by an angle t.
 *
 * @param angle The angle in degree.
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *xRotationInvMatrix(double angle) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - xRotationInvMatrix ");
        exit(1);
    }
    
    matrix[0] = matrix[15] = 1.;
    matrix[5] = cos(-angle * DegToRad);
    matrix[6] = -sin(-angle * DegToRad);
    matrix[9] = sin(-angle * DegToRad);
    matrix[10] = cos(-angle * DegToRad);
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to a basic rotation on the Y axis by an angle t.
 *
 * @param angle The angle in degree.
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *yRotationMatrix(double angle) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - yRotationMatrix ");
        exit(1);
    }
    
    matrix[5] = matrix[15] = 1.;
    matrix[0] = cos(angle * DegToRad);
    matrix[2] = sin(angle * DegToRad);
    matrix[8] = -sin(angle * DegToRad);
    matrix[10] = cos(angle * DegToRad);
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to the inverse of a basic rotation on the Y axis by an angle t.
 *
 * @param angle The angle in degree.
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *yRotationInvMatrix(double angle) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - yRotationInvMatrix ");
        exit(1);
    }
    
    matrix[5] = matrix[15] = 1.;
    matrix[0] = cos(-angle * DegToRad);
    matrix[2] = sin(-angle * DegToRad);
    matrix[8] = -sin(-angle * DegToRad);
    matrix[10] = cos(-angle * DegToRad);
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to a basic rotation on the Z axis by an angle t.
 *
 * @param angle The angle in degree.
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *zRotationMatrix(double angle) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - zRotationMatrix ");
        exit(1);
    }
    
    matrix[10] = matrix[15] = 1.;
    matrix[0] = cos(angle * DegToRad);
    matrix[1] = -sin(angle * DegToRad);
    matrix[4] = sin(angle * DegToRad);
    matrix[5] = cos(angle * DegToRad);
    
    return matrix;
}


/**
 * @brief Return the matrix corresponding to the inverse of a basic rotation on the Z axis by an angle t.
 *
 * @param angle The angle in degree.
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *zRotationInvMatrix(double angle) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - zRotationInvMatrix ");
        exit(1);
    }
    
    matrix[10] = matrix[15] = 1.;
    matrix[0] = cos(-angle * DegToRad);
    matrix[1] = -sin(-angle * DegToRad);
    matrix[4] = sin(-angle * DegToRad);
    matrix[5] = cos(-angle * DegToRad);
    
    return matrix;
}


/**
 * @brief Recursively propagate a transformation matrix to the node's sons.
 *
 * @param node Node of the tree.
 * @param vertex Transformation matrix of the vertices.
 * @param normal Transformation matrix of the normals.
 * @param inverse Inverse transformation matrix of the vertices.
 * @param translation True if the transformation is a translation, false otherwise.
 *
 * @return Whether the inverse matrix can be freed ore not. Vertex and normal matrix should always be freed.
 */
static bool propagate(Tree *node, double *vertex, double *normal, double *inverse, bool translation) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - propagate ");
        exit(1);
    }
    
    int i;
    bool ret;
    double *p, *old;
    
    if (node->left && node->right) {
        ret = propagate(node->left, vertex, normal, inverse, translation);
        ret &= propagate(node->right, vertex, normal, inverse, translation);
    }
    else if (!node->left && !node->right) {
        if (node->mi == NULL) {
            node->mi = inverse;
            ret = false;
        } else {
            old = node->mi;
            node->mi = matrixMatrixMult(inverse, node->mi);
            free(old);
            ret = true;
        }
    }
    else {
        fprintf(stderr, " propagate : Invalid node - has only one son\n");
        exit(1);
    }
    
    printf("%d\n", node->obj->size);
    for (i = 0; i < node->obj->size; i++) {
        p = matrixCoordMult(vertex, node->obj->vertex[i]);
        node->obj->vertex[i][0] = p[0];
        node->obj->vertex[i][1] = p[1];
        node->obj->vertex[i][2] = p[2];
        free(p);
        if (!translation) {
            p = matrixCoordMult(normal, node->obj->normal[i]);
            node->obj->normal[i][0] = p[0];
            node->obj->normal[i][1] = p[1];
            node->obj->normal[i][2] = p[2];
            free(p);
        }
    }
    
    return ret;
}


void printMatrix(double *m) {
    int i, j;
    
    for (i = 0; i < 16; i += 4) {
        for (j = 0; j < 4; j++) {
            printf("%.3f ", m[i + j]);
        }
        printf("\n");
    }
}


void printCoord(G3Xcoord coord) {
    printf("%.3f %.3f %.3f\n", coord[0], coord[1], coord[2]);
}


double *matrixMatrixMult(double *m, double *factor) {
    double *res = (double *) calloc(16, sizeof(double));
    int i, j, k;
    double sum;
    
    if (res == NULL) {
        errno = ENOMEM;
        perror("Error - matrixMatrixMult ");
        exit(1);
    }
    
    for (i = 0; i < 16; i += 4) {
        for (j = 0; j < 4; j++) {
            sum = 0;
            for (k = 0; k < 4; k++) {
                sum += factor[i + k] * m[j + k * 4];
            }
            res[i + j] = sum;
        }
    }
    
    return res;
}


double *matrixCoordMult(double *factor, G3Xpoint p) {
    if (p == NULL || factor == NULL) {
        errno = EFAULT;
        perror("Error - matrixCoordMult ");
        exit(1);
    }
    
    double *res = malloc(sizeof(double) * 3);
    if (!res) {
        errno = ENOMEM;
        perror("Error - matrixCoordMult ");
        exit(1);
    }
    
    double sum;
    int i, j;
    
    for (i = 0; i < 3; i++) {
        sum = 0;
        for (j = 0; j < 3; j++) {
            sum += factor[i * 4 + j] * p[j];
        }
        res[i] = sum + factor[i * 4 + 3];
    }
    
    return res;
}


void rotate(Tree *node, double x, double y, double z) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - rotate ");
        exit(1);
    }
    
    double *mat, *inv;
    if (x) {
        mat = xRotationMatrix(x);
        inv = xRotationInvMatrix(x);
        if (propagate(node, mat, mat, inv, true)) {
            free(inv);
        }
        free(mat);
    }
    if (y) {
        mat = yRotationMatrix(y);
        inv = yRotationInvMatrix(y);
        if (propagate(node, mat, mat, inv, true)) {
            free(inv);
        }
        free(mat);
    }
    if (z) {
        mat = zRotationMatrix(z);
        inv = zRotationInvMatrix(z);
        if (propagate(node, mat, mat, inv, true)) {
            free(inv);
        }
        free(mat);
    }
}


void translate(Tree *node, double x, double y, double z) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - translate ");
        exit(1);
    }
    
    double *mat = translationMatrix(x, y, z);
    double *inv = translationInvMatrix(x, y, z);
    
    if (propagate(node, mat, NULL, inv, true)) {
        free(inv);
    }
    free(mat);
}


void homothate(Tree *node, double x, double y, double z) {
    if (node == NULL) {
        errno = EFAULT;
        perror("Error - homothate ");
        exit(1);
    }
    
    double *vertex, *normal, *inverse;
    vertex = homothetyVertexMatrix(x, y, z);
    normal = homothetyNormalMatrix(x, y, z);
    inverse = homothetyVertexInvMatrix(x, y, z);
    
    if (propagate(node, vertex, normal, inverse, false)) {
        free(inverse);
    }
    free(vertex);
    free(normal);
}
