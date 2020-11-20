#include "glb_reg.h"

SyntaxTree_* parse_glb_reg(Parser_* parser){
  SyntaxTree_* tree = syn_tree_init(TREE_GLB_REG);

  parse_token(parser, GLB_REG);
  parse_token(parser, L_BR);

  redo:
  switch(parser->curr_token->type){
    case REF: {
      parse_token(parser, REF);

      switch(parser->curr_token->type)
      {
        case P_REG:
        {
          parse_token(parser, P_REG); 
          if(parser->curr_token->type == L_BK){
            parse_token(parser,L_BK); 
            if(parser->curr_token->type == NUM){
              blist_append(tree->p_references_indexes,parser->curr_token->val);
              parse_token(parser, NUM);
            }
            else
            {
              if(parser->curr_token->type == R_BK) blist_append(tree->p_references_indexes,"all");
            }
            parse_token(parser,  R_BK); // ]
          }
          else
          {
            blist_append(tree->p_references_indexes,"all");
          }
          
          if(parser->curr_token->type == R_BR) goto end;
          goto redo;
        }
        default:
        {
          fprintf(stderr,"\nError");
          exit(EXIT_FAILURE);
        }
      }

      if(parser->curr_token->type == L_BR) goto end;
      goto redo;
    }
    case UD:
    {
      fprintf(stderr,"\nCannot define variables inside global register\n");
      exit(EXIT_FAILURE);

      //why cant we define vars inside glb register again? anyways sorry I didnt code today I haven't been in the mood, I've just been sick and in pain so I will probably code tmr
    }
    case GLB_REG: {
      fprintf(stderr, "SyntaxError: Redefintion of global register at line %d", parser->lexer->line);
      exit(EXIT_FAILURE);
    }
    default: break;
  }

  end:
  parse_token(parser, R_BR);
  
  return tree;
}