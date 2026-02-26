#include "./Heap/heap.h"
#include "./Data_tree/data_tree.h"
#include "stdlib.h"
#include "stdio.h"

#define MEMORY_ALLOCATED 50000000

int main()
{
    Heap *h = _new_heap_(MEMORY_ALLOCATED);

    Heap_manager hm = new_heap_manager(h);

    free(h);

    return 0;
}