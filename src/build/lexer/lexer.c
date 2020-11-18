#include "lexer.h"

//init
Lexer_* lexer_init(char* source){
  Lexer_* lexer = calloc(1, sizeof(lexer)*2);
  lexer->source = source;
  lexer->line = 1;
  lexer->index = 0;
  lexer->curr_char = lexer->source[lexer->index];
  lexer->Extra = calloc(1,sizeof(*lexer->Extra)*2);
  lexer->Extra->index_number = -1;
  lexer->Extra->found_string = -1;

  return lexer;
}

//next char
void next_char(Lexer_* lexer){
  if(lexer->curr_char != '\0' && lexer->index<strlen(lexer->source))
  {
    lexer->index++;
    lexer->curr_char = lexer->source[lexer->index];
  }
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

char* convert_to_str(char char_)
{
  char* str = calloc(2,sizeof(*str)*2);
  str[0] = char_;
  str[1] = '\0';
  return str;
}

char* get_number(Lexer_* lexer)
{
  char* number = calloc(1,sizeof(*number)*2);
  do {
    char* curr = convert_to_str(lexer->curr_char);

    number = realloc(
      number,
      (strlen(number)+strlen(curr)+1)*sizeof(*number)*2
    );
    strcat(number,curr);

    next_char(lexer);
  } while(isdigit(lexer->curr_char));

  return number; // should return the number :D
  // lets try it
}

char* get_value(Lexer_* lexer)
{
  char* str = calloc(1,sizeof(*str));
  do {
    if(lexer->curr_char == '\n' || lexer->curr_char == ' ' || lexer->curr_char == '\t') break;
    char* curr = convert_to_str(lexer->curr_char);

    str = realloc(
      str,
      (strlen(str)+strlen(curr)+1)*sizeof(*str)*2
    );
    strcat(str,curr);

    next_char(lexer);
  } while(1);

  next_char(lexer);

  return str; // should return the number :D
  // lets try it
}

char* get_str(Lexer_* lexer)
{
  char* str = calloc(1,sizeof(*str));
  while(lexer->curr_char != '"')
  {
    char* curr = convert_to_str(lexer->curr_char);

    str = realloc(
      str,
      (strlen(str)+strlen(curr)+1)*sizeof(*str)*2
    );
    strcat(str,curr);
    
    next_char(lexer);
  }

  return str;
}

char peek(Lexer_* lexer, int offset)
{  
  int index = lexer->index; //pseudo index
  do {
    if(lexer->source[index]!=' '&&lexer->source[index]!='\t'){
      offset--;
    }
    index++;
  } while(offset>0);

  index++;

  if(!((index) > strlen(lexer->source)))
    return lexer->source[index];

  return '\0';
}

//lex
Token_* next_token(Lexer_* lexer){
  do {
      // skip whitespace
      top:
      if(lexer->curr_char == ' ' || lexer->curr_char == '\t')
        skip_space(lexer);
      
      if(isdigit(lexer->curr_char))
      {
        return token_init(get_number(lexer), NUM); // there we go
        break;
      }
      
    switch(lexer->curr_char){
      case 'p': {
        if(peek(lexer, 1)=='['){
          // we know that its either p[ or p [
          if(lexer->source[lexer->index+1]==' '||lexer->source[lexer->index+1]=='\t'){
            fprintf(stderr, "Unidentified token `p` at line: %d", lexer->line);
            exit(EXIT_FAILURE);
          }
          
          return tokenize(lexer, "p", P_REG);break;
        }
        return tokenize(lexer, "p", P_REG);break;
      }
      case '@':return tokenize(lexer,"@",GLB_REG);break;
      //case 'd':return tokenize(lexer,"d",D_REG); // added this.
      case '{':return tokenize(lexer,"{",L_BR);break;
      case '}':return tokenize(lexer,"}",R_BR);break;
      case '[':return tokenize(lexer,"[",L_BK);break;
      case ']':return tokenize(lexer,"]",R_BK);break;
      case '$':return tokenize(lexer,"$",REF);break;
      case ',':return tokenize(lexer,",",comma);break;
      case '#':return tokenize(lexer,"#",UD);break;
      case '\n': {
        lexer->line++;
        next_char(lexer);goto top;
      }
      case '"':
      {
        next_char(lexer);
        return tokenize(lexer,get_str(lexer),STR);
        break;
      }
      default: break; 
    }
    if(lexer->curr_char == '\0'){
      break;
    }

    //if(isalnum(lexer->curr_char)) // hmm
    //{
    //  char* value = get_value(lexer);
    //  return token_init(value, UD_VAL);
    //}

    //attnetion, commenting out the get_value did not work which means probably contents of get_str is wrong maybe
    
    next_char(lexer);
  } while (1);

  return token_init("\0", Eof);
}