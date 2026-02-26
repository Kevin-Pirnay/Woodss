#pragma once

#include <stdlib.h>
#include "../Heap/heap.h"

//!!!need to adapt to nodes of the tree!!!
typedef enum
{
    INT,
    STRING,
    DATA_WORD
}
Data_type;

typedef struct Linked_list Linked_list;

typedef struct Linked_list_manager
{
    Linked_list *l;

    int (*append)(void *data, size_t s, Data_type t, Heap_manager *h, struct Linked_list *l);
    int (*append_at)(void *data, size_t s, Data_type t, Heap_manager *h, int index, struct Linked_list *l);
    int (*remove_at)(int index, struct Linked_list *l);
    int (*print_list)(struct Linked_list *l);
} 
Linked_list_manager;


Linked_list_manager new_linked_list_manager(Heap_manager *hm);
