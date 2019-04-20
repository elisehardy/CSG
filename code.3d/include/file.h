#ifndef CSG_FILE_H
#define CSG_FILE_H

#include <stdio.h>
#include "tree.h"


/**
 * Parse the given file, construction the corresponding CSG tree.
 *
 * @param file File to be parsed.
 *
 * @return The parsed Tree.
 */
Tree *parseFile(FILE *file);

#endif
