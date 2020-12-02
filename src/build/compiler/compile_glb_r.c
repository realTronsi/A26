#include "compile_glb_rg.h"

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
      for(int i = 0; i < tree->trees[p_reg_index]->p_reg_values->list_len; i++)
      {
        char* val = tree->trees[p_reg_index]->p_reg_values->values[i];
        int minus = 0;
        for(int x = 0; x < strlen(val); x++)
        {
          if(val[x] == '\\') minus++;
        }
        fprintf(file,"\n\tmov ecx, p_msg_%d\n\tmov edx, %ld\n\tmov eax, 4\n\tmov ebx, 1\n\tsys_call\n",i+1,strlen(tree->trees[p_reg_index]->p_reg_values->values[i])-minus);
      }
    }
    else
    {
      if(!(atoi(tree->p_references_indexes->values[i]) >= tree->trees[p_reg_index]->p_reg_values->list_len) && !(atoi(tree->p_references_indexes->values[i]) < 0))
      {
        int minus = 0;
        char* val = tree->trees[p_reg_index]->p_reg_values->values[atoi(tree->p_references_indexes->values[i])];
        for(int x = 0; x < strlen(val); x++)
        {
          if(val[x] == '\\') minus++;
        }
        fprintf(file,"\n\tmov ecx, p_msg_%d\n\tmov edx, %ld\n\tmov eax, 4\n\tmov ebx, 1\n\tsys_call\n",atoi(tree->p_references_indexes->values[i])+1,strlen(tree->trees[p_reg_index]->p_reg_values->values[atoi(tree->p_references_indexes->values[i])])-minus);
      }else
      {
        fprintf(file,"\n\tcall err");
      }
    }
  }
  return tree;
}