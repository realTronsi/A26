#ifndef TOKEN
#define TOKEN

#include <stdio.h>
#include <stdlib.h>

typedef struct Token {
  enum {
    UD,
    P_REG, //p
    GLB_REG, //@
    D_REG, // d
    L_BR, // {
    R_BR, // }
    L_BK, // [
    R_BK, // ]
    REF, // $
    UD_VAL, // value after #
    NUM, //number
    STR,
    comma,
    Eof,
  } type;
  char* val;
} Token_;

Token_* token_init(char* value, int type);

#endif