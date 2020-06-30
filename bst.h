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
    int balance;
} BSTNode; 


BSTNode* create_node(int key); 
bool insert(BSTNode** root, int key); 
bool delete(BSTNode** root, int key); 
void detach_node(BSTNode* curr, BSTNode* parent_curr, int key);
void copy(BSTNode* target, BSTNode* source);
void make_balanced (BSTNode** root, int key, BSTNode* curr, BSTNode* youngest_ancestor, BSTNode* parent_ya);
void right_rotate(BSTNode** nd); 
void left_rotate(BSTNode** nd);
int calc_balance(BSTNode* nd); 
int calc_height(BSTNode* nd); 
int is_bst(BSTNode* nd, int output_code);
int is_balanced(BSTNode* nd, int output_code);
void print_tree(BSTNode* nd); 
void destroy_tree(BSTNode* root); 

#endif // BST_H