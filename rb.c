#include <stdio.h>
#include <stdlib.h>
#include "rb.h"


node *createNode(int value){

    node* newNode = (node*)malloc(sizeof(node));

    if(newNode){
        newNode->value = value;
        newNode->color = RED;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    printf("Erro de alocação de memoria\n");
    return newNode;
}


void insert(node **root, int value){
    node* auxFather, *auxRoot = *root, *newNode = createNode(value);;

    while(auxRoot){
        auxFather = auxRoot;

        if(value < auxRoot->value) auxRoot = auxRoot->left;

        else auxRoot = auxRoot->right;
        
    }
    //chegou no fim
    if(auxFather == NULL) *root = newNode;
    
    else if(auxFather->value > value) {

        auxFather->left = newNode;
        auxRoot->father = auxFather;
        
    }

    else{
        auxFather->right = newNode;
        auxRoot->father = auxFather;
    } 

    
    //balance(auxRoot);

    //recolor() -> função tio e avo e filho esquerdo

    //colore a cor da raiz de preto
    (*root)->color = BLACK; 
    
}
//procurar os casos de rotação & recoloração na inserção

//verifica se nó parâmetro é filho esquerdo, negação funcionando para filho direito
int isLeftSon(node* root){return root == root->father->left;}

node* grandFather(node* root){return root->father->father;}

//deve ter avo obrigatoriamente?
node* uncle(node *root){
    if(isLeftSon(root->father)) return grandFather(root)->right;
    else return grandFather(root)->left;
    return ;
}

enum color nodeColor(node* root){
    if(root) return root->color;
    else return BLACK;
}
