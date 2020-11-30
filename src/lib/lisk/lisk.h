#ifndef LISK
#define LISK
#include <stdlib.h>

typedef struct Lisk {
  void** values;
  char** keys;
  size_t n_items;
} Lisk_;

Lisk_* lisk_init();

Lisk_* lisk_set(Lisk_* lisk, void* item, char* key);
Lisk_* lisk_get(Lisk_* lisk, char* key);
Lisk_* lisk_delete(Lisk_* lisk, char* key);

Lisk_* lisk_addall(Lisk_* lisk, void** items, char** keys);
Lisk_* lisk_add(Lisk_* lisk, void* item, char* key);
//adds all to lisk

#endif