#include "stdio.h"
#include "heap.h"


struct Heap
{
    char *memory;

    size_t ptr;

    size_t total_size;
};


void *alloc(void *data, size_t size, Heap_manager *hm)
{
    if(!hm || !hm->h || !hm->h->memory) return NULL;

    Heap *h = hm->h;

    if (h->ptr + size > h->total_size) return NULL;//ptr is already offset by one

    void *adresse = (void *) &h->memory[h->ptr];

    for (size_t i = 0; i < size; i++)
    {
        if (data) h->memory[h->ptr++] = ((char *)data)[i];
        
        else h->memory[h->ptr++] = 0;
    }

    return adresse;
}

Heap *_new_heap_(size_t size)
{
    char *m = malloc(size);

    if (!m) { printf("Memory allocation failed for the amount of memory ask on the heap\n"); return NULL; }

    Heap *h = malloc(sizeof(Heap));

    if(!h) { printf("Memory allocation failed during the storage of heap struct \n"); free(m); return NULL; }

    h->memory = m;
    h->total_size = size;
    h->ptr = 0;

    return h;
}

void free_heap(Heap *h)
{
    if(!h ||!h->memory) return;

    free(h->memory);
    
    free(h);
}

Heap_manager new_heap_manager(Heap *h)
{
    if(!h) {printf("A heap must be instantiate first in order to initilaise a new heap_manager"); exit(-1);}

    Heap_manager hm;

    hm.h = h;

    hm.alloc = alloc;

    return hm;
}