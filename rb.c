#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

//declaração do ponteiro sentinela para tornar seguras as checagens de null ao decorrer do código (nós nulos devem ser tratados como pretos)
node Ward;
node* ward = &Ward; 

void bootstrap(){//inicializa o ponteiro sentinela no inicio do programa
    ward->color = BLACK;
    ward->father = ward;
    ward->left = ward;
    ward->right = ward;
}
node *createNode(int value){

    node* newNode = (node*)malloc(sizeof(node));

    if(newNode){
        newNode->value = value;
        newNode->color = RED;
        newNode->left = ward;
        newNode->right = ward;

        return newNode;
    }

    printf("Erro de alocação de memoria\n");
    return newNode;
}


//verifica se nó parâmetro é filho esquerdo, NAO E CERTO DE FUNCIONAR PARA O DIREITO
int isLeftSon(node* root){
    return root == root->father->left;
}

int isRoot(node* root){return root->father == ward;}

node* grandFather(node* root){return root->father->father;}

node* uncle(node *root){
    //se o pai e filho esquerdo retorna filho direito do avô
    if(isLeftSon(root->father)) return grandFather(root)->right;
    else return grandFather(root)->left;
}

node *brother(node* root){
    if(isLeftSon(root)) return root->father->right;
    else return root->father->left;
}

enum color nodeColor(node* root){ return root->color;}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//funçoes auxiliares acima


void rightRotate(node** trueRoot, node* root){//raiz absoluta e avô como parâmetros
    node *a = root, *b = root->left, *d = b->right;
    
    //caso a seja a raiz absoluta 
    if(isRoot(a)) *trueRoot = b;
    
    else if(isLeftSon(a)) a->father->left = b;

    else a->father->right = b;
    
    //de todo jeito pai de b se torna antigo pai de a
    b->father = a->father;
    b->right = a;
    
    a->father = b;
    a->left = d;

    //se o filho direito de b não é a sentinela, o campo pai dele aponta para a
    if(d != ward) d->father = a;

}

void leftRotate(node** trueRoot, node* root){//raiz absoluta e avô como parâmetros
    node *a = root, *b = root->right, *d = b->left;
    
    //caso a seja a raiz absoluta 
    if(isRoot(a)) *trueRoot = b;
    
    else if(isLeftSon(a)) a->father->left = b;

    else a->father->right = b;
    
    //de todo jeito pai de b se torna antigo pai de a
    b->father = a->father;
    b->left = a;
    
    a->father = b;
    
    a->right = d;

    //se o filho direito de b não é a sentinela, o campo pai dele aponta para a
    if(d != ward) d->father = a;
}

//função reajustar
void hotfix(node** trueRoot, node *root){

    //se o pai e vermelho, precisa de uma correção
    if(nodeColor(root->father)  == RED){
        
        if(nodeColor(uncle(root)) == RED){//recoloração, tio vermelho
        //cores do pai e tio viram preta e do avo, vermelho
            root->father->color = BLACK;
            uncle(root)->color = BLACK;
            
            //recolore avô
            grandFather(root)->color = RED;

            //chama recoloração para o avô
            hotfix(trueRoot, grandFather(root));

        } else {//rotações,tio preto >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DUVIDAS SOBRE PONTEIROS AQUI
            //rotações à direita
            if(isLeftSon(root->father)){
                //caso duplo
                if(!isLeftSon(root)){
                    //atualiza raiz relativa para o pivô
                    root = root->father;
                    leftRotate(trueRoot, root);
                    
                }
                //caso simples acontece direto
                //recoloração
                root->father->color = BLACK;
                grandFather(root)->color = RED;

                rightRotate(trueRoot, grandFather(root));//rotação esquerda em b

            } else {//caso de rotação à esquerda
                //verifica se e caso duplo
                if(isLeftSon(root)){
                    //atualiza root para apontar para o pivo
                    root = root->father;
                    rightRotate(trueRoot, root);
                }
                //caso simples
                root->father->color = BLACK;
                grandFather(root)->color = RED;

                leftRotate(trueRoot, grandFather(root));
            }

        }
    } 
}

void insert(node **root, int value){
    node* auxFather = ward, *auxRoot = *root, *newNode = createNode(value);

    while(auxRoot != ward){
        auxFather = auxRoot;
        
        //impede a adição de nó com valor repetido
        if(value == auxRoot->value) return;

        if(value < auxRoot->value) auxRoot = auxRoot->left;

        else auxRoot = auxRoot->right;
        
    }
    //caso de raiz nula
    if(auxFather == ward) {
        *root = newNode;
        newNode->father = ward;
    }
    //caso de inserção como filho esquerdo
    else if(auxFather->value > value) {

        auxFather->left = newNode;
        newNode->father = auxFather;
        
    } 
    //caso de inserção como filho direito
    else {

        auxFather->right = newNode;
        newNode->father = auxFather;
    } 

    hotfix(root, newNode);

    //garante raiz absoluta preta
    (*root)->color = BLACK;
    
}

void preOrder(node* root){
    
    if(root == ward) return;

    
    printf("[%d - ", root->value, root->color);

    switch(root->color){
        case RED: 
            printf("RED] ");
            break;
        case BLACK: 
            printf("BLACK] ");
            break;
        case DOUBLE_BLACK: 
            printf("DOUBLE BLACK] ");
            break;
    }

    preOrder(root->left);

    preOrder(root->right);
    
}