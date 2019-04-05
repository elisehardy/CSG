#ifndef CSG_CYLINDER_H
#define CSG_CYLINDER_H

#include "object.h"



bool insideCylinder(Object *obj, G3Xpoint p);


Object* buildRandomCylinder(int n, int p);

#endif
