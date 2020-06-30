#include "helpers.h"

// Pre-order printing
void print_tree(BSTNode* nd) {
    if (nd != NULL) {
        printf("%d %c %d\n", nd -> key, branch_code(nd), nd -> balance);
        print_tree(nd -> left); 
        print_tree(nd -> right); 
    }
}

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
    fread(&key, sizeof(key), 1, in_file_ptr); 
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
        attribute_balance(*root);
    return true;
}

void attribute_balance(BSTNode* root) {
    if (root == NULL) {
        return;
    }

    if (root -> left != NULL) {     
         root -> left -> balance = calc_balance(root -> left);  
    }  
    
    if (root -> right != NULL) {     
        root -> right -> balance = calc_balance(root -> right); 
    }
    
    root -> balance = calc_balance(root);
}

int calc_balance(BSTNode* nd) {
    if (nd == NULL) {
        return 0; 
    }

    return calc_height(nd -> left) - calc_height(nd -> right); 
}

int calc_height(BSTNode* nd) {
    if (nd == NULL) {
        return - 1; 
    }

    int left_height = 0; 
    int right_height = 0; 
    if (nd -> left != NULL) {     
        left_height = calc_height(nd -> left) + 1; 
    } 

    if (nd -> right != NULL) {     
        right_height = calc_height(nd -> right) + 1; 
    } 
    
    if (left_height >= right_height) {
        //printf("key = %d, left height = %d\n", nd -> key, left_height);
        return left_height; 
    } 
    else
    {
        //printf("key = %d, right height = %d\n", nd -> key, right_height);
        return right_height; 
    }
}

int is_bst(BSTNode* nd, int output_code) {
    if (nd == NULL) {
        return output_code; 
    }

    if (output_code == 00) {
        return output_code; 
    } 
    
    if (nd -> left != NULL) { 
        if (nd -> key < nd -> left -> key) {
            // not bst
            //printf("key = %d, left -> key = %d\n", nd -> key, nd -> left -> key);
            return 00;
        }
        else {
            output_code = is_bst(nd -> left, output_code);
        }
    }

    if (nd -> right != NULL) {
        if (nd -> key > nd -> right -> key) {
            // not bst 
            //printf("key = %d, right -> key = %d\n", nd -> key, nd -> right -> key);
            return 00;
        }
        else {
            output_code = is_bst(nd -> right, output_code);
        }
    }
    
    return output_code; 
}

int is_balanced(BSTNode* nd, int output_code) {
    if (nd == NULL) {
        return output_code; 
    }

    if (output_code == 0) {
        return output_code; 
    } 
    
    if (nd -> left != NULL) { 
        if (nd -> balance >= 2 || nd -> balance <= -2) {
            // Not balanced
            //printf("key = %d\n", nd -> key);
            return 0;
        }
        else {
            output_code = is_balanced(nd -> left, output_code);
        }
    }

    if (nd -> right != NULL) {
        if (nd -> balance >= 2 || nd -> balance <= -2) {
            // Not balanced
            //printf("key = %d\n", nd -> key);
            return 0;
        }
        else {
            output_code = is_balanced(nd -> right, output_code);
        }
    }
    return output_code; 
}