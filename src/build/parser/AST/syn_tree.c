#include "syn_tree.h"

SyntaxTree_* syn_tree_init(int id){
    SyntaxTree_* tree = calloc(1,sizeof(*tree)*15);

    tree->TokenType = id;

    tree->trees = calloc(1,sizeof(*tree->trees)*15);
    tree->l_of_trees = 0;

    // P_REG
    tree->p_reg =  blist_init();

    // GLOBAL
    tree->global_return = 0;
    tree->global_exists = -1;
    tree->p_references_indexes = blist_init();
    tree->d_references_indexes = blist_init();
    
    return tree;
}