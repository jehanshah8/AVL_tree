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

    int key; 
    char operation; 
    BSTNode* root = NULL;

    while (fread(&key, sizeof(key), 1, in_file_ptr) == 1) {
        operation = fgetc(in_file_ptr); 
        //printf("key = %d\noperation = %c\n", key, operation);
        switch (operation) {
            case 'i': 
                if (!insert(&root, key)) { 
                   return cleanup_b(root, in_file_ptr, out_file_path, 0); 
                }
                break; 
                     
            case 'd': 
                if (!delete(&root, key)) { 
                  return cleanup_b(root, in_file_ptr, out_file_path, 0); 
                }
                break; 
            default:
                return cleanup_b(root, in_file_ptr, out_file_path, 0); 
        }
        //print_tree(root);
    }
    printf("final output:\n");
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
    print_tree(root); 
    // Check if the tree created is a BST and if it is balanced.
    
    if (root == NULL) {
        // Empty tree. What to print???????
        printf("%d,%d,%d\n", 1, 1, 1);
        return true; 
    }

    int output_code = is_bst(root, 10);
    output_code += is_balanced(root, 1);

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
