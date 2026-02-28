
#include "data_tree.h"
#include "../Linked_list/linked_list.h"


typedef struct Tree_node
{
    struct Tree_node *prev;
    struct Tree_node *next_min;
    struct Tree_node *next_maj;

    Linked_list_manager lm; //of Data_word

    int checksum;
} 
Tree_node;

struct Data_tree
{
    Tree_node *root;
};

int add_data_to_node(void *data, size_t size, Heap_manager *hm, Linked_list_manager *lm, Data_type_tree_handler *dtth)
{
    if(!data || !hm || !lm || !lm->l) return -1;

    void *data_found = lm->find_data(data, size, dtth->compare, lm);
    
    if (!data_found) return dtth->append_to_the_list(data, size, hm, lm);
    
    else return dtth->if_found(data_found);
}


Tree_node *new_tree_node(void *data, int size, int checksum, Heap_manager *hm)
{
    Tree_node *n = hm->alloc(NULL, sizeof(Tree_node), hm->h);

    if(!n) return NULL;

    n->prev = NULL;
    n->next_min = NULL;
    n->next_maj = NULL;

    int err = 0;
    n->lm  = new_linked_list_manager(hm, &err);

    if(err) return NULL;

    n->checksum = checksum;

    return n;
}

Tree_node *create_new_node(
    void *data, 
    size_t size, 
    int checksum, 
    Tree_node *previous, 
    Heap_manager *hm, 
    Data_tree *dt,
    Data_type_tree_handler*dtth)
{
    if(!hm || !dt) return NULL;

    Tree_node *n = new_tree_node(data, size, checksum ,hm); if(!n) return NULL;

    int err = add_data_to_node(data, size, hm, &n->lm, dtth); if(err) return NULL;

    if (!previous) dt->root = n; //this is the root node

    else
    {
        n->prev = previous;
    
        if(checksum < previous->checksum) previous->next_min = n;
    
        else previous->next_maj = n;
    }

    return n;
}

int add_data_to_tree (void *data, size_t size, Heap_manager *hm, Data_tree_manager *dtm)
{
    if(!dtm || !dtm->dt) return -1;

    Data_tree *dt = dtm->dt;
    Data_type_tree_handler *dtth = &dtm->dtth;

    int checksum = dtth->compute_checksum(data, size);

    Tree_node *current = dt->root;//if there is no root then the code will automatically create a new node
    Tree_node *prev = NULL;

    while(current)
    {
        prev = current;

        if(checksum < current->checksum) current = current->next_min;

        else if (checksum > current->checksum) current = current->next_maj;

        else if (checksum == current->checksum) break;
    }

    if (current) return add_data_to_node(data, size, hm, &current->lm, dtth);

    else 
    {
        Tree_node *tn = create_new_node(data, size, checksum, prev, hm, dt, dtth);

        if (!tn) return -2;
    }

    return 0;
}


//add data
//find