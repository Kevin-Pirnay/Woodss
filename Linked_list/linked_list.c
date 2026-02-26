#include "stdio.h"
#include "linked_list.h"
#include "../Heap/heap.h"

//constructor
//append
//remove
//print

typedef struct Data_struct
{
    Data_type type;
    size_t size;
    void *data;
}
Data_struct;


typedef struct Node
{
    struct Node *prev;
    struct Node *next;
    Data_struct *data_struct;
}
Node;

struct Linked_list
{
    Node *head;
    Node *tail;
    Node *ptr;
    int count;

    Node *(*create_new_node)(void *data, size_t size, Data_type t, Heap_manager *h);
};


Data_struct *store_data_struct(Data_struct *d, Heap_manager *hm)
{
    void *ds = hm->alloc(d->data, d->size, hm->h); if(!ds) return NULL;

    d->data = ds;

    void *r = hm->alloc(d, sizeof(Data_struct), hm->h);

    if (!r) return NULL;

    return (Data_struct *)r;
}

Data_struct *new_data_struct(void *data, size_t size, Data_type t, Heap_manager *h)
{
    Data_struct d;

    d.type = t;
    d.data = data;
    d.size = size;

    if(t == STRING && *(((char *)data) + (size-1)) != '\0') {printf("error while storing data structure string! Data doesn't end with null terminator\n"); return NULL;}
    
    return store_data_struct(&d,h);
}


Node *new_node(Data_struct *d, Heap_manager *hm)
{
    Node n;

    n.prev = NULL;
    n.next = NULL;
    n.data_struct = d;
     
    return (Node *) hm->alloc(&n, sizeof(Node),hm->h);
}

Node *create_new_node(void *data, size_t size, Data_type t, Heap_manager *hm)
{
    Data_struct *d = new_data_struct(data, size, t, hm);

    if (!d) return NULL;

    return new_node(d,hm);
}

int initialise_list(Linked_list *l, Node *n)
{
    if (!l || !n) return -1;

    if (l->count > 0) { printf("list must be empty\n"); return -2; }

    l->head = n;
    l->tail = n;
    l->ptr = n;
    l->count++;

    return 0;
}

int append_at_first_pos(Linked_list *l, Node *n)
{
    if (!l || !n) return -1;

    l->ptr = l->head;

    l->head = n;

    l->head->next = l->ptr;

    l->ptr->prev = l->head;

    l->count++;

    return 0;
}

int append_at_middle_pos(Linked_list *l, Node *n, int index)
{
    if (!l || !n) return -1;

    if (l->count < 2) { printf("must be more than one node to append at the middle\n"); return -2; }

    if (index < 0 || index >= l->count) { printf("cannot add at the tail or beyond list count\n"); return -3; }

    Node *prev = l->head;
    Node *next = l->head->next;

    int i = 0;

    while(++i < index)
    {
        prev = next;
        next = prev->next;

        if (!next) { printf("cannot find next node\n"); return -4; }
    }

    prev->next = n;
    n->prev = prev;
    n->next = next;
    next->prev = n;

    l->count++;

    return 0;
}

int append_at_end_pos(Linked_list *l, Node *n)
{
    if (!l || !n) return -1;

    if ( l->count < 1 ) { printf("a tail must exist\n"); return -2; }

    l->tail->next = n;

    n->prev = l->tail;

    l->tail = n;

    l->count++;

    return 0;
}

int append_at(void *d, size_t s, Data_type t, Heap_manager *hm, int index, Linked_list *l)
{
    if (!l || index > l->count || index < 0) return -1;

    Node *n = l->create_new_node(d, s, t, hm); if (!n) { printf("memory allocation error to store node\n"); return -2; }
    
    int e;//error

    if (l->count == 0) { e = initialise_list(l,n); if (e) { printf("initialisation list error\n"); return e; }}

    else if (index == 0) { e = append_at_first_pos(l, n); return e; }

    else if (index == l->count) { e = append_at_end_pos(l,n); return e; }

    else  { e = append_at_middle_pos(l,n, index); return e; }

    return 0;
}

int append(void *d, size_t s, Data_type t, Heap_manager *hm, Linked_list *l)
{
    int e = 0;

    if (l->count == 0) e = append_at(d,s,t,hm,0,l);
   
    else e = append_at(d,s,t,hm,l->count,l);

    return e;
}

int print_data_struct(Data_struct *d)
{
    if (!d) return -1;

    if (d->type == INT) printf("%d\n", *(int *)d->data);

    else if (d->type == STRING) printf("%s\n", (char *)d->data);

    else return -2;

    return 0;
}

int print_list(Linked_list *l)
{
    if(!l || !l->head || !l->head->data_struct) return -1;

    Node *current = l->head;

    int i = 0;

    while (1)
    {
        int e = print_data_struct(current->data_struct); if(e) return -2;

        if ( ++i >= l->count ) break; 

        current = current->next;

        if (!current || !current->data_struct) return -3;
    }

    printf("\n");

    return 0;
}

int remove_at(int index, Linked_list *l)
{
    if (!l || index < 0 || index >= l->count) return -1;

    if(l->count == 0) return -2;
    
    Node *current = l->head;

    int i = 0;

    while(++i < index)
    {
        current = current->next;

        if (!current) return -3;
    }

    Node *prev = current->prev;
    Node *next = current->next;

    if(!current->prev) l->head = current->next;

    if(!current->next) l->tail = current->prev;
 
    if(current->prev) current->prev->next = current->next;

    if(current->next) current->next->prev = current->prev;

    l->count--;

    return 0;
}

Linked_list *new_linked_list(Heap_manager *hm)
{
    Linked_list *l = (Linked_list *)hm->alloc(NULL, sizeof(Linked_list), hm->h);

    if(!l) { printf("failed to allocate memory to store linked_list"); return NULL; }

    l->head = NULL;
    l->tail = NULL;
    l->ptr = NULL;
    l->count = 0;

    l->create_new_node = create_new_node;

    return l;
}

Linked_list_manager new_linked_list_manager(Heap_manager *hm)
{
    Linked_list_manager lm;

    lm.l = new_linked_list(hm);
    
    lm.append_at = append_at;
    lm.append = append;
    lm.print_list = print_list;
    lm.remove_at = remove_at;

    return lm;
}