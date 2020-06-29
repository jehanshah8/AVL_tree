#include "bst.h"
#include "helpers.h"
#include <string.h>

bool build_tree(const char* in_file_path, const char* out_file_path);

int main (int argc, char** argv) {

    if (argc == 4 && strcmp(argv[1], "-b") == 0) {
        if (!build_tree(argv[2], argv[3])) {
            return EXIT_FAILURE; 
        } 
    }
    else if (argc == 3 && strcmp(argv[1], "-e") == 0) {
        return 0; 
        //if (!evaluate_tree (argv[2])) {
          //  return EXIT_FAILURE; 
        //} 
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
                   return cleanup(root, in_file_ptr, out_file_path, 0); 
                }
                break; 
                     
            case 'd': 
                if (!delete(&root, key)) { 
                  return cleanup(root, in_file_ptr, out_file_path, 0); 
                }
                break; 
            default:
                return cleanup(root, in_file_ptr, out_file_path, 0); 
        }
        
    }
    printf("final output:\n");
    return cleanup(root, in_file_ptr, out_file_path, 1); 
}

/**
// option "-e"
bool evaluate_tree (const char* in_file_path) {
    
    * input file should have the following format:
    * int key char pattern
    * '1' -> has right child
    * '2' -> has left child
    * '3' -> has both children
    

    FILE* in_file_ptr = NULL; 
    in_file_ptr = fopen(in_file_path, "rb"); 

    // cannot open
    if (in_file_ptr == NULL) {
        printf("%d,%d,%d\n", -1, 0, 0);
        return EXIT_FAILURE;
    }
    // can open but wrong format
    //loop fread 
        if (!is_valid_node()) {
        printf("%d,%d,%d\n", 0, 0, 0);
        fclose(in_file_ptr);
        return EXIT_FAILURE;
        }
        // can open and correct format 
        else {
            // is bst
            if (is_bst()) {
                //is balanced 
                if (is_balanced()) {
                printf("%d,%d,%d\n", 1, 1, 1);
                fclose(in_file_ptr);
                return EXIT_SUCCESS;
                } 
                // bst but not balanced
                else {
                printf("%d,%d,%d\n", 1, 1, 0);
                fclose(in_file_ptr);
                return EXIT_SUCCESS;
                }
            } 
            // not bst
            else {
            printf("%d,%d,%d\n", 1, 0, 0);
            fclose(in_file_ptr);
            return EXIT_SUCCESS;
            }
        }
    
}

bool is_bst() {

}
*/