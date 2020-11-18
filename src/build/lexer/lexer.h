#ifndef LEXER
#define LEXER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token/token.h"

typedef struct Lexer {
  char* source;
  char curr_char;
  int index;
  int line;

  struct {
    int index_number;
    int found_string;
  } *Extra;
} Lexer_;

Lexer_* lexer_init(char* source);
Token_* next_token(Lexer_* lexer);

#endif