#include "parser.h"

Parser_* parser_init(Lexer_* lexer)
{
    Parser_* parser = calloc(1,sizeof(*parser)*2);
    
    parser->lexer = lexer;
    parser->curr_token = next_token(parser->lexer);
    parser->prev_token =  parser->curr_token;
    return parser;
}

void parse_token(Parser_* parser, int expected){
    if(parser->curr_token->type != expected){
      //printf("CURRENT: %c TOKEN: %d CURRENT: %c", parser->lexer->curr_char, parser->curr_token->type, parser->lexer->curr_char);
      printf("PREV: %d, CURR: %d, EXPECTED: %d", parser->prev_token->type, parser->curr_token->type, expected);
        fprintf(stderr, "\nUnexpected token '%s' on line: %d\n",parser->curr_token->val, parser->lexer->line);
        exit(EXIT_FAILURE);
    }
    parser->prev_token = parser->curr_token;
    parser->curr_token = next_token(parser->lexer);
}

SyntaxTree_* parse_curr_token(Parser_* parser){
  switch(parser->curr_token->type){
    case P_REG: return parse_p_reg(parser);
    case GLB_REG: return parse_glb_reg(parser);
    default: {
      printf("%d\n",parser->curr_token->type);
      fprintf(stderr, "\nUncaught value `%s` on line %d",parser->curr_token->val, parser->lexer->line);
      exit(EXIT_FAILURE);
    }
  }
}

SyntaxTree_* start_parsing(Parser_* parser)
{
  SyntaxTree_* main_tree = calloc(1,sizeof(*main_tree)*2);
  main_tree = parse_curr_token(parser);

  main_tree->l_of_trees++;
  main_tree->trees[0] = main_tree;

  // ^ you are correct, we can't enforce any tree token type. Which is why we do:
  // SyntaxTree_* main_tree = calloc(1,sizeof(*main_tree));
  // main_tree = parse_curr_token.
  // ^ main_tree is like any other tree setup throughout the parser. The only difference is that main_tree stores the array "trees" which stores every other tree
  while(parser->curr_token->type != Eof) {
    // this is where we start parsing the rest of the file!
    SyntaxTree_* tree = parse_curr_token(parser);

    if(tree)
    {
      main_tree->l_of_trees++;
      main_tree->trees = realloc(
        main_tree->trees,
        (main_tree->l_of_trees+1)*sizeof(*main_tree->trees)*2
      );
      main_tree->trees[main_tree->l_of_trees-1] = tree;
    }

    // then we append. This while loop is how we constantly parse the file until Eof(\0) is encountered
    // I will teach you how to append the tree to the trees array in main_tree. For now, just know that this while loop is needed to continue to parse the rest of the file:D
  }

  // we then return main_tree so that I can use the information picked up throughout the program in the compiler
  return main_tree;
}

SyntaxTree_* parse(Parser_* parser){
  return start_parsing(parser);
}