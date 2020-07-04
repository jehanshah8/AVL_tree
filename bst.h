#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h> 

typedef struct bstnode {
    int key; 
    struct bstnode* left; 
    struct bstnode* right;
    int height;
} BSTNode; 


BSTNode* create_node(int key); 
BSTNode* insert(BSTNode* root, int key);
void detach_node(BSTNode **root, BSTNode** parent, int key);
bool delete(BSTNode** root, BSTNode** parent, int key);
BSTNode* right_rotate(BSTNode* root); 
BSTNode* left_rotate(BSTNode* root);
int max(int n1, int n2);
int get_height(BSTNode* nd);
void set_height(BSTNode** nd); 
int get_balance(BSTNode* nd); 
int is_bst(BSTNode* nd, int output_code);
int is_balanced(BSTNode* nd, int output_code);
void print_tree(BSTNode* nd); 
void destroy_tree(BSTNode* root); 

#endif // BST_H