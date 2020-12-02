#ifndef AST
#define AST

#include <stdio.h>
#include "../../../lib/blist/blist.h"
#include "../../../lib/lisk/lisk.h"
#include "../../lexer/token/token.h"

typedef struct SyntaxTree {
  enum {
    TREE_UD,
    TREE_P_REG,
    TREE_GLB_REG,
    TREE_D_REG
  } TokenType;

  struct SyntaxTree** trees;
  size_t l_of_trees;

  // found any error?
  int errors;

  // GLOBAL
  int global_exists;
  int global_return;
  Blist_* p_references_indexes;
  Blist_* d_references_indexes;

  // REGISTER P (I/O) values
  Blist_* p_reg_values;

  //Strings
  Blist_* strings;
  char** escape_chars;
  int** ec_indexes;
  int** locations;
  size_t am;

  size_t l_of_strs; 
  char** UD_names;
  Blist_* UD_values; // Blist stores void types might as well use it to store the UD values :D
  size_t l_of_ud_variables;
} SyntaxTree_;

SyntaxTree_* syn_tree_init();

#endif