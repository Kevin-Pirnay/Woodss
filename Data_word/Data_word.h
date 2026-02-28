#pragma once

#include "../Data_tree/data_tree.h"

typedef struct Data_word Data_word;

int compare(void *data, size_t size, void *to_compare);

int append_to_the_list(void *data, size_t size, Heap_manager *hm, Linked_list_manager *lm);

int if_found_increment_occurence(void *data);