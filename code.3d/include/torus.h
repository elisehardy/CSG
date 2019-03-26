#ifndef CSG_TORE_H
#define CSG_TORE_H

#include "object.h"


Object* buildRegularTorus(int n, int p);

void drawTorus(Object *obj, int cam);

Object *buildRandomTorus(int n, int p, int rayonInterne, int rayonExterne);


#endif
