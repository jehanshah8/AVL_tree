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
} BSTNode; 

bool insert(BSTNode** nd, int key); 
bool delete(BSTNode** nd, int key); 
void balance (BSTNode** nd); 
bool is_balanced(BSTNode** nd); 
int calc_height(BSTNode** nd); 
void rotate_right(BSTNode** nd); 
void rotate_left(BSTNode** nd); 

#endif // BST_H