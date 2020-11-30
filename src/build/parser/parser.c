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
    //case D_REG: return parse_d_reg(parser);
    default: {
      fprintf(stderr, "\nUncaught value `%s`\n\t↳ %s:%d\n",parser->curr_token->val, parser->lexer->filename,parser->lexer->line);
      Exit();
      //exit(EXIT_FAILURE);
    }
  }
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

SyntaxTree_* parse_string(Parser_* parser, SyntaxTree_* tree){

  if(parser->curr_token->type == STR){
    char* string = parser->curr_token->val;
    for(size_t i = 0; i < strlen(string); i++){
      if(string[i]=='\\'){
        tree->am++;
        tree->ec_indexes = realloc(
          tree->ec_indexes,
          (tree->am+1)*sizeof(*tree->ec_indexes)
        );
        tree->ec_indexes[tree->am-1] = (int*)i;

        i++;
        if(string[i]=='n'){
          string = lish_delete(string, i, i-1);
          tree->escape_chars = realloc(tree->escape_chars, (tree->am+1)*sizeof(*tree->escape_chars));
          tree->escape_chars[tree->am-1] = "\n";
          //if(!(tree->strings->n_items > 0)) tree->strings = lisk_add(tree->strings,(void*)blist_append(tree->escape_chars, "\n"),string);
          //else {
            //tree->strings = lisk_set(tree->strings,(void*)blist_append(tree->escape_chars, "\n"),string);
          //}
        } else if(string[i]=='\\'){
          string = lish_delete(string, i-1);
        } else if(string[i]=='\''){
          string = lish_delete(string, i-1);
        } else if(string[i]=='\"'){
          string = lish_delete(string, i-1);
        }
      }
    }

    if(tree->am > 0) {
      blist_append(tree->strings,string);
      goto end;
    } else {
      blist_append(tree->p_reg_values,string);
      goto end;
    }
    
    end:
    return tree;
  }
  fprintf(stderr, "\nUnparsable string\n\t↳ %s:%d", parser->lexer->filename,parser->lexer->line);
  exit(EXIT_FAILURE);
}

SyntaxTree_* parse(Parser_* parser){
  return start_parsing(parser);
}