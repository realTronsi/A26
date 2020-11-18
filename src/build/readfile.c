#include "readfile.h"

char* read_file(char* filename){
  FILE *file = fopen(filename, "rb");
  char* code = calloc(1,sizeof(*code));

  if(file){
      fseek(file, 0, SEEK_END);
      long size = ftell(file);
      fseek(file, 0, SEEK_SET);
      if(size > 0)
      {
        code = realloc(
          code,
          size*sizeof(*code)
        );
          fread(code,1,size,file);
          return code;
      }
  }
  
  fprintf(stderr,"\nThe file %s does not exist\n",filename);
  exit(EXIT_FAILURE);
}