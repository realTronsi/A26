#include "compiler.h"
#include <string.h>

SyntaxTree_* create_p_register(SyntaxTree_* tree, FILE* file)
{
  fprintf(file,"\n\tglobal p_reg");
  return tree;
}
SyntaxTree_* compile_p_reg(SyntaxTree_* tree, FILE* file)
{
  // we will get to this
  fprintf(file,"\np_reg:\n");

  for(int i = 0; i < tree->p_reg->list_len; i++)
  {
    fprintf(file,"\n\tmov ecx, p_msg_%d\n\tsys_call\n",i+1);
  }
  fprintf(file,"\n\tmov eax, 1\n\tsys_call");
  return tree;
}
SyntaxTree_* rodata_p_reg(SyntaxTree_* tree, FILE* file)
{
  fprintf(file,"\nsection .rodata\n");
  fprintf(file,"\n\t; P REGISTER");
  for(int i = 0; i < tree->p_reg->list_len; i++)
  {
    fprintf(file,"\n\tp_msg_%d db \"%s\"",i+1,(char*)tree->p_reg->values[i]);
  }
  return tree;
}

SyntaxTree_* create_glb_register(SyntaxTree_* tree, FILE* file)
{
  fprintf(file,"\n\tglobal glb_reg");
  return tree;
}
SyntaxTree_* compile_glb_reg(SyntaxTree_* tree, FILE* file)
{
  // we will get to this
  fprintf(file,"\nglb_reg:\n\tmov eax, 1\n\tmov ebx, 0\n\tsys_call");
  return tree;
}
SyntaxTree_* rodata_glb_reg(SyntaxTree_* tree, int p_reg_index,FILE* file)
{
  for(int i = 0; i < tree->p_references_indexes->list_len; i++)
  {
    if(strcmp(tree->p_references_indexes->values[i],"all")==0)
    {
      for(int i = 0; i < tree->trees[p_reg_index]->p_reg->list_len; i++)
      {
        fprintf(file,"\n\tmov ecx, p_msg_%d\n\tmov edx, %ld\n\tmov eax, 4\n\tmov ebx, 1\n\tsys_call\n",i+1,strlen(tree->trees[p_reg_index]->p_reg->values[i]));
      }
    }
    else
    {
      if(!(atoi(tree->p_references_indexes->values[i]) > tree->trees[p_reg_index]->p_reg->list_len))
      {
        fprintf(file,"\n\tmov ecx, p_msg_%d\n\tmov edx, %ld\n\tmov eax, 4\n\tmov ebx, 1\n\tsys_call\n",atoi(tree->p_references_indexes->values[i])+1,strlen(tree->trees[p_reg_index]->p_reg->values[atoi(tree->p_references_indexes->values[i])]));
      }else
      {
        fprintf(file,"\n\tcall err");
      }
    }
  }
  return tree;
}

SyntaxTree_* compile(SyntaxTree_* tree)
{
  FILE* file = fopen("cmpler.s","wb");

  if(file)
  {

    /*
      Tronsi -
        I already know what you're gonna ask: "Why are you doing so many for loops".

        Long story short, I like sectionizing my assembly code so .text section first, all the global functions second, then .rodata / .bss sections third..
        So, in order to do that, we need to split it up into multiple different sections of for loops. But in the end, it won't really matter since we're compiling the assembly
    */

    // section .text
    fprintf(file,"section .text\n\tglobal err\n\tglobal _start\n\t%%define sys_call int 0x80");
    int p_reg_index = -1;
    for(int i = 0; i < tree->l_of_trees; i++)
    {
      switch(tree->trees[i]->TokenType)
      {
        case TREE_P_REG:
        {
          p_reg_index = i;
          create_p_register(tree,file);break;
        }
        case TREE_GLB_REG: create_glb_register(tree,file);break;
        default: 
        {
          fprintf(stderr,"\nCompilation Error\n");
          exit(EXIT_FAILURE);
        }
      }
    }

    // Actual code
    fprintf(file,"\nerr:\n\tmov ecx, msg\n\tmov edx, len\n\tmov eax, 4\n\tmov ebx, 1\n\tsys_call\n\n\tmov eax, 1\n\tmov ebx, 1\n\tsys_call");
    for(int i = 0; i < tree->l_of_trees; i++)
    {
      switch(tree->trees[i]->TokenType)
      {
        case TREE_P_REG: compile_p_reg(tree->trees[i],file);break;
        case TREE_GLB_REG: compile_glb_reg(tree->trees[i],file);break;
        default:
        {
          fprintf(stderr,"\nCompilation Error\n");
          exit(EXIT_FAILURE);
        }
      }
    }

    fprintf(file,"\nsection .data ; storing all compiler messages\n\tmsg db \"Compilation Error\",0xa\n\tlen equ $ - msg");

    // main function(_start)
    fprintf(file,"\n_start:\n");

    // section .rodata
    for(int i = 0; i < tree->l_of_trees; i++)
    {
      switch(tree->trees[i]->TokenType)
      {
        case TREE_P_REG:
        {
          fprintf(file,"\n\tmov eax, 1\n\tmov ebx, 0\n\tsys_call\n");
          rodata_p_reg(tree->trees[i], file);
          break;
        }
        case TREE_GLB_REG: 
        {
          rodata_glb_reg(tree, p_reg_index, file);break;
        }
        default:
        {
          fprintf(stderr,"\nCompilation Error\n");
          exit(EXIT_FAILURE);
        }
      }
    }

    fclose(file);
  }

  return tree;
}