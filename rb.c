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

//verifica se nó parâmetro é filho esquerdo, NAO E CERTO DE FUNCIONAR PARA O DIREITO
int isLeftSon(node* root){
    return root->father && root == root->father->left;
}

int isRoot(node* root){return !root->father;}

node* grandFather(node* root){return root->father->father;}

node* uncle(node *root){
    //se o pai e filho esquerdo retorna filho direito do avô
    if(isLeftSon(root->father)) return grandFather(root)->right;
    else return grandFather(root)->left;
    return ;
}

enum color nodeColor(node* root){
    if(root) return root->color;
    else return BLACK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//funçoes auxiliares acima

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

//recebe o avô do nó
void rotateRight(node** trueRoot, node* root){
    node *a = root, *b = root->left, *c = b->right;

    b->father = a->father;
}
//função recolorir
void hotfix(node** trueRoot, node *root){

    //rotações
    if(nodeColor(uncle(root)) == BLACK){

        //rotações à esquerda
        if(isLeftSon(root->father)){
            //caso simples
            if(isLeftSon(root)){
                 
            }
        }
    }

    else{//recoloração
        //cores do pai e tio viram preta
        root->father->color = BLACK;
        uncle(root)->color = BLACK;
        
        //recolore avô
        root->father->father = RED;
        hotfix(root->father->father);
    }
}
