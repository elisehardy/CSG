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
 * Trim whitespace on both side of str, returning the new size of str.
 *
 * @param str String to be trimmed.
 *
 * @return The size of the trimmed string.
 */
static int trim(char *str) {
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
    
    return size;
}


/**
 * Return an Object corresponding to the one follow 'obj:'.
 *
 * @param token String following 'obj:'.
 * @param line Current line number in the script.
 *
 * @return Pointer to the corresponding Object.
 */
static Object *parseObj(char *token, int line) {
    if (token == NULL) {
        errno = EFAULT;
        perror("Error - parseObj ");
        exit(1);
    }
    
    if (strcmp(token, "cube") == 0) {
        return buildRandomCube(400, 400);
    } else if (!strcmp(token, "sphere")) {
        return buildRandomSphere(1000, 1000);
    } else if (!strcmp(token, "cylinder")) {
        return buildRandomCylinder(1000, 1000);
    } else if (!strcmp(token, "torus")) {
        /* TODO FAUT DÉCIDER D'UNE VALEUR CANONIQUE POUR INNER RADIUS ET OUTER RADIUS */
        return buildRandomTorus(1000, 1000, 1, 2);
    } else if (!strcmp(token, "cone")) {
        return buildRandomCone(1000, 1000);
    }
    
    fprintf(stderr, "Error: Unknown shape (line %d) - '%s'\n", line, token);
    exit(1);
}


/**
 * Return an Operator corresponding to the one follow 'op:'.
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
        return SUBTRACTION;
    }
    
    if (!strcmp(token, "inter")) {
        return INTERSECTION;
    }
    
    if (!strcmp(token, "union")) {
        return UNION;
    }
    
    if (!strcmp(token, "equal")) {
        return EQUAL;
    }
    
    fprintf(stderr, "Error: Unknown operator (line %d) - '%s'\n", line, token);
    exit(1);
}


/**
 * Return a color corresponding to the one following 'col:'.
 *
 * @param b String following 'blue:'.
 * @param r String following 'red:'.
 * @param g String following 'green:'.
 * @param a String following 'alpha:'.
 * @param line Current line number in the script.
 *
 * @return The corresponding color.
 */
static float *parseCol(char *r, char *b, char *g, char *a) {
    if (r == NULL || g == NULL || b == NULL || a == NULL) {
        errno = EFAULT;
        perror("Error - parseCol ");
        exit(1);
    }
    
    float *color = malloc(sizeof(float) * 4);
    if (!color) {
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
 * Return a tranlsation corresponding to the one following 'T:'.
 *

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
 * Return a homothate corresponding to the one following 'col:'.
 *

 */
static void parseH(Tree *tree, char *x, char *y, char *z) {
    if (tree == NULL || x == NULL || y == NULL || z == NULL) {
        errno = EFAULT;
        perror("Error - parseT ");
        exit(1);
    }
    
    homothate(tree, strtof(x, NULL), strtof(y, NULL), strtof(z, NULL));
}


/**
 * Return a rotate corresponding to the one following 'col:'.
 *

 */
static void parseR(Tree *tree, char *x, char *y, char *z) {
    if (tree == NULL || x == NULL || y == NULL || z == NULL) {
        errno = EFAULT;
        perror("Error - parseT ");
        exit(1);
    }
    
    rotate(tree, strtof(x, NULL), strtof(y, NULL), strtof(z, NULL));
}


Tree *parseFile(FILE *file) {
    
    char *line = NULL, *token = NULL, *r, *g, *b, *a, *x, *y, *z;
    Tree *current = NULL;
    float *color;
    Stack *stack = NULL;
    size_t len = 0;
    int l, read, i;
    Operator op;
    
    for (l = 1; (read = getline(&line, &len, file)) != -1; l++) {
        trim(line);
        
        if (!strlen(line)) {
            continue;
        }
        
        if ((token = strtok(line, ":")) == NULL) {
            fprintf(stderr, "Error: Syntax error (line %d).\n", l);
            exit(1);
        }
        
        trim(token);
        if (!strcmp(token, "obj")) {
            if ((token = strtok(NULL, ":")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            trim(token);
            
            current = newLeaf(parseObj(token, l));
            stack = addStack(stack, current);
        } else if (!strcmp(token, "col")) {
            if ((r = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            if ((g = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            if ((b = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            if ((a = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            color = parseCol(r, g, b, a);
            for (i = 0; i < current->obj->size; i++) {
                memcpy(current->obj->color[i], color, sizeof(float) * 4);
            }
            
        } else if (!strcmp(token, "T")) {
            if ((x = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            if ((y = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            if ((z = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseT(current, x, y, z);
        } else if (!strcmp(token, "H")) {
            if ((x = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            if ((y = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            if ((z = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseH(current, x, y, z);
        } else if (!strcmp(token, "Rx")) {
            if ((x = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseR(current, x, "0", "0");
        } else if (!strcmp(token, "Ry")) {
            if ((y = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseR(current, "0", y, "0");
        } else if (!strcmp(token, "Rz")) {
            if ((z = strtok(NULL, ";")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            parseR(current, "0", "0", z);
        } else if (!strcmp(token, "op")) {
            if ((token = strtok(NULL, ":")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            trim(token);
            op = parseOp(token, l);
            current = newNode(popStack(&stack), popStack(&stack), op);
            stack = addStack(stack, current);
        } else {
            fprintf(stderr, "Error: Unknown action (line %d) - '%s'\n", l, token);
            exit(1);
        }
    }
    return popStack(&stack);
}
