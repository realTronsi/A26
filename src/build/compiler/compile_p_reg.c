#include "compile_p_reg.h"

SyntaxTree_* create_p_register(SyntaxTree_* tree, FILE* file)
{
  fprintf(file,"\n\tglobal p_reg");
  return tree;
}

SyntaxTree_* compile_p_reg(SyntaxTree_* tree, FILE* file)
{
  // we will get to this
  fprintf(file,"\np_reg:\n");

  for(int i = 0; i < tree->p_reg_values->list_len; i++)
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
  if(tree->p_reg_values->list_len > 0)
  {
    char* sequence = malloc(32);
    for(int i = 0; i < tree->p_reg_values->list_len; i++)
    {
      sprintf(sequence,"\n\tp_msg_%d db '",i+1);
      char* str = (char*)tree->p_reg_values->values[i];
      for(int x = 0; x < strlen(str); x++)
      {
        if(x == strlen(str)-1)
        {
          if(str[x]!='\0')
          {
            char* curr = calloc(2,sizeof(*curr));
            curr[0] = str[x];
            curr[1] = '\0';
            strcat(sequence,curr);
            free(curr);
          }
          add_end:
          strcat(sequence,"'");
          break;
        }
        if(str[x] == '\\')
        {
          redo_:
          x++;
          if(str[x] == 'n')
          {
            strcat(sequence,"',0xa,'");
            x++;
            if(str[x] == '\\') goto redo_;
          }
        }

        if(str[x] != '\0')
        {
          char* curr = calloc(2,sizeof(*curr));
          curr[0] = str[x];
          curr[1] = '\0';
          strcat(sequence,curr);
          if(str[x+1] == '\0')
          {
            free(curr);
            goto add_end;
          }
        } else goto add_end;
      }
      fprintf(file,"%s",sequence);
    }
  }
  return tree;
}