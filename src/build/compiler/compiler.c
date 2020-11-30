#include "compiler.h"
#include <string.h>

void Exit()
{
  FILE* file = fopen("cmpler.s","wb");

  if(file)
  {
    fprintf(file,"section .text\n\tglobal _start\n\n_start:\n\tmov ecx, msg\n\tmov edx, len\n\tmov eax, 4\n\tmov ebx, 1\n\tint 0x80\n\n\tmov eax, 1\n\tmov ebx, 1\n\tint 0x80\n\nsection .data\n\tmsg db \"Compilation Error\",0xa\n\tlen equ $ - msg\n");
    fclose(file);
    exit(EXIT_FAILURE);
  }
}

SyntaxTree_* compile(SyntaxTree_* tree)
{
  FILE* file = fopen("cmpler.s","wb");

  if(file)
  {

    // section .text
    fprintf(file,"section .text\n\tglobal err\n\tglobal _start\n\t%%define sys_call int 0x80");
    int p_reg_index = -1, global_found = -1;
    for(int i = 0; i < tree->l_of_trees; i++)
    {
      if(tree->trees[i]->errors == 0)
      {
        fprintf(file,"\n_start:\n\tmov ecx, errmsg\n\tmov edx, len\n\tmov eax, 4\n\tmov ebx, 1\n\tsys_call\n\n\tmov eax, 1\n\tmov ebx, 1\n\tsys_call");
        fprintf(file,"\nsection .data\n\terrmsg db 0xa,0xa,\"Compilation error\",0xa,0xa\n\tlen equ $ - errmsg");
        goto end;
      }
      switch(tree->trees[i]->TokenType)
      {
        case TREE_P_REG:
        {
          p_reg_index = i;
          create_p_register(tree,file);break;
        }
        case TREE_GLB_REG:
        {
          global_found = 0;
          break;
        }
        default: 
        {
          fprintf(stderr,"\nCompilation Error\n");
          exit(EXIT_FAILURE);
        }
      }
    }


    // Actual code
    fprintf(file,"\nerr:\n\tmov ecx, msg\n\tmov edx, len\n\tmov eax, 4\n\tmov ebx, 1\n\tsys_call\n\n\tmov eax, 1\n\tmov ebx, 1\n\tsys_call");

    if(global_found == 0)
    {
      for(int i = 0; i < tree->l_of_trees; i++)
      {
        switch(tree->trees[i]->TokenType)
        {
          case TREE_P_REG: compile_p_reg(tree->trees[i],file);break;
          case TREE_GLB_REG: break;
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

      // rodata
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
            if(p_reg_index != -1)
            {
              rodata_glb_reg(tree, p_reg_index, file);
              break;
            }
            if(tree->trees[i]->p_references_indexes->list_len > 0)
            {
              fprintf(file,"\n\tcall err\n\tsys_call");
              goto end;
            }
            fprintf(file,"\n\tmov eax, 1\n\tmov ebx, 0\n\tsys_call\n");
            goto end;
          }
          default:
          {
            fprintf(stderr,"\nCompilation Error\n");
            exit(EXIT_FAILURE);
          }
        }
      }
    } else {
      fprintf(file,"\n_start:\n\tcall err");
      fprintf(file,"\n\nsection .rodata\n\tmsg db \"Compilation error: Global not found\",0xa\n\tlen equ $ - msg");
    }

    end:
    fclose(file);
  }

  return tree;
}