#include "bst.h"
#include "helpers.h"
#include <string.h>

bool build_tree(const char* in_file_path, const char* out_file_path);
bool evaluate_tree (const char* in_file_path); 
int main (int argc, char** argv) {

    if (argc == 4 && strcmp(argv[1], "-b") == 0) {
        if (!build_tree(argv[2], argv[3])) {
            return EXIT_FAILURE; 
        } 
    }
    else if (argc == 3 && strcmp(argv[1], "-e") == 0) { 
        if (!evaluate_tree (argv[2])) {
            return EXIT_FAILURE; 
        } 
    }
    else {
        return EXIT_FAILURE; 
    }

    return EXIT_SUCCESS; 
}

// Option "-b"
bool build_tree(const char* in_file_path, const char* out_file_path) {
    FILE* in_file_ptr = NULL; 
    in_file_ptr = fopen(in_file_path, "rb"); 
    
    // Check if file was opened successfully
    if (in_file_ptr == NULL) {
        printf("%d\n", -1); 
        return false; 
    }

    int count = 0;
    int key; 
    char operation; 
    BSTNode* root = NULL;
    BSTNode* parent = NULL; 

    while (fread(&key, sizeof(key), 1, in_file_ptr) == 1) {
        operation = fgetc(in_file_ptr); 
        count++; 
        //printf("%d.)key = %d\toperation = %c\n", count, key, operation);
        switch (operation) {
            case 'i':
                //printf("inserting...\n");
                //root = insert(root, key); 
                if (!insert(&root, key)) { // if insertion failed 
                   return cleanup_b(root, in_file_ptr, out_file_path, 0); 
                }
                break; 
                     
            case 'd': 
                //printf("deleting...\n"); 
                if (!delete(&root, &parent, key)) {
                    return cleanup_b(root, in_file_ptr, out_file_path, 0);
                };
                break; 
            default:
                return cleanup_b(root, in_file_ptr, out_file_path, 0); 
        }
        //print_tree(root);
    }
    //printf("final output:\n");
    // to print tree, go into cleanup_b function (located in helpers.c) and uncomment print_tree(nd)
    return cleanup_b(root, in_file_ptr, out_file_path, 1); 
}


// option "-e"
bool evaluate_tree (const char* in_file_path) {
    FILE* in_file_ptr = NULL; 
    in_file_ptr = fopen(in_file_path, "rb"); 

    // Check if file was opened successfully
    if (in_file_ptr == NULL) {
        printf("%d,%d,%d\n", -1, 0, 0);
        return false;
    }

    // Recursively create tree from example file
    //printf("trying to recreate tree\n");
    BSTNode* root = NULL;
    if (!recreate_tree(&root, in_file_ptr)) {
        fclose(in_file_ptr);
        destroy_tree(root);
        printf("%d,%d,%d\n", 0, 0, 0);
        return false;
    } 
    fclose(in_file_ptr);
    //uncomment below to see the tree that was built from file
    //print_tree(root); 
    
    if (root == NULL) {
        //PeerReview:
        // Empty tree. What to print???????
        printf("%d,%d,%d\n", 1, 1, 1);
        return true; 
    }

    // Check if the tree created is a BST and if it is balanced.
    int output_code = is_bst(root, 10);
    output_code += is_balanced(root, 1);
    destroy_tree(root);
    switch (output_code) {
        case 11: 
            // BST and is balanced 
            printf("%d,%d,%d\n", 1, 1, 1);
            break;
        case 10: 
            // BST but NOT balanced
            printf("%d,%d,%d\n", 1, 1, 0);
            break;

        case 01: 
            // Not BST but is balanced
            printf("%d,%d,%d\n", 1, 0, 1);
            break;
        case 00: 
            // Not BST and not balanced
            printf("%d,%d,%d\n", 1, 0, 0);
            break;
    }
    return true; 
}
