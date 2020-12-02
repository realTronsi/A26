#ifndef PARSER
#define PARSER
#include "../lexer/token/token.h"
#include "../lexer/lexer.h"
#include "AST/syn_tree.h"
#include "../../lib/lish/lish.h"
#include <stdio.h>

typedef struct Parser {
    Token_* curr_token;
    Token_* prev_token;
    Lexer_* lexer;
} Parser_;

#include "glb_reg.h"
#include "p_reg.h"
#include "d_reg.h"

Parser_* parser_init(Lexer_* lexer);
void parse_token(Parser_* parser, int expected);
SyntaxTree_* parse(Parser_* parser);

#endif