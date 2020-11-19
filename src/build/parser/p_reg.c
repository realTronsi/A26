#include "p_reg.h"

SyntaxTree_* parse_p_reg(Parser_* parser)
{
  SyntaxTree_* tree = syn_tree_init(TREE_P_REG);
  parse_token(parser, P_REG);
  parse_token(parser, L_BR);
  
  redo:
  switch(parser->curr_token->type)
  {
    case REF: {
      parse_token(parser, REF);
      
      switch(parser->curr_token->type)
      {
        case P_REG:
        {
          // I hope ur mad
          parse_token(parser, P_REG);
          
          if(parser->curr_token->type == L_BK) { // i hope so
            parse_token(parser,L_BK);
            // for the hell of it.
            if(parser->curr_token->type == NUM)
            { 
              blist_append(tree->p_references_indexes,parser->curr_token->val);
              parse_token(parser, NUM);

              if(parser->curr_token->type == R_BR) goto end;
              goto redo;
            } else if(parser->curr_token->type == R_BK){
              blist_append(tree->d_references_indexes,0);
              parse_token(parser,R_BK);
            } else {
              fprintf(stderr,"\nUnexpected token `%s` on line %d\n",parser->curr_token->val, parser->lexer->line);
              exit(EXIT_FAILURE);
            }
          } else {
            //throw error since we're inside the p register and so we cant just loop inside forever unless you want to allow it
            fprintf(stderr,"\nExpecting `[`\n");
            exit(EXIT_FAILURE);
          }
        }
        default: {
          fprintf(stderr, "Unidentified reference %d", parser->lexer->line);
          exit(EXIT_FAILURE);
        }
      }
    }
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