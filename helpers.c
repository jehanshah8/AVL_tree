#include "helpers.h"
#include "bst.h"

// Pre-order write to file
void write_tree_to_file(BSTNode* nd, const char* out_file_path) {
    FILE* out_file_ptr = fopen(out_file_path, "wb"); 
    if (out_file_ptr != NULL) {
        _write_tree(nd, out_file_ptr); 
    } 
    fclose(out_file_ptr); 
}

// helper to write to file recursively
void _write_tree(BSTNode* nd, FILE* out_file_ptr) {
    //printf("printing tree\n");
    if (nd != NULL) {
        char code = branch_code(nd); 
        fwrite(&(nd -> key), sizeof(nd -> key), 1, out_file_ptr);
        fwrite(&code, sizeof(char), 1, out_file_ptr); 
        //fputc(code, out_file_ptr); 
        _write_tree(nd -> left, out_file_ptr); 
        _write_tree(nd -> right, out_file_ptr); 
    }
}

bool cleanup_b (BSTNode* nd, FILE* in_file_ptr, const char* out_file_path, int print_code) {  
    //printf("final output:\n");
    //print_tree(nd); 
    write_tree_to_file(nd, out_file_path);
    destroy_tree(nd);
    fclose(in_file_ptr); 
    printf("%d\n", print_code); 
    return print_code == 1; 
}

int branch_code(BSTNode* nd) {
    // both children 
    if (nd -> left != NULL && nd -> right != NULL) { 
        return 3; 
    }
    // only left child
    else if (nd -> left != NULL) {
        return 2;
    }
    // only right child
    else if (nd -> right != NULL) { 
        return 1;
    } 
    // no children
    else {
       return 0;
    }
}

// Incorrectly attributes balance. Check tree 0 to see error by running tree 0 in -b mode and -e mode. 
// Last column prints balance
bool recreate_tree(BSTNode** root, FILE* in_file_ptr) {
    //printf("recreating node\n");
    int key;
    char branch_code; 
    if (fread(&key, sizeof(key), 1, in_file_ptr) == 1) {; 
        branch_code = fgetc(in_file_ptr);
        //printf("read finished\n");
        //printf("recreating node with key = %d\n", key);
        *root = create_node(key); 
        //printf("node created successfully\n");
        //printf("branch_code = %d\n", branch_code);
        switch (branch_code) {
            case 3: //left & right
                //printf("branch_code case: %d\n", branch_code);
                recreate_tree(&((*root) -> left), in_file_ptr); 
                recreate_tree(&((*root) -> right), in_file_ptr); 
                break; 
            case 2: //left 
                //printf("branch_code case: %d\n", branch_code);
                recreate_tree(&((*root) -> left), in_file_ptr); 
                break;
            case 1: //right
                //printf("branch_code case: %d\n", branch_code);
                recreate_tree(&((*root) -> right), in_file_ptr); 
                
                break;
            case 0: 
                //printf("branch_code case: %d\n", branch_code);
                break;
            default:
                //printf("branch_code case: default\n");
                // incorrect format
                return false;
        }
        //attribute_balance(*root);
        set_height(root);
    }
    return true;
}



