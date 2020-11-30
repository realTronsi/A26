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
          fprintf(stderr,"\nUnexpected `%s`\n\t↳ %s:%d\n",parser->curr_token->val,parser->lexer->filename,parser->lexer->line);
          tree->errors = 0;
        }
      }

      if(parser->curr_token->type == L_BR) goto end;
      goto redo;
    }
    case UD:
    {
      parse_token(parser, UD);
      if(parser->curr_token->type == UD_VAL)
      {
        parse_token(parser,UD_VAL);
        if(parser->curr_token->type == DASH){
          parse_token(parser, DASH);

          if(parser->curr_token->type == F_AR) // we don't know that the token would be a >, so we have to check. It could very well be that the user forgot to put a >..
          {
            parse_token(parser, F_AR);
            printf("%d",parser->curr_token->type);
            //just a question, u know how like for example UD is inside an enum in the token struct, my question is how are we able to just use it freely like this? Are all elements inside an enum global? Since the enum is inside a struct, so shouldn't we have to do like token->enum->UD instead or something like that??

            // ===MOCA===
            // You simply do not call an enum upon using the keyword enum. The enum is a part of the struct, and we initialize a new instance of the struct(the variable parser), which we can then use to refer to the name of the enum.

            //ALso -> is used for pointer structs, why is our structs a pointer and not normal, bc in normal we use blah.property and I always thought C uses -> for such but it actually only uses -> when the struct is a pointer, so why is our struct a pointer???

            // ===MOCA==
            // pointers keep the information. Not having it as a pointer means the information cannot carry over to the next function. Having the struct as a pointer means we can keep the information stored throughout each function the struct is used in.
          } else {
            fprintf(stderr,"\nExpecting `->` for variable assignment. Missing '>'\n\t↳ %s:%d\n",parser->lexer->filename,parser->lexer->line);
          }
        }
      } else {
        fprintf(stderr,"\nExpecting a User-Defined(UD) variable name\n\t↳ %s:%d\n",parser->lexer->filename,parser->lexer->line);
        tree->errors = 0;
      }
    }
    case GLB_REG: {
      fprintf(stderr, "\nSyntaxError: Redefintion of global register\n\t↳ %s:%d\n",parser->lexer->filename, parser->lexer->line);
      tree->errors = 0;
    }
    default: break;
  }

  end:
  parse_token(parser, R_BR);
  
  return tree;
}