#include "parser.h"

Parser_* parser_init(Lexer_* lexer)
{
    Parser_* parser = calloc(1,sizeof(*parser));
    
    parser->lexer = lexer;
    parser->curr_token = next_token(parser->lexer);
    parser->prev_token = calloc(1,sizeof(*parser->prev_token));

    return parser;
}

void parse_next_token(Parser_* parser, int expected){
  parser->prev_token = parser->curr_token;
  parser->curr_token = next_token(parser->lexer);

  if(expected != -1 && parser->curr_token->type != expected){
    fprintf(stderr, "Unexpected token on line: %d", parser->lexer->line);
    exit(EXIT_FAILURE);
  }
}

SyntaxTree_* parse_curr_token(Parser_* parser){
  switch(parser->curr_token->type){
    case GLB_REG: {
      parse_glb_reg(parser);
    }
    default: {
      fprintf(stderr, "%d", parser->lexer->line);
      exit(EXIT_FAILURE);
    }
  }
}

SyntaxTree_* parse(Parser_* parser){
  SyntaxTree_* main_tree = syn_tree_init(); // we cant enforce this to be GLB since the first doesnt HAVE to be the glb since obviously it could be other registers or be newlines or macros or something
  do {
    parse_next_token(parser, -1); //for not expecting anything
  } while(parser->curr_token->type != EOF);
}