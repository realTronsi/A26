#ifndef COMPILER
#define COMPILER
#include <stdio.h>
#include <stdlib.h>
#include "../parser/AST/syn_tree.h"

SyntaxTree_* compile(SyntaxTree_* tree);

#endif