
#include "data_tree.h"
#include "../Linked_list/linked_list.h"


Data_word *new_data_word(void *data, size_t size, Heap_manager *hm)
{
    Data_word *dw = hm->alloc(NULL, sizeof(Data_word), hm->h);

    if(!dw) return NULL;

    char *pstr = hm->alloc(data, size, hm->h);

    dw->word = pstr;
    dw->size = size;
    dw->occurrence = 1;

    return dw;
}

Data_word data_word_init(void *data, size_t size)
{
    Data_word dw;

    dw.word = data;
    dw.size = size;
    dw.occurrence = 1;

    return dw;
}

int compute_checksum(char *word, size_t size)
{
    int sum = 0; 
    
    for (size_t i = 0; i < size; i++) sum += word[i] * (i+1);
    
    return sum;
}

int add_data_to_list(void *data, size_t size, Heap_manager *hm, Linked_list_manager *lm)
{
    Data_word *dw_found = (Data_word *)lm->find(data, size, lm->l);
    
    if (!dw_found)
    {
        Data_word *new_dw = new_data_word(data, size, hm);

        if(!new_dw) return -1;

        lm->append(new_dw, sizeof(Data_word), DATA_WORD, hm, lm->l);
        
        return 0;
    }
    
    else dw_found->occurrence++;

    return 0;
}

Tree_node *new_tree_node(void *data, int size, int checksum, Heap_manager *hm)
{
    Tree_node *n = hm->alloc(NULL, sizeof(Tree_node), hm->h);

    n->prev = NULL;
    n->next_min = NULL;
    n->next_maj = NULL;

    n->lm  = new_linked_list_manager(hm);

    Data_word dw = data_word_init(data, size);
    n->lm.append(&dw, sizeof(Data_word), DATA_WORD, hm, n->lm.l);

    n->checksum = checksum;

    return n;
}

int add_data_word_to_tree (void *data, size_t size, Heap_manager *hm, Data_tree *dt)
{
    if(!dt) return -1;

    int checksum = compute_checksum((char *)data, size);

    Tree_node *current = dt->root;//if there is no root then the code will automatically create a new node
    Tree_node *prev = NULL;

    while(current)
    {
        prev = current;

        if(checksum < current->checksum) current = current->next_min;

        else if (checksum > current->checksum) current = current->next_maj;

        else if (checksum == current->checksum) break;
    }

    if (current) add_data_to_list(data, size, hm, &current->lm);

    else 
    {
        Tree_node *tn = new_tree_node(data, size, checksum, hm);

        if (!prev) { dt->root = tn; return 0; }//this is the root node

        tn->prev = prev;

        if(checksum < current->checksum) prev->next_min = tn;

        else prev->next_maj = tn;
    }

    return 0;
}
