#include "syn_tree.h"

SyntaxTree_* syn_tree_init(int id){
    SyntaxTree_* tree = calloc(1,sizeof(*tree));

    tree->TokenType = id;

    tree->trees = calloc(1,sizeof(*tree->trees));
    tree->l_of_trees = 0;

    tree->reg_p = calloc(1,sizeof(*tree->reg_p));
    tree->global_return = 0;
    tree->global_exists = -1;
    
    return tree;
}