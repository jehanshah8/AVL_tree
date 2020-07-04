#include "bst.h"
#include "helpers.h"

// Allocates memeory for a new node and initializes it
BSTNode *create_node(int key)
{
    BSTNode *nd = malloc(sizeof(*nd));
    if (nd == NULL)
    {
        printf("MEMORY ERROR: Failed to allocate memory for new node\n");
        return NULL;
    }
    *nd = (BSTNode){.key = key, .left = NULL, .right = NULL, .height = 0};
    //printf("Node created successfully\n");
    return nd;
}

BSTNode *insert(BSTNode *root, int key)
{
    if (root == NULL)
    {
        return create_node(key);
    }

    if (key <= root->key)
    { //less than or equal to so that duplicates always go left
        root->left = insert(root->left, key);
    }
    else
    {
        root->right = insert(root->right, key);
    }

    set_height(&root);

    int balance = get_balance(root);

    //tallest child is left child
    if (balance > 1 && key <= root->left->key)
    {
        //printf("right\n");
        return right_rotate(root);
    }

    //tallest child is right child
    if (balance < -1 && key > root->right->key)
    {
        //printf("left\n");
        return left_rotate(root);
    }

    //balance in opp direction
    if (balance > 1 && key > root->left->key)
    {
        //printf("left, then right\n");
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    //balance in opp direction
    if (balance < -1 && key <= root->right->key)
    {
        //printf("right, then left\n");
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

bool delete (BSTNode **root, BSTNode **parent, int key)
{
    if (*root == NULL)
    {
        return true;
    }

    if (key == (*root)->key)
    {
        detach_node(root, parent, key);
    }
    else if (key < (*root)->key)
    {
        delete (&(*root)->left, root, key);
    }
    else if (key > (*root)->key)
    {
        delete (&(*root)->right, root, key);
    }

    if (*root == NULL)
    {
        return true;
    }

    set_height(root);
    int balance = get_balance(*root);

    // Left heavy => rotate right
    if (balance > 1 && get_balance((*root)->left) >= 0)
    {
        *root = right_rotate(*root);
        return true;
    }

    // Right heavy => rotate left
    if (balance < -1 && get_balance((*root)->right) <= 0)
    {
        *root = left_rotate(*root);
        return true;
    }

    // If both the youngest ancestor and the child are unbalanced in OPPOSITE directions
    // Left rotate then, right rotate
    if (balance > 1 && get_balance((*root)->left) < 0)
    {
        (*root)->left = left_rotate((*root)->left);
        *root = right_rotate(*root);
        return true;
    }

    // Right rotate then, left rotate
    if (balance < -1 && get_balance((*root)->right) > 0)
    {
        (*root)->right = right_rotate((*root)->right);
        *root = left_rotate(*root);
        return true;
    }

    return true;
}

void detach_node(BSTNode **root, BSTNode **parent, int key)
{
    if ((*root)->left == NULL && (*root)->right == NULL)
    {
        //printf("target node has no children\n");
        if (*parent != NULL)
        {
            if ((*parent)->left == (*root))
            {
                (*parent)->left = NULL;
            }
            else
            {
                (*parent)->right = NULL;
            }
        }
        BSTNode *temp = *root;
        *root = NULL;
        free(temp);
    }
    else if ((*root)->left != NULL && (*root)->right != NULL)
    {
        //printf("target node has 2 children\n");
        // find immidiate predecessor by going left once and then keep going right
        BSTNode *parent_temp = (*root);
        BSTNode *temp = (*root)->left;

        while (temp->right != NULL)
        {
            parent_temp = temp;
            temp = temp->right;
        } // while the predecessor isn't found

        // copy key
        (*root)->key = temp->key;

        // Delete the inorder predecessor
        delete (&temp, &parent_temp, temp->key);
    }
    else if ((*root)->left != NULL)
    {
        //printf("target node has only left child\n");
        //link parent of current node to its left child
        if (*parent != NULL)
        {
            if ((*parent)->left == (*root))
            {
                (*parent)->left = (*root)->left;
            }
            else
            {
                (*parent)->right = (*root)->left;
            }
        }
        BSTNode *temp = *root;
        *root = NULL;
        free(temp);
    }
    // only right child
    else if ((*root)->right != NULL)
    {
        //printf("target node has only right child\n");
        //link parent of current node to its right child
        if (*parent != NULL)
        {
            if ((*parent)->left == (*root))
            {
                (*parent)->left = (*root)->right;
            }
            else
            {
                (*parent)->right = (*root)->right;
            }
        }
        BSTNode *temp = *root;
        *root = NULL;
        free(temp);
    }
}

int max(int left, int right)
{
    if (left >= right)
    {
        //printf("key = %d, left height = %d\n", nd -> key, left);
        return left;
    }
    else
    {
        //printf("key = %d, right height = %d\n", nd -> key, right);
        return right;
    }
}

// Made to avoid keep chekcing for NULL and reduce chances of seg fault
// Also helps in case I want to stop using heigth as an attribute
int get_height(BSTNode *nd)
{
    if (nd == NULL)
    {
        return -1;
    }

    return nd->height;
}

void set_height(BSTNode **nd)
{
    if (*nd == NULL)
    {
        return;
    }

    (*nd)->height = max(get_height((*nd)->left), get_height((*nd)->right)) + 1;
}

// Calculates the balance of any given node
int get_balance(BSTNode *nd)
{
    if (nd == NULL)
    {
        return 0;
    }

    return get_height(nd->left) - get_height(nd->right);
}

BSTNode *right_rotate(BSTNode *root)
{
    BSTNode *new_root = root->left;
    BSTNode *temp = new_root->right;

    new_root->right = root;
    root->left = temp;

    set_height(&root);
    set_height(&new_root);

    return new_root;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
BSTNode *left_rotate(BSTNode *root)
{
    BSTNode *new_root = root->right;
    BSTNode *temp = new_root->left;

    new_root->left = root;
    root->right = temp;

    set_height(&root);
    set_height(&new_root);

    return new_root;
}

int is_bst(BSTNode *nd, int output_code)
{
    if (nd == NULL)
    {
        return output_code;
    }

    if (output_code == 00)
    {
        return output_code;
    }

    if (nd->left != NULL)
    {
        if (nd->key < nd->left->key)
        {
            // not bst
            //printf("key = %d, left -> key = %d\n", nd -> key, nd -> left -> key);
            return 00;
        }
        else
        {
            output_code = is_bst(nd->left, output_code);
        }
    }

    if (nd->right != NULL)
    {
        if (nd->key > nd->right->key)
        {
            // not bst
            //printf("key = %d, right -> key = %d\n", nd -> key, nd -> right -> key);
            return 00;
        }
        else
        {
            output_code = is_bst(nd->right, output_code);
        }
    }

    return output_code;
}

int is_balanced(BSTNode *nd, int output_code)
{
    if (nd == NULL)
    {
        return output_code;
    }

    if (output_code == 0)
    {
        return output_code;
    }

    if (nd->left != NULL)
    {
        if (get_balance(nd) >= 2 || get_balance(nd) <= -2)
        {
            // Not balanced
            //printf("key = %d\n", nd -> key);
            return 0;
        }
        else
        {
            output_code = is_balanced(nd->left, output_code);
        }
    }

    if (nd->right != NULL)
    {
        if (get_balance(nd) >= 2 || get_balance(nd) <= -2)
        {
            // Not balanced
            //printf("key = %d\n", nd -> key);
            return 0;
        }
        else
        {
            output_code = is_balanced(nd->right, output_code);
        }
    }
    return output_code;
}

// Pre-order printing
void print_tree(BSTNode *nd)
{
    if (nd != NULL)
    {
        printf("%d %d\n", nd->key, branch_code(nd));
        print_tree(nd->left);
        print_tree(nd->right);
    }
}

// Free entire tree
void destroy_tree(BSTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    destroy_tree(root->left);
    destroy_tree(root->right);
    *root = (BSTNode){.key = 0, .left = NULL, .right = NULL, .height = -1};
    free(root);
}
