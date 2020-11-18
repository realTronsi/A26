#include "p_reg.h"

SyntaxTree_* parse_p_reg(Parser_* parser)
{
  SyntaxTree_* tree = syn_tree_init(TREE_P_REG);
  parse_token(parser, P_REG);
  parse_token(parser, L_BR);
  
  while(parser->curr_token->type == STR)
  {
    blist_append(tree->p_reg, parser->curr_token->val);
    parse_token(parser, STR);
  }
  parse_token(parser, R_BR);
  
  for(int i = 0; i < tree->p_reg->list_len; i++)
    printf("%s\n",tree->p_reg->values[i]);
  return tree;
}