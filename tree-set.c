#include "tree-set.h"


TreeSet *new_treeset(int (* equals)(const void *a, const void *b), int (* compare)(const void *a, const void *b)){
    TreeSet *tree = (TreeSet *) malloc(sizeof(TreeSet));

    tree->equals = equals;
    tree->compare = compare;

    tree->number_of_nodes = 0;
    tree->root = NULL;

    return tree;
}

NODE *new_node(const void *element){
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->value = element;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}

int treeset_add(TreeSet *this_set, const void *element){

/**
 * adding new element to root, if set is empty
 * */

    if(this_set->root == NULL){
        this_set->root = new_node(element);
        return 1;
    }

    NODE *this_element = this_set->root;
    NODE *pointer = this_set->root;
    NODE *new_element = new_node(element);

    while(pointer != NULL){
        if(this_set->equals(pointer->value, element)){
            return 0;
        }
        else if(this_set->compare(pointer->value, element) < 0){
            this_element = pointer;
            pointer = pointer->right_child;
        }
        else {
            this_element = pointer;
            pointer = pointer->left_child;
        }
    }

    if(this_set->compare(this_element->value, element) < 0){
        this_element->right_child = new_element;
    }
    else{
        this_element->left_child = new_element;    
    }

    this_set->number_of_nodes++;

    return 1;

/**
 * 
 * 
 * NEEDS REFACTORING
 * */
}



int treeset_contains(TreeSet *this_set, const void *element){

    NODE *pointer = this_set->root;

    while(pointer != NULL){
        if(this_set->equals(pointer->value, element)){
            return 1;
        }
        else if(this_set->compare(pointer->value, element) < 0){
            pointer = pointer->right_child;
        }
        else{
            pointer = pointer->left_child;
        }
    }
    return 0;
}



int treeset_size(TreeSet *this_set){
    return this_set->number_of_nodes;
}


int treeset_isempty(TreeSet *this_set){
    return this_set->number_of_nodes == 0;
}