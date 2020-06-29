#include "helpers.h"

// Pre-order printing
void print_tree(BSTNode* nd) {
    if (nd != NULL) {
        printf("%d %c %d\n", nd -> key, type_of_branches(nd), nd -> balance);
        print_tree(nd -> left); 
        print_tree(nd -> right); 
    }
}

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
    printf("Printing tree\n");
    if (nd != NULL) {
        /**TODO**/ //wirte to file here //////////////////////
        _write_tree(nd -> left); 
        _write_tree(nd -> right); 
    }
}

bool cleanup_b (BSTNode* nd, FILE* in_file_ptr, const char* out_file_path, int print_code) {  
    //write_tree_to_file(nd, out_file_path); ///////////////////uncomment this line
    print_tree(nd); 
    destroy_tree(nd);
    fclose(in_file_ptr); 
    printf("%d\n", print_code); 
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
                (*root) -> balance += 1;
                recreate_tree(&((*root) -> left), in_file_ptr); 
                break;
            case 1: //right
                //printf("branch_code case: %d\n", branch_code);
                recreate_tree(&((*root) -> right), in_file_ptr); 
                (*root) -> balance -= 1;
                break;
            case 0: 
                //printf("branch_code case: %d\n", branch_code);
                break;
            default:
                //printf("branch_code case: default\n");
                // incorrect format
                return false;
        }

    return true;
}

int is_bst(BSTNode* nd, int prev_key, int output_code) {
    if (nd == NULL) {
        return output_code; 
    }
    printf("in is_bst, key = %d, prev_key = %d output_code = %d\n", nd -> key, prev_key, output_code); 
    output_code = is_bst(nd -> left, nd -> key, output_code);
    if (nd -> key < prev_key) {
        // not bst
        printf("in is_bst, key = %d, prev_key = %d\n", nd -> key, prev_key); 
        printf("not a bst\n");
        return 00; 
    }
    /**
    if (nd -> balance >= 2 || nd -> balance <= -2) {
        output_code = 10; 
    }
    */
    output_code = is_bst(nd -> right, nd -> key, output_code);
    return output_code; 
}

/**
BSTNode* next = nd -> left; 
        BSTNode* curr = nd;
    BSTNode* prev = NULL;  
    while (next != NULL)
    {   
        prev = curr; 
        curr = next; 
        next = next -> left; 
        // Breaks rule of BST, left must be smalled than parent
        if (curr -> key > prev -> key) {
            // not bst
            printf("%d,%d,%d\n", 1, 0, 0);
            return; 
        }
    }
    
    next = curr -> right;
    is_bst(BSTNode* nd) 
    while (next != NULL) { 
        prev = curr; 
        curr = next; 
        next = curr -> left; 
        // Breaks rule of BST, right must be bigger than parent
        if (next -> key > curr -> key) {
            
            return; 
        }
    }




        is(nd -> left); 
        printf("%d %c\n", nd -> key, type_of_branches(nd));
        is(nd -> right); 
    return 

*/



