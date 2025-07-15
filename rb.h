#ifndef RB_H
#define RB_H

#include <stdio.h>
#include <stdlib.h>

enum color {RED, BLACK, DOUBLE_BLACK};

typedef struct node{
    int value;
    enum color color;
    struct node* father;
    struct node* left;
    struct node* right;
}node;

extern node* ward;
extern node* db;

void bootstrap();
void insert(node** root, int value);
void removeNode(node** trueRoot, node* root, int value); 
void preOrder(node* root);
#endif