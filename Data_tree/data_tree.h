#pragma once

#include "stddef.h"
#include "../Linked_list/linked_list.h"

typedef struct
{
    char *word;
    size_t size;
    int occurrence;
}
Data_word;

typedef struct Tree_node
{
    struct Tree_node *prev;
    struct Tree_node *next_min;
    struct Tree_node *next_maj;

    Linked_list_manager lm;//of Data_word

    int checksum;
} 
Tree_node;


typedef struct Data_tree
{
    Tree_node *root;
    Tree_node *current;

    int (*add_data_to_tree) (void *data, int size, Heap_manager *hm, struct Data_tree *dt);
}
Data_tree;


//add
//find
//