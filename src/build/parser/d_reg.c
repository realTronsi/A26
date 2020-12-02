#include "d_reg.h"

SyntaxTree_* parse_d_reg(Parser_* parser)
{
  SyntaxTree_* tree = syn_tree_init(TREE_D_REG);

  parse_token(parser,D_Reg);
  parse_token(parser,L_BR);
  parse_token(parser,R_BR);

  return tree;
}