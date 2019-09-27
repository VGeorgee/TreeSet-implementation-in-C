#include "tree-set.h"


TreeSet *new_treeset(int (* equals)(const void *a, const void *b), int (* compare)(const void *a, const void *b)){
    TreeSet *tree = (TreeSet *) malloc(sizeof(TreeSet));

    tree->equals = equals;
    tree->compare = compare;

    tree->number_of_nodes = 0;
    tree->root = NULL;

    return tree;
}
