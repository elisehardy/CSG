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
    
    if (!matrix) {
        perror("Could not allocate matrix.");
        exit(1);
    }
    
    matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.;
    matrix[3] = x;
    matrix[7] = y;
    matrix[11] = z;
    
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
static double *homothetyMatrix(double x, double y, double z) {
    double *matrix = (double *) calloc(16, sizeof(double));
    if (!matrix) {
        perror("Could not allocate matrix.");
        exit(1);
    }
    
    matrix[15] = 1.;
    matrix[0] = x;
    matrix[5] = y;
    matrix[10] = z;
    
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
    if (!matrix) {
        perror("Could not allocate matrix.");
        exit(1);
    }
    
    matrix[0] = matrix[15] = 1.;
    matrix[5] = cos(angle);
    matrix[6] = -sin(angle);
    matrix[10] = sin(angle);
    matrix[11] = cos(angle);
    
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
    if (!matrix) {
        perror("Could not allocate matrix.");
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
 * Return the matrix corresponding to a basic rotation on the Z axis by an angle t.
 *
 * @param t The angle in radian.
 *
 * @return The computed 4x4 matrix as an array of 16 points.
 */
static double *zRotationMatrix(double angle) {
    double *matrix = (double *) calloc(16, sizeof(double));
    if (!matrix) {
        perror("Could not allocate matrix.");
        exit(1);
    }
    
    matrix[10] = matrix[15] = 1.;
    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[4] = sin(angle);
    matrix[5] = cos(angle);
    
    return matrix;
}


void matrixMatrixMult(double *m, double *factor) {
    double *res;
    int i, j, k;
    double sum;
    
    res = (double *) calloc(16, sizeof(double));
    if (!res) {
        perror("Could not allocate matrix.");
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


void matrixPointMult(double *factor, G3Xpoint *p) {
    G3Xpoint res;
    int i, j, k;
    double sum;
    
    for (i = 0; i < 4; i++) {
        sum = 0;
        for (j = 0; j < 3; j++) {
            sum += factor[i * 4 + j] * *p[j];
        }
        res[i] = sum + factor[i * 4 + 3];
    }
    
    memcpy(*p, res, sizeof(G3Xpoint));
}


void matrixVectorMult(double *factor, G3Xvector *v) {
    G3Xvector res;
    int i, j, k;
    double sum;
    
    for (i = 0; i < 4; i++) {
        sum = 0;
        for (j = 0; j < 3; j++) {
            sum += factor[i * 4 + j] * *v[j];
        }
        res[i] = sum;
    }
    
    memcpy(*v, res, sizeof(G3Xvector));
}


void rotate(Object *obj, double x, double y, double z) {
    double *xMat = xRotationMatrix(x);
    double *yMat = yRotationMatrix(y);
    double *zMat = zRotationMatrix(z);
    int i;
    
    for (i = 0; i < obj->size; i++) {
        if (x) {
            matrixPointMult(xMat, &obj->vertex[i]);
            matrixVectorMult(xMat, &obj->normal[i]);
        }
        if (y) {
            matrixPointMult(yMat, &obj->vertex[i]);
            matrixVectorMult(yMat, &obj->normal[i]);
        }
        if (z) {
            matrixPointMult(zMat, &obj->vertex[i]);
            matrixVectorMult(yMat, &obj->normal[i]);
        }
    }
}


void translate(Object *obj, double x, double y, double z) {
    double *mat = translationMatrix(x, y, z);
    int i;
    
    for (i = 0; i < obj->size; i++) {
        matrixPointMult(mat, &obj->vertex[i]);
        matrixVectorMult(mat, &obj->normal[i]);
    }
}

