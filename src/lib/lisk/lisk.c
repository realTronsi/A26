#include "lisk.h"
#include <stdio.h>

Lisk_* lisk_init(){
  Lisk_* lisk = calloc(1, sizeof(*lisk));

  lisk->n_items = 0;
  lisk->values = calloc(1, sizeof(*lisk->values));
  lisk->keys = calloc(1, sizeof(*lisk->keys));

  return lisk;
}

int indexOfKey(Lisk_* lisk, char* key){
  for(int i=0; i<lisk->n_items; i++){
    if(lisk->keys[i]==key)
      return i;
  }
  return -1;
}

Lisk_* lisk_get(Lisk_* lisk, char* key){
  int index = indexOfKey(lisk, key);
  if(index == -1){
    fprintf(stderr, "\n\tKey goes not exist(%s)", key);
    exit(EXIT_FAILURE);
  }
  return lisk->values[index];
}

Lisk_* lisk_delete(Lisk_* lisk, char* key){
  int index = indexOfKey(lisk, key);
  if(index == -1){
    fprintf(stderr, "\n\tKey goes not exist(%s)", key);
    exit(EXIT_FAILURE);
  }

  for (int i = index; i < lisk -> n_items; i++) {
    lisk->values[i] = lisk->values[i + 1];
  }
  for (int i = index; i < lisk -> n_items; i++) {
    lisk->keys[i] = lisk->keys[i + 1];
  }

  lisk->n_items--;
  lisk->values = realloc(lisk->values,(lisk->n_items+1)*sizeof(*lisk->values));
  lisk->keys = realloc(lisk->keys,(lisk->n_items+1)* sizeof(*lisk->keys));

  return lisk;
}

Lisk_* lisk_set(Lisk_* lisk, void* item, char* key){
  int index = indexOfKey(lisk, key);
  if(index != -1){
    lisk->values[index] = item;
    return lisk;
  } else {
    lisk->n_items++;

    lisk->values = realloc(lisk->values, (lisk->n_items+1)*sizeof(*lisk->values));
    lisk->keys = realloc(lisk->keys, (lisk->n_items+1)*sizeof(*lisk->keys));

    lisk->values[lisk->n_items-1]=item;
    lisk->keys[lisk->n_items-1]=key;

    return lisk;
  }
}

Lisk_* lisk_addall(Lisk_* lisk, void** items, char** keys){
  int items_length = sizeof(items)/sizeof(items[0]);
  for(int i=0; i<items_length; i++){
    lisk_set(lisk, items[i], keys[i]);
  }
  return lisk;
}

Lisk_* lisk_add(Lisk_* lisk, void* item, char* key)
{
  lisk->n_items++;
  lisk->keys = realloc(
    lisk->keys,
    (lisk->n_items+1)*sizeof(*lisk->keys)
  );
  lisk->values = realloc(
    lisk->values,
    (lisk->n_items+1)*sizeof(*lisk->values)
  );

  lisk->keys[lisk->n_items-1] = key;
  lisk->values[lisk->n_items-1] = item;

  return lisk;
}