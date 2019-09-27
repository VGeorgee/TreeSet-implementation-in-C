typedef struct node{

    void *value;
    node *left_child;
    node *right_child;

} NODE;

typedef struct treeset{

    node *root;
    int number_of_nodes;

    int (* equals)(const void *a, const void *b);
    int (* compare)(const void *a, const void *b);

} TreeSet;

int treeset_add(TreeSet *this_set, const void *element);
int treeset_contains(TreeSet *this_set, const void *element);
int treeset_remove(TreeSet *this_set, const void *element);
int treeset_size(TreeSet *this_set);
int treeset_isempty(TreeSet *this_set);
void treeset_clear(TreeSet *this_set);
void *treeset_ceiling(TreeSet *this_set, const void *element);
void *treeset_floor(TreeSet *this_set, const void *element);
void *treeset_first(TreeSet *this_set);
void *treeset_last(TreeSet *this_set);
void *treeset_higher(TreeSet *this_set, const void *element);
void *treeset_lower(TreeSet *this_set, const void *element);
void *treeset_pollfirst(TreeSet *this_set);
void *treeset_polllast(TreeSet *this_set);