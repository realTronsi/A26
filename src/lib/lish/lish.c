#include "lish.h"

char* lish_delete(char* str, int index, ...)
{

  va_list args;

  va_start(args, index);

  for (int i = 1; i < index; i++){
    int index_ = va_arg(args, int)-(i-1); //offset for each deletion

    for (int l = index_; l < sizeof(str)/sizeof(str[0]); l++){
      str[l] = str[l+1];
    }
    str = realloc(str, sizeof(*str));
  }

  va_end(args);

  return str;
}

