#ifndef TOKEN
#define TOKEN

#include <stdio.h>
#include <stdlib.h>

typedef struct Token {
  enum {
    UD,
    P_REG,
    GLB_REG,
    L_BR,
    R_BR,
    comma,
    EOF,
  } type;
  char* val;
} Token_;

Token_* token_init(char* value, int type);

#endif