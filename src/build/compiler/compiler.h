#ifndef COMPILER
#define COMPILER
#include <stdio.h>
#include <stdlib.h>
#include "../parser/AST/syn_tree.h"
#include "compile_p_reg.h"

SyntaxTree_* compile(SyntaxTree_* tree);
void Exit();

#endif