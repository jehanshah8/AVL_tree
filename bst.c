#include "bst.h"

int _compare(const void* o1, const void* o2) {
    return *(const int *)o1 - *(const int *)o2;  
}

// Creates and inserts a new node and rebalances tree as needed
bool insert(BSTNode* root, int key) {
    BSTNode* parent = NULL; 
    BSTNode* nd = root; 
    while (nd != NULL) {
        parent = nd; 
        if (key <= nd -> key) { //less than or equal to so that duplicates always go left 
            nd = nd -> left; 
        }  
        else { 
            nd = nd -> right; 
        }
    } // while ends when an empty slot is found
    
    // Checks is memory was successfully allocated 
    if (!create_node(nd, key, parent)) {
        return false; 
    }
    
    /** not needed?
    // Points parent to the correct node
    if (parent == NULL) {
        root = nd; 
    } 
    else {
        if (nd -> key <= parent -> key) {
            parent -> left = nd;
        } 
        else {
            parent -> right = nd;
        } 
    }
    */

    //make_balanced(nd); 
    return true; 
}

/** Attempting to insert recursively. Trouble with maintaining parent
// Creates and inserts a new node and rebalances tree as needed
bool insert(BSTNode* nd, int key) {
    if (nd == NULL) {
        if (!create_node(nd, key)) {
        return false; 
        }
    }
    else if (key <= nd -> key) {
        insert(nd -> left, key); 
    } 
    else {
        insert(nd -> right, key); 
    }
    make_balanced(nd); 
    return true; 
}
*/

// Allocates memeory for a new node and initializes it
bool create_node(BSTNode* nd, int key, BSTNode* parent) {
    nd = malloc(sizeof(*nd)); 
        if (nd == NULL) {
            return false; 
        }
    *nd = (BSTNode) {.key = key, .left = NULL, .right = NULL, .parent = parent}; 
    return true; 
}

bool delete(BSTNode* root, int key) {
    BSTNode* nd = root; 
    while (nd -> key != key) { 
        // key not found
        if (nd == NULL) { 
            return true; 
        }

        if (key <= nd -> key) { //less than or equal to so that duplicates always go left 
            nd = nd -> left; 
        }  
        else { 
            nd = nd -> right; 
        }
    } // while key is not found or node is not NULL

    // both children
    if (nd -> left != NULL && nd -> right != NULL) { 
         BSTNode* temp = nd -> left; 
        // find immidiate predecessor by going left once and then keep going right
        while (temp -> right != NULL) {    
            temp = temp -> right; 
        } // while the predecessor isn't found

        nd = temp; // is this okay or do all parameters need to be copied manually? 
        delete(temp, (temp -> key)); 
    }
    // only left child
    else if (nd -> left != NULL) {
        //link parent of current node to its left child
        nd -> parent -> left = nd -> left; 
        //link the parent of node's left child to node's parent
        nd -> left -> parent = nd -> parent; 
        free(nd); 
    }
    // only right child
    else if (nd -> right != NULL) { 
        //link parent of current node to its right child
        nd -> parent -> right = nd -> right; 
        //link parent of current node to its right child
        nd -> right -> parent = nd -> parent; 
        free(nd); 
    } 
    // no children 
    else {
        free(nd);
    }
    
    //make_balanced(nd); 
    return false; 
}
/**
// Operates on the whole tree
// Takes in the root and checks if any node is unbalanced. 
// If it is unbalanced, it rotates as needed and repeats the checking and correcting process
void make_balanced (BSTNode* root) {
    //TODO
    return; 
}

// Operates on the whole tree
// Tells if the whole tree is balanced or not
bool is_balanced(BSTNode* nd) {
    //TODO
    return false; 
}

// Calculates the balance of any given node
int calc_balance(BSTNode* nd) {

}

// Calculates the height of any given node
int calc_height(BSTNode* nd) {
    //TODO
    return -1; 
}

void rotate_right(BSTNode* nd) {
    //TODO
    return; 
}

void rotate_left(BSTNode* nd) {
    //TODO
    return; 
}

*/