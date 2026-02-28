#pragma once

#include "stddef.h"
#include "../Linked_list/linked_list.h"


typedef struct Data_tree Data_tree;

typedef struct
{
    int (*compute_checksum)(void *data, size_t size);
    int (*compare)(void *data, size_t size, void *to_compare);
    int (*append_to_the_list)(void *data, size_t size, Heap_manager *hm, Linked_list_manager *lm);
    int (*if_found)(void *data);
}
Data_type_tree_handler;


typedef struct Data_tree_manager
{
    Data_tree *dt;

    Data_type_tree_handler dtth;

    int (*add_data_to_tree) (void *data, size_t size, Heap_manager *hm, struct Data_tree_manager *dtm);
}
Data_tree_manager;

//add
//find
//