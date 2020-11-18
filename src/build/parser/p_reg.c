#include "p_reg.h"

SyntaxTree_* parse_p_reg(Parser_* parser)
{
  SyntaxTree_* tree = syn_tree_init(TREE_P_REG);
  parse_token(parser, P_REG);
  parse_token(parser, L_BR);
  parse_token(parser, STR);

  parse_token(parser,  R_BR);
  printf("what");
  return tree;
}