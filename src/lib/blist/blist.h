#ifndef BLIST
#define BLIST
#include <stdlib.h>

typedef struct Blist {
  void** values;
  size_t list_len;
} Blist_;

Blist_* blist_init();
Blist_* blist_append(Blist_* list, void* item);
Blist_* blist_insert(Blist_* list, void* item, int index);
void* blist_get(Blist_* list, int index);
Blist_* blist_remove(Blist_* list, int index);
int blist_index_of(Blist_* list, void* item);
int blist_contains(Blist_* list, void* item);
void* blist_pop(Blist_* list);
Blist_* blist_replace(Blist_* list, void* item, int index);
Blist_* blist_slice(Blist_* list, int start, int end);
Blist_* blist_clearall(Blist_* list);
Blist_* blist_foreach(Blist_* list,void*(*func)(void*arg));
Blist_* blist_filter(Blist_* list, int(*func)(void*arg));
Blist_* blist_clear(Blist_* list, void* item);
Blist_* blist_move(Blist_* list, int index, int pos);
Blist_* blist_map(Blist_* list, void*(*func)(void*arg));
void* blist_reduce(Blist_* list, void*(*func)(void*arg1, void*arg2));
Blist_* blist_combine(Blist_* list1, Blist_* list2);
void* blist_find(Blist_ * list, int( * func)(void * arg));
Blist_* blist_fill(Blist_ * list, void* item);
int blist_every(Blist_ * list, int( * func)(void * arg));
int blist_some(Blist_ * list, int( * func)(void * arg));
int blist_last_index_of(Blist_* list, void* item);
Blist_* blist_reverse(Blist_* list);

#endif