#include "syn_tree.h"

SyntaxTree_* syn_tree_init(int id){
    SyntaxTree_* tree = calloc(1,sizeof(*tree)*15);

    tree->TokenType = id;
    tree->errors = -1;

    tree->trees = calloc(1,sizeof(*tree->trees)*15);

    // P_REG
    tree->p_reg_values =  blist_init();

    // GLOBAL
    tree->global_return = 0;
    tree->global_exists = -1;
    tree->p_references_indexes = blist_init();
    tree->d_references_indexes = blist_init();
    tree->strings = blist_init();
    tree->escape_chars = calloc(1,sizeof(*tree->escape_chars));
    tree->ec_indexes = calloc(1,sizeof(*tree->ec_indexes));
    tree->locations = calloc(1,sizeof(*tree->locations));
    tree->am = 0;

    // UD
    tree->UD_names = calloc(1,sizeof(*tree->UD_names));
    tree->UD_values = calloc(1,sizeof(*tree->UD_values));
    tree->l_of_ud_variables = 0;

    return tree;
}