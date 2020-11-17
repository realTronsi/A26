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
          if(parser->curr_token->type == L_BR){
            parse_token(parser, L_BR);
            parse_token(parser, NUM); //expecting number
            //now we can do syntax tree stuff to reference to it right?
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

      //if(parser->curr_token->type == R_BR) goto end;
      //goto redo;
    }
    case UD:
    {
      fprintf(stderr,"\nCannot define variables inside global register\n");
      exit(EXIT_FAILURE);
    }
    //case R_BR: goto end;break;  this might not be needed, but lets keep it just in case. Also, I added break just in case the switch statement continued.(it's happened before)
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