#include "token.h"

Token_* token_init(char* value, int type){
  Token_* token = calloc(1, sizeof(*token));
  token->val = value;

  token->type = type;

  return token;
}
