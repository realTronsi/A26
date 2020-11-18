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
          parse_token(parser, P_REG); // I think what I did is pretty self explanatory.
          // I added a check to see if our current token is [ and if it is then we continue onward
          // then, I appended the token value(which should be the index), into the p_references_indexes blist.
          if(parser->curr_token->type == L_BK){
            parse_token(parser,L_BK); // [
            // I added this just to be safe. Just in case the user puts something else other than a index number..
            // you can delete it if you feel as if it is useless!
            if(parser->curr_token->type == NUM){
              blist_append(tree->p_references_indexes,parser->curr_token->val);
              parse_token(parser, NUM);
            }
            else
            {
              fprintf(stderr,"\nExpecting index number.\n");
              exit(EXIT_FAILURE);
            }
            parse_token(parser,  R_BK); // ]
          }
          else
          {
            fprintf(stderr,"\nExpecting index number.\n");
            exit(EXIT_FAILURE);
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