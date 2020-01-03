#include "tree-set.h"


TreeSet *new_treeset(int (* equals)(const void *a, const void *b), int (* compare)(const void *a, const void *b), void (* print)(const void *a)){
    TreeSet *tree = (TreeSet *) malloc(sizeof(TreeSet));

    tree->equals = equals;
    tree->compare = compare;
    tree->print = print;

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


int treeset_remove(TreeSet *this_set, const void *element){
    
    if(this_set->root == NULL){
        return 0;
    }

    NODE *search_pointer, *search_pointer_predecessor;
    search_pointer = this_set->root;

    while(!this_set->equals(search_pointer->value, element)){

        search_pointer_predecessor = search_pointer;

        search_pointer = this_set->compare(search_pointer->value, element) < 0 
        ? search_pointer->right_child 
        : search_pointer->left_child;
        
        if(search_pointer == NULL){
            return 0;
        }


        /**
         * 
         * 
         * 
         * 
         * 
         * 
         * 
         * 
         * 
         * 
         * 
         * */
    }
    puts("treeset_remove not yet implemented");
    return 0;
}



int treeset_size(TreeSet *this_set){
    return this_set->number_of_nodes;
}

int treeset_isempty(TreeSet *this_set){
    return this_set->number_of_nodes == 0;
}

void treeset_clear(TreeSet *this_set){
    NODE **array_of_nodes = malloc(sizeof(NODE *) * this_set->number_of_nodes);
    int i, n;

    array_of_nodes[0] = this_set->root;
    n = 1;

    for(i = 0; i < n; i++){
        if(array_of_nodes[i]->left_child != NULL){
            array_of_nodes[n++] = array_of_nodes[i]->left_child;
        }
        else if(array_of_nodes[i]->right_child != NULL){
            array_of_nodes[n++] = array_of_nodes[i]->right_child;
        }
    }

    for(i = n-1; i >= 0; i--){
        //free(array_of_nodes[i]->value); might cause error
        array_of_nodes[i]->value = NULL;
        array_of_nodes[i]->left_child = NULL;
        array_of_nodes[i]->right_child = NULL;
        free(array_of_nodes[i]);
    }
    free(array_of_nodes);
    this_set->root = NULL;
    this_set->number_of_nodes = 0;
}

void *treeset_ceiling(TreeSet *this_set, const void *element){
    NODE *pointer = this_set->root;
    while(pointer && this_set->compare(pointer->value, element) < 0){
        pointer = pointer->right_child;
    }
    return pointer;
}

void *treeset_floor(TreeSet *this_set, const void *element){
    NODE *pointer = this_set->root;
    while(pointer && this_set->compare(pointer->value, element) < 0){
        pointer = pointer->left_child;
    }
    return pointer;
}

void *treeset_first(TreeSet *this_set){

    if(this_set->root == NULL){
        return NULL;
    }

    NODE *pointer = this_set->root;

    while(pointer->left_child != NULL){
        pointer = pointer->left_child;
    }

    return pointer->value;
}

void *treeset_last(TreeSet *this_set){

    if(this_set->root == NULL){
        return NULL;
    }

    NODE *pointer = this_set->root;

    while(pointer->right_child != NULL){
        pointer = pointer->right_child;
    }

    return pointer->value;
}


void *treeset_higher(TreeSet *this_set, const void *element){
    NODE *pointer = treeset_ceiling(this_set, element);
    return pointer ? pointer->right_child : NULL;
}

void *treeset_lower(TreeSet *this_set, const void *element){
    NODE *pointer = treeset_floor(this_set, element);
    return pointer ? pointer->left_child : NULL;
}

void *treeset_poll_first(TreeSet *this_set){

    if(this_set->root == NULL){
        return NULL;
    }

    NODE *pointer, *previous_pointer;
    void *data_from_first = NULL;
    pointer = previous_pointer = this_set->root;

    while(pointer->left_child != NULL){
        previous_pointer = pointer;
        pointer = pointer->left_child;
    }

    if(previous_pointer != pointer){
        previous_pointer->left_child = pointer->right_child;
    }
    else if(this_set->root == pointer){
        this_set->root = this_set->root->right_child;
    }

    data_from_first = pointer->value;
    free(pointer);

    return data_from_first;
}
void *treeset_poll_last(TreeSet *this_set){
    
    if(this_set->root == NULL){
        return NULL;
    }

    NODE *pointer, *previous_pointer;
    void *data_from_first = NULL;
    pointer = previous_pointer = this_set->root;

    while(pointer->right_child != NULL){
        previous_pointer = pointer;
        pointer = pointer->right_child;
    }

    if(previous_pointer != pointer){
        previous_pointer->right_child = pointer->left_child;
    }  
    else if(this_set->root == pointer){
        this_set->root = this_set->root->left_child;
    }

    data_from_first = pointer->value;
    free(pointer);

    return data_from_first;
}

void treeset_print_preorder(TreeSet *this_set){
    preorder_printer(this_set->root, this_set->print);
}

void preorder_printer(NODE *pointer, void (* print)(const void *a)){
    if(pointer == NULL){
        return;
    }
    print(pointer->value);
    preorder_printer(pointer->left_child, print);
    preorder_printer(pointer->right_child, print);
}

void treeset_print_inorder(TreeSet *this_set){
    inorder_printer(this_set->root, this_set->print);
}

void inorder_printer(NODE *pointer, void (* print)(const void *a)){
    if(pointer == NULL){
        return;
    }
    inorder_printer(pointer->left_child, print);
    print(pointer->value);
    inorder_printer(pointer->right_child, print);
}

void treeset_print_postorder(TreeSet *this_set){
    postorder_printer(this_set->root, this_set->print);
}

void postorder_printer(NODE *pointer, void (* print)(const void *a)){
    if(pointer == NULL){
        return;
    }
    postorder_printer(pointer->left_child, print);
    postorder_printer(pointer->right_child, print);
    print(pointer->value);
}