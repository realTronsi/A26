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
        fprintf(stderr,"\nPlease provide an input file\n");
        exit(EXIT_FAILURE);
    }
    Lexer_* lexer = lexer_init(read_file(argv[1]),argv[1]);
    Parser_* parser = parser_init(lexer);
    SyntaxTree_* tree = parse(parser);
    compile(tree);

    free(lexer);
    free(parser);
    free(tree);
}