/** @file file.c
 *
 *  @brief Contains the definition of the **file parsing**'s functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */


#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "../include/file.h"
#include "../include/cube.h"
#include "../include/sphere.h"
#include "../include/cylinder.h"
#include "../include/torus.h"
#include "../include/cone.h"
#include "../include/matrix.h"
#include "../include/stack.h"


/**
 * @brief Trim whitespace on both side of str, returning the new size of str.
 *
 * @param str String to be trimmed.
 *
 * @return The size of the trimmed string.
 */
static int trimAndLower(char *str) {
    int size, i = 0, len = strlen(str) - 1;
    
    if (len == -1) {
        return 0;
    }
    
    while (isspace(str[i]) && i < len) {
        i++;
    }
    while (isspace(str[len]) && len > i) {
        len--;
    }
    
    if (i == len) {
        if (!isspace(str[i])) {
            return 1;
        }
        
        str[0] = '\0';
        return 0;
    }
    
    size = len - i + 1;
    memmove(str, str + i, size);
    str[size] = '\0';
    
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    
    return size;
}


/**
 * @brief Return an Object corresponding to the one following 'obj:'.
 *
 * @param token String following 'obj:'.
 * @param line Current line number in the script.
 *
 * @return Pointer to the corresponding Object.
 */
static Object *parseObj(char *token, char *points, int line) {
    if (token == NULL) {
        errno = EFAULT;
        perror("Error - parseObj ");
        exit(1);
    }
    
    int p = 500;
    if (points != NULL) {
        trimAndLower(points);
        if ((p = strtol(points, NULL, 10)) == 0) {
            p = 500;
        }
    }
    
    if (strcmp(token, "cube") == 0) {
        return buildRandomCube(p, p);
    }
    else if (!strcmp(token, "sphere")) {
        return buildRandomSphere(p, p);
    }
    else if (!strcmp(token, "cylinder")) {
        return buildRandomCylinder(p, p);
    }
    else if (!strcmp(token, "torus")) {
        return buildRandomTorus(p, p);
    }
    else if (!strcmp(token, "cone")) {
        return buildRandomCone(p, p);
    }
    
    fprintf(stderr, "Error: Unknown shape (line %d) - '%s'\n", line, token);
    exit(1);
}


/**
 * @brief Return an Operator corresponding to the one following 'op:'.
 *
 * @param token String following 'op:'.
 * @param line Current line number in the script.
 *
 * @return The corresponding operator.
 */
static Operator parseOp(char *token, int line) {
    if (token == NULL) {
        errno = EFAULT;
        perror("Error - parseOp ");
        exit(1);
    }
    
    if (!strcmp(token, "sous")) {
        return OP_SUBTRACTION;
    }
    
    if (!strcmp(token, "inter")) {
        return OP_INTERSECTION;
    }
    
    if (!strcmp(token, "union")) {
        return OP_UNION;
    }
    
    if (!strcmp(token, "equal")) {
        return OP_EQUAL;
    }
    
    fprintf(stderr, "Error: Unknown operator (line %d) - '%s'\n", line, token);
    exit(1);
}


/**
 * @brief Return a color corresponding to the one following 'col:'.
 *
 * @param r String following 'red:'.
 * @param g String following 'green:'.
 * @param b String following 'blue:'.
 * @param a String following 'alpha:'.
 *
 * @return The corresponding color.
 */
static float *parseCol(char *r, char *g, char *b, char *a) {
    if (r == NULL || g == NULL || b == NULL || a == NULL) {
        errno = EFAULT;
        perror("Error - parseCol ");
        exit(1);
    }
    
    float *color = malloc(sizeof(G3Xcolor));
    if (color == NULL) {
        errno = ENOMEM;
        perror("Error - parseCol ");
        exit(1);
    }
    
    color[0] = strtof(r, NULL);
    color[1] = strtof(g, NULL);
    color[2] = strtof(b, NULL);
    color[3] = strtof(a, NULL);
    
    return color;
}


/**
 * @brief Translate a node according to the given x, y, z.
 *
 * @param tree Node to be translated.
 * @param x Translation distance on X.
 * @param y Translation distance on Y.
 * @param z Translation distance on Z.
 */
static void parseT(Tree *tree, char *x, char *y, char *z) {
    if (tree == NULL || x == NULL || y == NULL || z == NULL) {
        errno = EFAULT;
        perror("Error - parseT ");
        exit(1);
    }
    
    translate(tree, strtof(x, NULL), strtof(y, NULL), strtof(z, NULL));
}


/**
 * @brief Rotate a node according to the given x, y, z.
 *
 * @param tree Node to be rotated.
 * @param x Rotation angle on X.
 * @param y Rotation angle on Y.
 * @param z Rotation angle on Z.
 */
static void parseR(Tree *tree, char *x, char *y, char *z) {
    if (tree == NULL || x == NULL || y == NULL || z == NULL) {
        errno = EFAULT;
        perror("Error - parseR ");
        exit(1);
    }
    
    rotate(tree, strtof(x, NULL), strtof(y, NULL), strtof(z, NULL));
}


