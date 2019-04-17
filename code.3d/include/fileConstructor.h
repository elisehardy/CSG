#ifndef CSG_FILECONSTRUCTOR_H
#define CSG_FILECONSTRUCTOR_H


typedef struct _cell {
    Object *obj;
    struct _cell *tail;
    struct _cell *next;
} Queue;


void readAndFillTree(FILE *file, Tree *tree);

#endif
