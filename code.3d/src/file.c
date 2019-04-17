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
#include "../include/queue.h"


/**
 * Trim whitespace on both side of str, returning the new size of str.
 *
 * @param str String to bez trimmed.
 *
 * @return The size of the trimmed string.
 */
static int trim(char *str) {
    int size, i = 0, len = strlen(str) - 1;
    
    while (isspace(str[i]) && i <= len) {
        i++;
    }
    while (isspace(str[len]) > i) {
        len--;
    }
    
    if (i > len) {
        str[0] = '\0';
        return 0;
    }
    
    str[len + 1] = '\0';
    size = len - i + 1;
    
    printf("%s %d %d %d\n", str, i, len, size);
    memmove(str, str + i, size);
    
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
        return buildRandomCube(1000, 1000);
    }
    else if (!strcmp(token, "sphere")) {
        return buildRandomSphere(1000, 1000);
    }
    else if (!strcmp(token, "cylinder")) {
        return buildRandomCylinder(1000, 1000);
    }
    else if (!strcmp(token, "torus")) {
        /* FAUT DÉCIDER D'UNE VALEUR CANONIQUE POUR INNER RADIUS ET OUTER RADIUS */
        return buildRandomTorus(1000, 1000, 10, 20);
    }
    else if (!strcmp(token, "cone")) {
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


Tree *parseFile(FILE *file) {
    char *line = NULL, *token = NULL;
    Queue *queue = NULL;
    Tree *root = NULL;
    size_t len = 0;
    int l, read;
    
    for (l = 1; (read = getline(&line, &len, file)) != -1; l++) {
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
            addQueue(queue, parseObj(token, l));
        }
        
        else if (!strcmp(token, "obj")) {
        }
        
        else if (!strcmp(token, "col")) {
        }
        
        else if (!strcmp(token, "T")) {
        }
        
        else if (!strcmp(token, "H")) {
        }
        
        else if (!strcmp(token, "Rx")) {
        }
        
        else if (!strcmp(token, "Ry")) {
        }
        
        else if (!strcmp(token, "Rz")) {
        }
        
        else if (!strcmp(token, "op")) {
            if ((token = strtok(NULL, ":")) == NULL) {
                fprintf(stderr, "Error: Syntax error (line %d).\n", l);
                exit(1);
            }
            trim(token);
            parseOp(token, l);
        }
        
        else {
            fprintf(stderr, "Error: Unknown action (line %d) - '%s'\n", l, token);
            exit(1);
        }
    }
    
    return root;
}
