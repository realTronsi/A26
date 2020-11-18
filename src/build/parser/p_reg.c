#include "p_reg.h"

SyntaxTree_* parse_p_reg(Parser_* parser)
{
  SyntaxTree_* tree = syn_tree_init(TREE_P_REG);
  parse_token(parser, P_REG);
  parse_token(parser, L_BR);
  
  redo:
  switch(parser->curr_token->type)
  {
    case STR:
    {
      while(parser->curr_token->type == STR)
      {
        blist_append(tree->p_reg, parser->curr_token->val);
        parse_token(parser, STR);
      }

      if(parser->curr_token->type == R_BR) goto end;
      goto redo;
    }
    case NUM:
    {
      while(parser->curr_token->type == NUM)
      {
        blist_append(tree->p_reg,parser->curr_token->val);
        parse_token(parser, NUM);
      }
      if(parser->curr_token->type == R_BR) goto end;
      goto redo;
    }
    default:
    {
      fprintf(stderr,"\nInvalid syntax `%s` on line %d\n",parser->curr_token->val, parser->lexer->line);
      exit(EXIT_FAILURE);
    }
  }

  end:
  parse_token(parser, R_BR);
  return tree;
}