/**
 * @brief Dilate a node according to the given x, y, z.
 *
 * @param tree Node to be dilated.
 * @param x Factor of dilatation on X.
 * @param y Factor of dilatation on Y.
 * @param z Factor of dilatation on Z.
 */
static void parseH(Tree *tree, char *x, char *y, char *z) {
    if (tree == NULL || x == NULL || y == NULL || z == NULL) {
        errno = EFAULT;
        perror("Error - parseH ");
        exit(1);
    }
    
    homothate(tree, strtof(x, NULL), strtof(y, NULL), strtof(z, NULL));
}


Tree *parseFile(FILE *file) {
    
    char *line = NULL, *token = NULL, *points, *r, *g, *b, *a, *x, *y, *z;
    Tree *current = NULL;
    Stack *stack = NULL;
    size_t len = 0;
    float *color;
    Operator op;
    int l, i;
    
    for (l = 1; getline(&line, &len, file) != -1; l++) {
        trimAndLower(line);
        if (!strlen(line) || line[0] == '#') {
            continue;
        }
        
        if ((token = strtok(line, ":")) == NULL) {
            fprintf(stderr, "Error: Syntax error (line %d).\n", l);
            exit(1);
        }
        trimAndLower(token);
        
        // Object
        if (!strcmp(token, "obj")) {
            if ((token = strtok(NULL, " ")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            points = strtok(NULL, " ");
            trimAndLower(token);
            current = newLeaf(parseObj(token, points, l));
            stack = addStack(stack, current);
        }
            
            // Color
        else if (!strcmp(token, "col")) {
            if (current == NULL) {
                fprintf(
                        stderr,
                        "Error: error (line %d) - Transformations can only be declared after an object/operator.\n", l
                );
                exit(1);
            }
            if ((r = strtok(NULL, ";")) == NULL || (g = strtok(NULL, ";")) == NULL || (b = strtok(NULL, ";")) == NULL
                || (a = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            color = parseCol(r, g, b, a);
            for (i = 0; i < current->obj->size; i++) {
                memcpy(current->obj->drawData[i].color, color, sizeof(G3Xcolor));
            }
            free(color);
        }
            
            // Translation
        else if (!strcmp(token, "t")) {
            if (current == NULL) {
                fprintf(
                        stderr,
                        "Error: error (line %d) - Transformations can only be declared after an object/operator.\n", l
                );
                exit(1);
            }
            if ((x = strtok(NULL, ";")) == NULL || (y = strtok(NULL, ";")) == NULL || (z = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseT(current, x, y, z);
        }
            
            // Dilatation
        else if (!strcmp(token, "h")) {
            if (current == NULL) {
                fprintf(
                        stderr,
                        "Error: error (line %d) - Transformations can only be declared after an object/operator.\n", l
                );
                exit(1);
            }
            if ((x = strtok(NULL, ";")) == NULL || (y = strtok(NULL, ";")) == NULL || (z = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseH(current, x, y, z);
        }
            
            // X Rotation
        else if (!strcmp(token, "rx")) {
            if (current == NULL) {
                fprintf(
                        stderr,
                        "Error: error (line %d) - Transformations can only be declared after an object/operator.\n", l
                );
                exit(1);
            }
            if ((x = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseR(current, x, "0", "0");
        }
            
            // Y Rotation
        else if (!strcmp(token, "ry")) {
            if (current == NULL) {
                fprintf(
                        stderr,
                        "Error: error (line %d) - Transformations can only be declared after an object/operator.\n", l
                );
                exit(1);
            }
            if ((y = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseR(current, "0", y, "0");
        }
            
            // Z Rotation
        else if (!strcmp(token, "rz")) {
            if (current == NULL) {
                fprintf(
                        stderr,
                        "Error: error (line %d) - Transformations can only be declared after an object/operator.\n", l
                );
                exit(1);
            }
            if ((z = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseR(current, "0", "0", z);
        }
            
            // Operation
        else if (!strcmp(token, "op")) {
            if (sizeStack(stack) < 2) {
                fprintf(stderr, "Error: error (line %d) - Cannot apply operator on less than 2 object.\n", l);
                exit(1);
            }
            if ((token = strtok(NULL, ":")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            trimAndLower(token);
            op = parseOp(token, l);
            current = newNode(popStack(&stack), popStack(&stack), op);
            stack = addStack(stack, current);
        }
            
            // Unknown
        else {
            fprintf(stderr, "Error: Unknown action (line %d) - '%s'\n", l, token);
            exit(1);
        }
    }
    free(line);
    
    if (sizeStack(stack) > 1) {
        fprintf(
                stderr,
                "Error: Last declared object/operator is not linked to other object/operator (maybe an operator is missing).\n"
        );
        exit(1);
        
    }
    if (sizeStack(stack) < 1) {
        fprintf(stderr, "Error: no object declared.\n");
        exit(1);
    }
    return popStack(&stack);
}
