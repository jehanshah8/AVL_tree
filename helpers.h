#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"

void write_tree_to_file(BSTNode* nd, const char* out_file_path);
void _write_tree(BSTNode* nd);
bool cleanup (BSTNode* nd, FILE* in_file_ptr, const char* out_file_path, int print_code); 
char type_of_branches(BSTNode* nd); 
bool is_valid_node(); 

#endif // HELPERS_H