#include "data_word.h"
#include "../Data_tree/data_tree.h"

#include "stddef.h"


typedef struct
{
    char *word;
    size_t size;
    int occurrence;
}
Data_word;

Data_word init_data_word(void *data, size_t size, Heap_manager *hm, int *err)
{
    Data_word dw = {0};

    if (!data || !hm || err) { *err = -1; return dw;}

    dw.word = hm->alloc(data, size, hm); if (!dw.word) *err = -2;

    dw.size = size;

    dw.occurrence = 1;

    return dw;
}

int compare(void *data, size_t size, void *to_compare)
{
    Data_word *dw = (Data_word *) to_compare;

    int match = 0;

    if (size == dw->size)
    {
        match = 1;

        for (size_t i = 0; i < size; i++)
        {
            if (((char *)data)[i] != dw->word[i]) { match = 0; break; }
        }        
    }
    
    return match;
}

int append_to_the_list(void *data, size_t size, Heap_manager *hm, Linked_list_manager *lm)
{
    int err = 0;

    Data_word new_dw = init_data_word(data, size, hm, &err);

    if(err) return -1;

    err = lm->append(&new_dw, sizeof(Data_word), DATA_WORD, hm, lm); 
    
    if(err) return -2;

    return 0;
}

int if_found_increment_occurence(void *data)
{
    if(!data) return -1;

    Data_word *d = (Data_word *)data;

    d->occurrence++;

    return 0;
}