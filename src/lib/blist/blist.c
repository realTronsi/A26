#include "../blist/blist.h"

#include <stdio.h>

#include <ctype.h>

Blist_ * blist_init() {
  Blist_ * list = calloc(1, sizeof(*list));

  list->list_len = 0;
  list->values = calloc(1, sizeof(*list->values));
  return list;
}

Blist_* blist_append(Blist_ * list, void * item) {
  list->list_len++;

  list->values = realloc(list->values, (list->list_len + 1) * sizeof(*list->values));
  list->values[list->list_len - 1] = item;

  return list;
}

Blist_ * blist_insert(Blist_ * list, void * item, int index) {
  if (index > list->list_len) {
    for (int i = list->list_len; i < index; i++) {
      list->list_len++;
      list->values = realloc(
        list->values,
        (list->list_len + 1) * sizeof(*list->values)
      );

      list->values[i] = NULL;
    }

    list->list_len++;
    list->values = realloc(
      list->values,
      (list->list_len + 1) * sizeof(*list-> values)
    );
    list->values[index] = item;

    return list;
  } else {
    list->list_len++;

    list->values = realloc(list->values, (list->list_len) * sizeof(*list->values));

    for (int i = list->list_len - 1; i > index - 1; i--) {
      list->values[i + 1] = list->values[i];
    }
    list->values[index] = item;
  }

  return list;
}

void * blist_get(Blist_ * list, int index) {
  if (index > list -> list_len || index < 0) {
    fprintf(stderr, "\n\tIndex out of bound(%d)", index);
    exit(EXIT_FAILURE);
  }

  return list->values[index];
}

Blist_ * blist_remove(Blist_ * list, int index) {
  if (index > list -> list_len || index < 0) {
    fprintf(stderr, "\n\tIndex out of bound(%d)", index);
    exit(EXIT_FAILURE);
  }

  for (int i = index; i < list -> list_len; i++) {
    list->values[i] = list->values[i + 1];
  }

  list->list_len--;
  list->values = calloc(list->list_len+1, sizeof(*list->values));

  return list;
}

int blist_index_of(Blist_ * list, void * item) {
  for (int i = 0; i < list->list_len; i++) {
    if (item == list->values[i])
      return i;
  }

  return -1;
}

int blist_contains(Blist_ * list, void * item) {
  if (blist_index_of(list, item) != -1)
    return 0;

  return 1;
}

Blist_* blist_replace(Blist_ * list, void * item, int index) {
  if (index > list -> list_len || index < 0) {
    fprintf(stderr, "\n\tIndex out of bound(%d)", index);
    exit(EXIT_FAILURE);
  }

  list -> values[index] = item;
  return list;
}

void * blist_pop(Blist_ * list) {

  void * item = list->values[list->list_len - 1];

  list->values[list->list_len - 1] = (void * ) 0;

  list->list_len--;
  list->values = realloc(
    list->values,
    list->list_len * sizeof(*list->values)
  );

  return item;
}

Blist_* blist_slice(Blist_ * list, int start, int end) {
  Blist_* new_list = blist_init();
  if (
    start > list->list_len || start < 0 ||
    end > list->list_len || end < 0
  ) {
    fprintf(stderr, "\n\tIndex out of bound(%d)", start);
    exit(EXIT_FAILURE);
  }
  int index = end + 1;
  if (start < end) {
    for (int i = end; i >= start; i--) {
      blist_append(new_list, list->values[i]);
    }
    return new_list;
  }
  if (start > end) {
    for (int i = start; i >= end; i--) {
      blist_append(new_list, list->values[i]);
    }
    return new_list;
  }

  blist_append(new_list, list->values[start]);

  return new_list;
}

Blist_* blist_free(Blist_* list)
{
    list->list_len = 0;

    free(list->values);
    free(list);

    return list;
}
Blist_* blist_clearall(Blist_ * list) 
{

    list = blist_free(list);

    list = blist_init();

    return list;
}


Blist_* blist_foreach(Blist_ * list, void * ( * func)(void * arg)) {
  for (int i = 0; i < list -> list_len; i++) {
    list->values[i] = func(list->values[i]);
  }
  return list;
}

Blist_* blist_filter(Blist_ * list, int( * func)(void * arg)) {
  Blist_ * new_list = blist_init();

  for (int i = 0; i < list -> list_len; i++) {

    if (func(list->values[i]) == 0)
      blist_append(new_list, list -> values[i]);
    if (func(list->values[i]) == 1)
      continue;
  }

  return new_list;
}

Blist_* blist_clear(Blist_ * list, void * item) {
  for (int i = 0; i < list -> list_len; i++) {
    if (list->values[i] == item) {
      blist_remove(list, i);
      i--;
    }
  }
  return list;
}

Blist_* blist_move(Blist_ * list, int index, int pos) {
  if (index > list->list_len || index < 0 || pos < 0) {
    fprintf(stderr, "\n\tIndex out of bound(%d)", index);
    exit(EXIT_FAILURE);
  }

  void * item = list->values[index];
  blist_remove(list, index);
  blist_insert(list, item, pos);

  return list;
}

Blist_* blist_map(Blist_ * list, void * ( * func)(void * arg)) {
  Blist_ * new_list = blist_init();
  for (int i = 0; i < list->list_len; i++) {
    blist_append(new_list, func(list->values[i]));
  }
  return new_list;
}

void * blist_reduce(Blist_ * list, void * ( * func)(void * arg1, void * arg2)) {
    void * reduced = list -> values[0];
    for (int i = 0; i < list->list_len - 1; i++) {
        reduced = func(reduced, list->values[i + 1]);
    }
    return (int*)reduced;
}

Blist_* blist_combine(Blist_* list1, Blist_* list2){
  Blist_ * new_list = blist_init();

  for(int i=0; i<list1->list_len; i++){
    blist_append(new_list, list1->values[i]);
  }
  for(int i=0; i<list2->list_len; i++){
    blist_append(new_list, list2->values[i]);
  }
  return new_list;
}

void* blist_find(Blist_ * list, int( * func)(void * arg)) {

  for (int i = 0; i < list -> list_len; i++) {

    if (func(list->values[i]) == 0)
      return list -> values[i];
  }

  return NULL;
}

Blist_* blist_fill(Blist_ * list, void* item) {

  for (int i = 0; i < list -> list_len; i++) {
    list -> values[i]=item;
  }

  return list;
}

int blist_every(Blist_ * list, int( * func)(void * arg)) {

  for (int i = 0; i < list -> list_len; i++) {
    if (func(list->values[i]) == 1)
      return 1;
  }

  return 0;
}

int blist_some(Blist_ * list, int( * func)(void * arg)) {

  for (int i = 0; i < list -> list_len; i++) {
    if (func(list->values[i]) == 0)
      return 0;
  }

  return 1;
}

int blist_last_index_of(Blist_ * list, void * item) {
  for (int i = list->list_len-1; i >= 0; i++) {
    if (item == list->values[i])
      return i;
  }

  return -1;
}

Blist_* blist_reverse(Blist_* list){
  Blist_* temp_list = blist_init();
  for (int i = list->list_len-1; i >= 0; i++) {
    blist_append(temp_list, list->values[i]);
  }
  list = temp_list;
  blist_clearall(temp_list);
  return list;
}