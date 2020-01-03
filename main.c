#include <stdio.h>
#include <stdlib.h>
#include "tree-set.h"



int *new_int(int n){
    int *new_number = malloc(sizeof (int));
    *new_number = n;
    return new_number;
}
int int_equals(const void *a, const void *b){
    int na = *(int *)a;
    int nb = *(int *)b;

    return na == nb;
}

int int_compare(const void *a, const void *b){
    int na = *(int *)a;
    int nb = *(int *)b;

    if(na > nb){
        return 1;
    }
    if(na < nb){
        return -1;
    }
    return 0;
}

int main()
{
    /**
     * tests for TreeSet
     * */

    TreeSet *test = new_treeset(int_equals, int_compare);

    for(int i = 0; i < 10; i++){
        treeset_add(test, new_int(i));
    }

    puts("adding elements done");
    printf("biggest element should be 9, found: %d\n", *(int *)treeset_last(test));
    printf("smallest element should be 0, found: %d\n", *(int *)treeset_first(test));

    int *biggest_poll = (int *) treeset_poll_last(test);
    int *smallest_poll = (int *) treeset_poll_first(test);

    printf("biggest element should be 9, polled element: %d\n", *biggest_poll);
    printf("smallest element should be 0, polled element: %d\n", *smallest_poll);

    printf("biggest element should be 8, found: %d\n", *(int *)treeset_last(test));
    printf("smallest element should be 1, found: %d\n", *(int *)treeset_first(test));

    return 0;
}
