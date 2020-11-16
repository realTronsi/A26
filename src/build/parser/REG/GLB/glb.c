#include "glb.h"

SyntaxTree_* parse_glb_reg(Parser_* parser){
  SyntaxTree_* tree = syn_tree_init(TREE_GLB_REG);
  parse_next_token(parser, L_BR);

  do {
    parse_next_token(parser, -1);

    if(parser->curr_token->type == EOF){
      fprintf(stderr, "SyntaxError: Unresolved '{' on line: %d", parser->lexer->line);
    }
  } while(parser->curr_token->type != R_BR);

  return tree;
}