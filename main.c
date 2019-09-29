#include <stdio.h>
#include <stdlib.h>
#include "tree-set.h"

// to run tests, download https://github.com/VGeorgee/standard-types-for-C
#include "standard-types.h"

int main()
{
    /**
     * tests for TreeSet
     * */

    TreeSet *test = new_treeset(int_equals, int_compare, int_print);

    for(int i = 0; i < 10; i++){
        treeset_add(test, new_int(i));
    }

    puts("adding elements done");

    puts("preorder: ");
    treeset_print_preorder(test);
    
    puts("\ninorder: ");
    treeset_print_inorder(test);
    
    puts("\npostorder: ");
    treeset_print_postorder(test);

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
