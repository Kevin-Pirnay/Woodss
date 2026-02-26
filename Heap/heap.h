#pragma once

#include <stdlib.h>

typedef struct Heap Heap;

typedef struct Heap_manager
{
    Heap *h;
    
    void *(*alloc) (void *data, size_t size, struct Heap *h);
}
Heap_manager;


Heap *_new_heap_(size_t size);

Heap_manager new_heap_manager(Heap *h);

