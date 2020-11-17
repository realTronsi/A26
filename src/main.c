#include <stdio.h>
#include "build/lexer/lexer.h"
#include "build/parser/parser.h"
#include "build/parser/AST/syn_tree.h"
#include "build/compiler/compiler.h"
#include "build/readfile.h"

int main(int args, char* argv[])
{
    if(args < 2)
    {
        // no input file, throw error.
        fprintf(stderr,"\ntronsi is doing great :D\n");
        exit(EXIT_FAILURE);
    }
  char* code = read_file(argv[1]);
  Lexer_* lexer = lexer_init(code);
  Parser_* parser = parser_init(lexer);
  SyntaxTree_* tree = parse(parser);
}