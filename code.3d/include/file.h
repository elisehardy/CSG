/** @file file.h
 *
 *  @brief Header for the **file parsing** functions.
 *
 *  @author Elise Hardy
 *  @author Quentin Coumes
 */

#ifndef CSG_FILE_H
#define CSG_FILE_H

#include <stdio.h>
#include "tree.h"


/**
 * @brief  Parse the given file, construction the corresponding CSG tree.
 *
 * @param file File to be parsed.
 *
 * @return The parsed Tree.
 */
Tree *parseFile(FILE *file);

#endif
