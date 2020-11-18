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
  int global_exists;
  int global_return;

  // REGISTER P (I/O)
  Blist_* p_reg;
} SyntaxTree_;

SyntaxTree_* syn_tree_init();

#endif