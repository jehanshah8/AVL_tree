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
bool delete(BSTNode* root, int key); 
/**
void make_balanced (BSTNode* nd); 
bool is_balanced(BSTNode* nd); 
int calc_balance(BSTNode* nd); 
int calc_height(BSTNode* nd); 
*/
void right_rotate(BSTNode** nd); 
void left_rotate(BSTNode** nd); 

#endif // BST_H