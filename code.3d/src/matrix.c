#include "../include/matrix.h"


/**
 * Return the matrix corresponding to a basic translation of the given factor.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param x Factor on the Z axis
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
 * Return the matrix corresponding to the inverse of a basic translation of the given factor.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param x Factor on the Z axis
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
 * Return the matrix corresponding to a basic homothety of the given factor.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param x Factor on the Z axis
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
 * Return the matrix corresponding to the inverse of a basic homothety of the given factor on a vertex.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param x Factor on the Z axis
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
 * Return the matrix corresponding to a basic homothety of the given factor on a normal.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param x Factor on the Z axis
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
 * Return the matrix corresponding to the inverse of a basic homothety of the given factor on a normal.
 *
 * @param x Factor on the X axis
 * @param y Factor on the Y axis
 * @param x Factor on the Z axis
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *homothetyNormalInvMatrix(double x, double y, double z) {
    double *matrix = (double *) calloc(16, sizeof(double));
    
    if (matrix == NULL) {
        errno = ENOMEM;
        perror("Error - homothetyNormalInvMatrix ");
        exit(1);
    }
    
    matrix[15] = 1.;
    matrix[0] = y && z ? 1 / (y * z) : 0;
    matrix[5] = x && z ? 1 / (x * z) : 0;
    matrix[10] = x && y ? 1 / (x * y) : 0;
    
    return matrix;
}


/**
 * Return the matrix corresponding to a basic rotation on the X axis by an angle t.
 *
 * @param t The angle in radian.
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
    matrix[5] = cos(angle);
    matrix[6] = -sin(angle);
    matrix[9] = sin(angle);
    matrix[10] = cos(angle);
    
    return matrix;
}


/**
 * Return the matrix corresponding to the inverse of a basic rotation on the X axis by an angle t.
 *
 * @param t The angle in radian.
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
    matrix[5] = cos(-angle);
    matrix[6] = -sin(-angle);
    matrix[9] = sin(-angle);
    matrix[10] = cos(-angle);
    
    return matrix;
}


/**
 * Return the matrix corresponding to a basic rotation on the Y axis by an angle t.
 *
 * @param t The angle in radian.
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
    matrix[0] = cos(angle);
    matrix[2] = sin(angle);
    matrix[8] = -sin(angle);
    matrix[10] = cos(angle);
    
    return matrix;
}


/**
 * Return the matrix corresponding to the inverse of a basic rotation on the Y axis by an angle t.
 *
 * @param t The angle in radian.
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
    matrix[0] = cos(-angle);
    matrix[2] = sin(-angle);
    matrix[8] = -sin(-angle);
    matrix[10] = cos(-angle);
    
    return matrix;
}


/**
 * Return the matrix corresponding to a basic rotation on the Z axis by an angle t.
 *
 * @param t The angle in radian.
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
    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[4] = sin(angle);
    matrix[5] = cos(angle);
    
    return matrix;
}


/**
 * Return the matrix corresponding to the inverse of a basic rotation on the Z axis by an angle t.
 *
 * @param t The angle in radian.
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
    matrix[0] = cos(-angle);
    matrix[1] = -sin(-angle);
    matrix[4] = sin(-angle);
    matrix[5] = cos(-angle);
    
    return matrix;
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


void matrixMatrixMult(double *m, double *factor) {
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
    
    *m = *res;
}


void matrixCoordMult(double *factor, G3Xcoord p) {
    if (!p) {
        errno = EFAULT;
        perror("Error - matrixCoordMult ");
        exit(1);
    }
    
    G3Xcoord res;
    double sum;
    int i, j;
    
    for (i = 0; i < 3; i++) {
        sum = 0;
        for (j = 0; j < 3; j++) {
            sum += factor[i * 4 + j] * p[j];
        }
        res[i] = sum + factor[i * 4 + 3];
    }
    
    memcpy(p, res, sizeof(G3Xcoord));
}


void rotate(Object *obj, double x, double y, double z) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - rotate ");
        exit(1);
    }
    
    double *xMat = xRotationMatrix(x);
    double *yMat = yRotationMatrix(y);
    double *zMat = zRotationMatrix(z);
    int i;
    
    for (i = 0; i < obj->size; i++) {
        if (x) {
            matrixCoordMult(xMat, obj->vertex[i]);
            matrixCoordMult(xMat, obj->normal[i]);
        }
        if (y) {
            matrixCoordMult(yMat, obj->vertex[i]);
            matrixCoordMult(yMat, obj->normal[i]);
        }
        if (z) {
            matrixCoordMult(zMat, obj->vertex[i]);
            matrixCoordMult(yMat, obj->normal[i]);
        }
    }
}


void translate(Object *obj, double x, double y, double z) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - translate ");
        exit(1);
    }
    
    double *mat = translationMatrix(x, y, z);
    int i;
    
    for (i = 0; i < obj->size; i++) {
        matrixCoordMult(mat, obj->vertex[i]);
    }
}


void homothate(Object *obj, double x, double y, double z) {
    if (obj == NULL) {
        errno = EFAULT;
        perror("Error - homothate ");
        exit(1);
    }
    
    double *vmat = homothetyVertexMatrix(x, y, z);
    double *nmat = homothetyNormalMatrix(x, y, z);
    int i;
    
    for (i = 0; i < obj->size; i++) {
        matrixCoordMult(vmat, obj->vertex[i]);
        matrixCoordMult(nmat, obj->normal[i]);
    }
}
