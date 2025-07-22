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

//funções auxiliares diversas
void preOrder(node* root);
void igniteWard();
void igniteDoubleBlack();
void removeDoubleBlack();
void bootstrap();
enum color nodeColor(node* root);

//funções auxiliares de nó
node* createNode(int value);
node* brother(node* root);
node* uncle(node* root);
node* grandFather(node* root);

//booleans
int isLeftSon(node* root);
int isRoot(node* root);

//funções estruturais
void insert(node** root, int value);
void hotfix(node** trueRoot, node *root);
void removeNode(node** trueRoot, node* root, int value); 
void removeHotfix(node** trueRoot, node *root);
void rightRotate(node** trueRoot, node* root);
void leftRotate(node** trueRoot, node* root);
#endif