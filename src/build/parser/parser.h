#ifndef PARSER
#define PARSER
#include "../lexer/token/token.h"
#include "../lexer/lexer.h"
#include "AST/syn_tree.h"
#include <stdio.h>

#include "REG/GLB/glb.h"

typedef struct Parser {
    Token_* curr_token;
    Token_* prev_token;
    Lexer_* lexer;
} Parser_;

Parser_* parser_init(Lexer_* lexer);
void parse_next_token(Parser_* parser, int expected);
SyntaxTree_* parse(Parser_* parser);

#endif