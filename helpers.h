#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"

void print_tree(BSTNode* nd);
void write_tree_to_file(BSTNode* nd, const char* out_file_path);
void _write_tree(BSTNode* nd);
bool cleanup_b(BSTNode* nd, FILE* in_file_ptr, const char* out_file_path, int print_code); 
char type_of_branches(BSTNode* nd); 
bool recreate_tree(BSTNode** root, FILE* in_file_ptr);
int is_bst(BSTNode* nd, int prev_key, int output_code);
#endif // HELPERS_H