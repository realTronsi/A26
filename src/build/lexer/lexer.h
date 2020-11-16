#ifndef LEXER
#define LEXER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token/token.h"

typedef struct Lexer {
  char* source;
  char curr_char;
  int index;
  int line;
} Lexer_;

Lexer_* lexer_init(char* source);
Token_* next_token(Lexer_* lexer);

#endif