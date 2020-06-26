#include "helpers.h"

// Pre-order write to file
void write_tree_to_file(BSTNode* nd, const char* out_file_path) {
    FILE* out_file_ptr = fopen(out_file_path, "wb"); 
    if (out_file_ptr != NULL) {
        _write_tree(nd); 
    } 
    fclose(out_file_ptr); 
}

// helper to write to file recursively
void _write_tree(BSTNode* nd) {
    if (nd != NULL) {
        
        printf("%d %c", nd -> key, type_of_branches(nd));
        _write_tree(nd -> left); 
        _write_tree(nd -> right); 
    }
}

bool cleanup (BSTNode* nd, FILE* in_file_ptr, const char* out_file_path, int print_code) { 
    write_tree_to_file(nd, out_file_path); 
    fclose(in_file_ptr); 
    printf("%d\n", 1); 
    return print_code == 1; 
}

char type_of_branches(BSTNode* nd) {
    // both children 
    if (nd -> left != NULL && nd -> right != NULL) { 
        return '3'; 
    }
    // only left child
    else if (nd -> left != NULL) {
        return '2';
    }
    // only right child
    else if (nd -> right != NULL) { 
        return '1';
    } 
    // no children
    else {
       return '0';
    }
}