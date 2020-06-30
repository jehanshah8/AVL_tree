#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"

void write_tree_to_file(BSTNode* nd, const char* out_file_path);
void _write_tree(BSTNode* nd, FILE* out_file_ptr);
bool cleanup_b(BSTNode* nd, FILE* in_file_ptr, const char* out_file_path, int print_code); 
int branch_code(BSTNode* nd); 
bool recreate_tree(BSTNode** root, FILE* in_file_ptr);
void attribute_balance(BSTNode* root); 
#endif // HELPERS_H