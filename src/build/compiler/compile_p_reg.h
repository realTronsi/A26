#ifndef c_p_r
#define c_p_r

#include "compiler.h"
#include <string.h>
SyntaxTree_* create_p_register(SyntaxTree_* tree, FILE* file);
SyntaxTree_* compile_p_reg(SyntaxTree_* tree, FILE* file);
SyntaxTree_* rodata_p_reg(SyntaxTree_* tree, FILE* file);

#endif