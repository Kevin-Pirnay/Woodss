#pragma once

#include "stddef.h"
#include "../Linked_list/linked_list.h"

typedef struct
{
    char *word;
    int occurence;
}
Data_word;

typedef struct Tree_node
{
    struct Tree_node *prev;
    struct Tree_node *next_min;
    struct Tree_node *next_maj;

    Linked_list_manager *l;//of Data_word

    int checksum;
} 
Tree_node;


typedef struct
{
    Tree_node *head;
    Tree_node *ptr;

    int (*add_data) (Tree_node *n, Data_tree dt);
}
Data_tree;

//add
//find
//