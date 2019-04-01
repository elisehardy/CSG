#ifndef CSG_TORE_H
#define CSG_TORE_H

#include "object.h"


Object* buildRegularTorus(int n, int p);

bool insideTorus(Object *obj, G3Xcoord);

void drawTorus(Object *obj, int cam);

Object *buildRandomTorus(int n, int p, int rayonInterne, int rayonExterne);


#endif
