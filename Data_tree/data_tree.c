
#include "data_tree.h"

int compute_checksum(char *word, int size)
{
    int sum = 0; 
    
    for (int i = 0; i < size; i++) sum += word[i] * (i+1);
    
    return sum;
}

int add_to_list(void *data, int size, Linked_list_manager *l)
{
    //verify is the word exist in the list
    //if yes -> incerement occurence
    //else, crate new node
}

int create_new_node()
{

}

int add_data (void *data, int size, int checksum, Data_tree *dt)
{
    if(!dt || !dt->head) return -1;

    Tree_node *current = dt->head;

    while(current)
    {
        if(checksum < current->checksum) current = current->next_min;

        else if (checksum > current->checksum) current = current->next_maj;

        else if (checksum == current->checksum) break;
    }

    if (current) add_to_list(data, size, current->l);

    else create_new_node();

    return 0;
}
