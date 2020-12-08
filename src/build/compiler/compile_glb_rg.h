#ifndef c_g_r
#define c_g_r

#include "compiler.h"
SyntaxTree_* compile_glb_reg(SyntaxTree_* tree, FILE* file);
SyntaxTree_* rodata_glb_reg(SyntaxTree_* tree, int p_reg_index,FILE* file,SyntaxTree_* all);

#endif