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

//apenas para garantir a criação do nó sentilena
extern node* ward;

void bootstrap();
void insert(node** root, int value);
void preOrder(node* root);
#endif