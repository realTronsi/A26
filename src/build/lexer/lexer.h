#ifndef LEXER
#define LEXER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token/token.h"

typedef struct Lexer {
  char* source;
  char* filename;
  char curr_char;
  int index;
  int line;
  int new_line_char;

  struct {
    int index_number;
    int found_string;
  } *Extra;
} Lexer_;

Lexer_* lexer_init(char* source, char* filename);
Token_* next_token(Lexer_* lexer);
char* convert_to_str(char char_);

#endif