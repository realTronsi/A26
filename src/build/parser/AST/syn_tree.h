#ifndef AST
#define AST

#include <stdio.h>
#include "../../../lib/blist/blist.h"
#include "../../lexer/token/token.h"

typedef struct SyntaxTree {
  enum {
    TREE_UD, // redefinition, just use Tree before them to keep from repitition
    TREE_P_REG,
    TREE_GLB_REG
  } TokenType;

  struct SyntaxTree** trees;
  size_t l_of_trees;

  // GLOBAL
  /*
    ADDED: p_references, d_references

    p_references:
      references to indexes in the p register to print.
    d_references:
      references to indexes in the d register to work with
  */
  int global_exists;
  int global_return;
  Blist_* p_references_indexes; // it will be a number. Have _indexes at the end makes it easier for us to decipher that we need to type cast all indexes of the blist as a integer
  Blist_* d_references_indexes; // ^

  // REGISTER P (I/O)
  Blist_* p_reg;
} SyntaxTree_;

SyntaxTree_* syn_tree_init();

#endif