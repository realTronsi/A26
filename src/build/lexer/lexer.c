#include "lexer.h"

char special_chars[2] = {
  '{', '}'
};

//init
Lexer_* lexer_init(char* source){
  Lexer_* lexer = calloc(1, sizeof(lexer));
  lexer->source = source;
  lexer->index = 0;
  lexer->curr_char = lexer->source[lexer->index];

  return lexer;
}

//next char
Lexer_* next_char(Lexer_* lexer){
  if(lexer->curr_char != '\0' && lexer->index<strlen(lexer->source))
  {
    lexer->index++;
    lexer->curr_char = lexer->source[lexer->index];

    if(lexer->curr_char == '\n')
      lexer->line++;
  }

  return lexer;
}

//skip space
void skip_space(Lexer_* lexer){
  do {
    next_char(lexer);
  } while(lexer->curr_char == ' ' || lexer->curr_char == '\t');
}

Token_* tokenize(Lexer_* lexer, char* val, int token_id)
{
    next_char(lexer);
    return token_init(val, token_id);
}

//lex
Token_* next_token(Lexer_* lexer){
  do {
      // skip whitespace
      top:
      if(lexer->curr_char == ' ' || lexer->curr_char == '\t')
        skip_space(lexer);
        
    switch(lexer->curr_char){
      case 'p':return tokenize(lexer,"p",P_REG);
      case '@':return tokenize(lexer,"@",GLB_REG);
      case '{':return tokenize(lexer,"{",L_BR);
      case '}':return tokenize(lexer,"}",R_BR);
      case ',':return tokenize(lexer,",",comma);
      case '\n': next_char(lexer);goto top;
      default: break; 
    }
    if(lexer->curr_char == '\0'){
      break;
    }
    next_char(lexer);
  } while (1);

  return token_init("\0", EOF);
}