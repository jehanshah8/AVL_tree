#include "bst.h"

int main (int argc, char** argv) {
    if ("b") {

    }
    else if ("e") {
        evaluate_tree ();
    }
    return EXIT_SUCCESS; 
}

// option "-b"
//least significant bit
if (node -> right == NULL) {
    0;
} else {
    1; 
} 

//second least significant bit 
if (node -> left == NULL) {
    0;
} else {
    1; 
} 

// option "-e"
void evaluate_tree (const char* path) {
    FILE* fptr = NULL; 
    fptr = fopen(path, "r"); 

    // cannot open
    if (fptr == NULL) {
        printf("%d,%d,%d\n", -1, 0, 0);
        return EXIT_FAILURE;
    }
    // can open but wrong format
    else if (is_valid_input()) {
        printf("%d,%d,%d\n", 0, 0, 0);
        return EXIT_FAILURE;
    }
    // can open and correct format 
    else {
        if (is_bst()) {
            if (is_balanced()) {
                printf("%d,%d,%d\n", 1, 1, 1);
                return EXIT_SUCCESS;
            } 
            else {
                printf("%d,%d,%d\n", 1, 1, 0);
                return EXIT_SUCCESS;
            }
        } 
        else {
            printf("%d,%d,%d\n", 1, 0, 0);
            return EXIT_SUCCESS;
        }
    }
}

bool is_valid_input() {

}

bool is_bst() {

}