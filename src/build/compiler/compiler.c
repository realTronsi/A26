#include "compiler.h"

void compile(SyntaxTree_* tree)
{
    FILE* file = fopen("cmpler.s","wb");

    if(file)
    {
        fprintf(file,"section .text\n\tglobal _start\n\t%%define sys_call int 0x80\n\n_start:\n\tmov eax, 1\n\tmov ebx, 0\n\tsys_call");
        fclose(file);
    }
}