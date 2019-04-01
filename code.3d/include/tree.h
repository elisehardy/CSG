#ifndef CSG_TREE_H
#define CSG_TREE_H

typedef struct _node {
    Object *obj;
    char op;
    bool neg;
    double *md, *mi, *mn;
    _node *right, *left;
};

#endif
