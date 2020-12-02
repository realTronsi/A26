#include "parser.h"

Parser_* parser_init(Lexer_* lexer)
{
    Parser_* parser = calloc(1,sizeof(*parser));
    
    parser->lexer = lexer;
    parser->curr_token = next_token(parser->lexer);
    parser->prev_token =  parser->curr_token;
    return parser;
}

void parse_token(Parser_* parser, int expected){
    if(parser->curr_token->type != expected){
      fprintf(stderr, "\nUnexpected token '%s'\n\t↳ %s:%d\n",parser->curr_token->val,parser->lexer->filename,parser->lexer->line);
      Exit();
    }
    parser->prev_token = parser->curr_token;
    parser->curr_token = next_token(parser->lexer);
}

SyntaxTree_* parse_curr_token(Parser_* parser){
  switch(parser->curr_token->type){
    case P_REG: return parse_p_reg(parser);
    case GLB_REG: return parse_glb_reg(parser);
    case D_Reg: return parse_d_reg(parser);
    //case D_REG: return parse_d_reg(parser);
    default: {
      fprintf(stderr, "\nUncaught value `%s`\n\t↳ %s:%d\n",parser->curr_token->val, parser->lexer->filename,parser->lexer->line);
      Exit(); // this will output "Compilation Error" via cmpler.s
      //exit(EXIT_FAILURE);
    }
  }
  return (void*)0; // we should never get here, but this is needed to avoid warnings
}

SyntaxTree_* start_parsing(Parser_* parser)
{
  SyntaxTree_* main_tree = calloc(1,sizeof(*main_tree));
  main_tree = parse_curr_token(parser);

  main_tree->l_of_trees++;
  main_tree->trees[0] = main_tree;

  while(parser->curr_token->type != Eof) {
    SyntaxTree_* tree = parse_curr_token(parser);

    if(tree)
    {
      main_tree->l_of_trees++;
      main_tree->trees = realloc(
        main_tree->trees,
        (main_tree->l_of_trees+1)*sizeof(*main_tree->trees)
      );
      main_tree->trees[main_tree->l_of_trees-1] = tree;
    }
  }
  
  return main_tree;
}

SyntaxTree_* parse(Parser_* parser){
  return start_parsing(parser);
}