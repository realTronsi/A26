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
              blist_append(tree->p_reg_values,tree->p_reg_values->values[atoi(parser->curr_token->val)]);
              parse_token(parser, NUM);
              parse_token(parser, R_BK);

              if(parser->curr_token->type == R_BR) goto end;
              goto redo;
            } else {
              fprintf(stderr,"\nUnexpected token `%s`\n\t↳ %s:%d",parser->curr_token->val,parser->lexer->filename, parser->lexer->line);
              tree->errors = 0;
            }
          } else {
            fprintf(stderr, "\nCannot reference entire register inside itself\n\t↳ %s:%d\n", parser->lexer->filename, parser->lexer->line);
            tree->errors = 0;
          }
        }
        default: {
          fprintf(stderr, "\nUnidentified reference `%s`\n\t↳ %s:%d\n",parser->curr_token->val, parser->lexer->filename, parser->lexer->line);
          tree->errors = 0;
        }
      }
    }
    case STR:
    {
      while(parser->curr_token->type == STR)
      {
        //parse_string(parser, tree);
        blist_append(tree->p_reg_values, parser->curr_token->val);
        parse_token(parser, STR);
      }

      if(parser->curr_token->type == R_BR) goto end;
      goto redo;
    }
    case NUM:
    {
      while(parser->curr_token->type == NUM)
      {
        blist_append(tree->p_reg_values,parser->curr_token->val);
        parse_token(parser, NUM);
      }
      if(parser->curr_token->type == R_BR) goto end;
      goto redo;
    }
    default:
    {
      if(parser->curr_token->type == R_BR) goto end;
      fprintf(stderr,"\nInvalid syntax `%s\n\t↳ %s:%d\n",parser->curr_token->val,parser->lexer->filename,parser->lexer->line);
      tree->errors = 0;
    }
  }

  end:
  parse_token(parser, R_BR);
  return tree;
}