#include "bst.h"
#include "helpers.h"

int _compare(const void* o1, const void* o2) {
    return *(const int *)o1 - *(const int *)o2;  
}

// Creates and inserts a new node and rebalances tree as needed
bool insert(BSTNode** root, int key) {
    printf("inserting new node\n");
    BSTNode* parent_ya = NULL;
    BSTNode* parent_curr = NULL;  
    BSTNode* youngest_ancestor = *root; 
    BSTNode* curr = *root; 
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
    
    //printf("reached balancing stage\n");
    // Keeps track of balance preemptively?? 
    curr = youngest_ancestor;
    while (curr != nd) { 
        if (key <= curr -> key) { 
            curr -> balance += 1; 
            curr = curr -> left;   
        }
        else {
            curr -> balance -= 1; 
            curr = curr -> right; 
        }
    }

    //printf("evaluating if balacing is required\n");
    // If it's already balanced, return
    if (youngest_ancestor -> balance < 2 && youngest_ancestor -> balance > -2) { 
        return true; 
    }

    //printf("needs balancing\n");
    make_balanced_i (root, key, curr, youngest_ancestor, parent_ya);
    return true; 
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

//PeerReview: Deleting works without any rebalancing 
bool delete(BSTNode** nd, BSTNode** parent, BSTNode** grandparent, int key) {
    printf("deleting node\n");

    if (*nd == NULL) { 
        return true; 
    }

    BSTNode* new_child = NULL; 

    if ((*nd) -> key == key) {
        detach_node(*nd, *parent, key);
    } 
    else if (key < (*nd) -> key) { //less than or equal to so that duplicates always go left 
        delete(&((*nd) -> left), nd, parent, key); 
    }  
    else { 
        delete(&((*nd) -> right), nd, parent, key);
    }
    
    if (parent != NULL && *parent != NULL) {
        if (key <= (*parent) -> key) { 
            new_child = (*parent) -> left;
        }
        else {
            new_child = (*parent) -> right;
        }
        
        (*parent) -> balance = calc_balance(*parent);
        if ((*parent) -> balance >= 2 || (*parent) -> balance <= -2) {
            printf("FUCK YOU! SEG FAULT!!!!!\n");
            printf("needs rebalancing\n");
            make_balanced_d (grandparent, parent, &new_child);
        }
    }
    return true; 
}

void make_balanced_d(BSTNode** grandparent, BSTNode** child, BSTNode** parent) {
    // The subtree rooted at the youngest ancestor needs balancing 
    // curr points to the new root of the subtree
    // parent_ya has to point to curr after rebalancing

    // If both the youngest ancestor and the child are unbalanced in the SAME direction
    BSTNode* temp; 
    // Left heavy => rotate right
    if ((*parent) -> balance == 2 && (*child) -> balance == 1) { 
        temp = *child;
        right_rotate(parent); 
        (*parent) -> balance = 0; 
        (*child) -> balance = 0; 
    }

    // Right heavy => rotate left
    if ((*parent) -> balance == -2 && (*child) -> balance == -1) {
        temp = *child;
        left_rotate(parent); 
        (*parent) -> balance = 0; 
        (*child) -> balance = 0; 
    }

    // If both the youngest ancestor and the child are unbalanced in OPPOSITE directions

    // Left rotate then, right rotate
    if ((*parent) -> balance == 2 && (*child) -> balance == -1) {
        temp = (*child) -> right; 
        left_rotate(child); 
        (*parent) -> left = temp; 
        right_rotate(parent);
        if (temp -> balance == 0) {
            (*parent) -> balance = 0; 
            (*child) -> balance = 0;
        }
        else {
            if (temp -> balance == 1) {
                (*parent) -> balance = -1; 
                (*child) -> balance = 0;
            }
            else {
                (*parent) -> balance = 0; 
                (*child) -> balance = 1; 
            }
            temp -> balance = 0; 
        }
    }

    // Right rotate then, left rotate
     if ((*parent) -> balance == -2 && (*child) -> balance == 1) {
        temp = (*child) -> left; 
        right_rotate(child); 
        (*parent) -> right = temp; 
        left_rotate(parent);
        if (temp -> balance == 0) {
            (*parent) -> balance = 0; 
            (*child) -> balance = 0;
        }
        else {
            if (temp -> balance == -1) {
                (*parent) -> balance = 1; 
                (*child) -> balance = 0;
            }
            else {
                (*parent) -> balance = 0; 
                (*child) -> balance = -1; 
            }
            temp -> balance = 0; 
        }
    }

    if (temp -> key <= (*grandparent) -> key) {
        (*grandparent) -> left = temp; 
    }
    else {
        (*grandparent) -> right = temp; 
    }
}

void detach_node(BSTNode* curr, BSTNode* parent_curr, int key) {
       // no children 
    if (curr -> left == NULL && curr -> right == NULL) {
        //printf("target node has no children\n");
        if (parent_curr != NULL) {
            if (parent_curr -> left == curr) {
                parent_curr -> left = NULL;
            }
            else {
                parent_curr -> right = NULL;
            }
        }
        free(curr); 
    }
    // both children
    else if (curr -> left != NULL && curr -> right != NULL) { 
        //printf("target node has 2 children\n");
         BSTNode* temp = curr -> left; 
         BSTNode* parent_temp = curr; 
        // find immidiate predecessor by going left once and then keep going right
        while (temp -> right != NULL) {
            parent_temp = temp;     
            temp = temp -> right; 
        } // while the predecessor isn't found

        copy(curr, temp);
        detach_node(temp, parent_temp, (temp -> key)); //needs recursice call because it could also have 2, 1, or no children
    }
    // only left child
    else if (curr -> left != NULL) {
        //printf("target node has only left child\n");
        //link parent of current node to its left child
        if (parent_curr -> left == curr) {
            parent_curr -> left = curr -> left; 
        }
        else {
            parent_curr -> right = curr -> left;
        }
        //Need to readjust balance of parent_curr
        *curr = (BSTNode) {.key = key, .left = NULL, .right = NULL, .balance = 0}; 
        free(curr); 
    }
    // only right child
    else if (curr -> right != NULL) { 
        //printf("target node has only right child\n");
        //link parent of current node to its right child
        if (parent_curr -> left == curr) {
            parent_curr -> left = curr -> right;
        }
        else {
            parent_curr -> right = curr -> right;
        }
        //Need to readjust balance of parent_curr
        *curr = (BSTNode) {.key = key, .left = NULL, .right = NULL, .balance = 0}; 
        free(curr); 
    } 
}

void copy(BSTNode* target, BSTNode* source) {
    target -> key = source -> key; 
}

void make_balanced_i (BSTNode** root, int key, BSTNode* curr, BSTNode* youngest_ancestor, BSTNode* parent_ya) {
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
}

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

// Calculates the balance of any given node
int calc_balance(BSTNode* nd) {
    if (nd == NULL) {
        return 0; 
    }

    return calc_height(nd -> left) - calc_height(nd -> right); 
}

// Calculates the height of any given node
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

// Pre-order printing
void print_tree(BSTNode* nd) {
    if (nd != NULL) {
        printf("%d %d %d\n", nd -> key, branch_code(nd), nd -> balance);
        print_tree(nd -> left); 
        print_tree(nd -> right); 
    }
}

void destroy_tree(BSTNode* root) {
    if (root == NULL) {
        return;
    }

    destroy_tree(root -> left); 
    destroy_tree(root -> right);
    *root = (BSTNode) {.key = 0, .left = NULL, .right = NULL, .balance = 0}; 
    free(root);
} 
