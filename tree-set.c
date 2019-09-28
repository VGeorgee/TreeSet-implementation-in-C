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

void treeset_clear(TreeSet *this_set){
    NODE **stack_of_nodes = malloc(sizeof(NODE *) * this_set->number_of_nodes);
    int i, n;

    stack_of_nodes[0] = this_set->root;
    n = 1;

    for(i = 0; i < n; i++){
        if(stack_of_nodes[i]->left_child != NULL){
            stack_of_nodes[n++] = stack_of_nodes[i]->left_child;
        }
        else if(stack_of_nodes[i]->right_child != NULL){
            stack_of_nodes[n++] = stack_of_nodes[i]->right_child;
        }
    }

    for(i = n-1; i >= 0; i--){
        //free(stack_of_nodes[i]->value); might cause error
        stack_of_nodes[i]->value = NULL;
        stack_of_nodes[i]->left_child = NULL;
        stack_of_nodes[i]->right_child = NULL;
        free(stack_of_nodes[i]);
    }
}


int treeset_remove(TreeSet *this_set, const void *element){
    puts("treeset_remove not yet implemented");
    return 0;
}


void *treeset_first(TreeSet *this_set){

    if(this_set->root == NULL){
        return NULL;
    }

    NODE *pointer = this_set->root;

    while(pointer->left_child == NULL){
        pointer = pointer->left_child;
    }

    return pointer->value;
}

void *treeset_last(TreeSet *this_set){

    if(this_set->root == NULL){
        return NULL;
    }

    NODE *pointer = this_set->root;

    while(pointer->right_child == NULL){
        pointer = pointer->right_child;
    }
    
    return pointer->value;
}