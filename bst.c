#include "bst.h"
#include "helpers.h"

int _compare(const void* o1, const void* o2) {
    return *(const int *)o1 - *(const int *)o2;  
}

// Allocates memeory for a new node and initializes it
BSTNode* create_node(int key) {
    BSTNode* nd = malloc(sizeof(*nd)); 
        if (nd == NULL) {
            printf("MEMORY ERROR: Failed to allocate memory for new node\n"); 
            return NULL; 
        }
    *nd = (BSTNode) {.key = key, .left = NULL, .right = NULL, .balance = 0}; 
    //printf("Node created successfully\n"); 
    return nd; 
}

// Creates and inserts a new node and rebalances tree as needed
bool insert(BSTNode** root, int key) {
    printf("inserting new node\n");
    BSTNode* parent_ya = NULL;
    BSTNode* parent_curr = NULL;  
    BSTNode* curr = *root; 
    BSTNode* youngest_ancestor = *root; 
    BSTNode* nd = NULL;
    while (curr != NULL) {
        if (key <= curr -> key) { //less than or equal to so that duplicates always go left 
            nd = curr -> left; //point left
        }  
        else { 
            nd = curr -> right; //point right
        }

        if (nd != NULL && nd -> balance != 0) {
            parent_ya = curr; 
            youngest_ancestor = nd;  
        }
        parent_curr = curr; 
        curr = nd;
    } // while ends when curr points to an empty slot
    
    // Creates new node and checks is memory was successfully allocated 
    nd = create_node(key); 
    if (nd == NULL) {
        return false; 
    }
    
    // Points parent to the correct node
    if (parent_curr == NULL) {
        *root = nd; 
        return true; 
    } 
    else {
        if (nd -> key <= parent_curr -> key) {
            parent_curr -> left = nd;
        } 
        else {
            parent_curr -> right = nd;
        } 
    }
    
    printf("reached balancing stage\n");
    // Keeps track of balance preemptively?? 
    curr = youngest_ancestor;
    // testing
    if (curr == NULL) {
        printf("curr = NULL\n");
    }
    //end testing 
    while (curr != nd) { //remove && curr != NULL
        if (key <= curr -> key) { //correct <= vs <
            printf("if\n");
            curr -> balance += 1; 
            curr = curr -> left;   
        }
        else {
            curr -> balance -= 1; 
            curr = curr -> right; 
        }
    }

    printf("evaluating if balacing is required\n");
    // If it's already balanced, return
    if (youngest_ancestor -> balance < 2 && youngest_ancestor -> balance > -2) { 
        return true; 
    }

    printf("needs balancing\n");
    BSTNode* child; // which child nd is inserted into
    // Make child point to the tallest child of ya, which was made talled by adding node
    if (key <= youngest_ancestor -> key) {
        child = youngest_ancestor -> left;
    } 
    else {
        child = youngest_ancestor -> right; 
    }
    
    // The subtree rooted at the youngest ancestor needs balancing 
    // curr points to the new root of the subtree
    // parent_ya has to point to curr after rebalancing

    // If both the youngest ancestor and the child are unbalanced in the SAME direction

    // Left heavy => rotate right
    if (youngest_ancestor -> balance == 2 && child -> balance == 1) {
        curr = child; 
        right_rotate(&youngest_ancestor); 
        youngest_ancestor -> balance = 0; 
        child -> balance = 0; 
    }

    // Right heavy => rotate left
    if (youngest_ancestor -> balance == -2 && child -> balance == -1) {
        curr = child; 
        left_rotate(&youngest_ancestor); 
        youngest_ancestor -> balance = 0; 
        child -> balance = 0; 
    }

    // If both the youngest ancestor and the child are unbalanced in OPPOSITE directions

    // Left rotate then, right rotate
    if (youngest_ancestor -> balance == 2 && child -> balance == -1) {
        curr = child -> right; 
        left_rotate(&child); 
        youngest_ancestor -> left = curr; 
        right_rotate(&youngest_ancestor);
        if (curr -> balance == 0) {
            youngest_ancestor -> balance = 0; 
            child -> balance = 0;
        }
        else {
            if (curr -> balance == 1) {
                youngest_ancestor -> balance = -1; 
                child -> balance = 0;
            }
            else {
                youngest_ancestor -> balance = 0; 
                child -> balance = 1; 
            }
            curr -> balance = 0; 
        }
    }

    // Right rotate then, left rotate
    if (youngest_ancestor -> balance == -2 && child -> balance == 1) {
        curr = child -> left; 
        right_rotate(&child); 
        youngest_ancestor -> right = curr; 
        left_rotate(&youngest_ancestor);
        if (curr -> balance == 0) {
            youngest_ancestor -> balance = 0; 
            child -> balance = 0;
        }
        else {
            if (curr -> balance == -1) {
                youngest_ancestor -> balance = 1; 
                child -> balance = 0;
            }
            else {
                youngest_ancestor -> balance = 0; 
                child -> balance = -1; 
            }
            curr -> balance = 0; 
        }     
    }

    if (parent_ya == NULL) {
        *root = curr; 
    } 
    else {
        if (key <= parent_ya -> key) {
            parent_ya -> left = curr; 
        }
        else {
            parent_ya -> right = curr; 
        }
    }

    return true; 
}

/*
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
*/

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
*/

void right_rotate(BSTNode** nd) {
    BSTNode* temp = ((*nd) -> left) -> right;
    ((*nd) -> left) -> right = *nd; 
    nd = &((*nd) -> left);
    ((*nd) -> right) -> left = temp;
}

void left_rotate(BSTNode** nd) {
    BSTNode* temp = ((*nd) -> right) -> left;
    ((*nd) -> right) -> left = *nd; 
    nd = &((*nd) -> right);
    ((*nd) -> left) -> right = temp;
}


