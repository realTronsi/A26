#include "syn_tree.h"

SyntaxTree_* syn_tree_init(int id){
    SyntaxTree_* tree = calloc(1,sizeof(*tree)*15);

    tree->TokenType = id;

    tree->trees = calloc(1,sizeof(*tree->trees)*15);
    tree->l_of_trees = 0;

    tree->p_reg = calloc(1,sizeof(*tree->p_reg)*15);
    tree->global_return = 0;
    tree->global_exists = -1;
    
    return tree;
}