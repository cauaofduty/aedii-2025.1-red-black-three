#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

//declaração do ponteiro sentinela para tornar seguras as checagens de null ao decorrer do código (nós nulos devem ser tratados como pretos)
node Ward;
node* ward = &Ward; 

node doubleBlack;
node* db = &doubleBlack;

void bootstrap(){//inicializa o ponteiro sentinela e o no db no inicio do programa
    ward->color = BLACK;
    ward->father = ward;
    ward->left = ward;
    ward->right = ward;

    db->color = DOUBLE_BLACK;
    db->father = ward;
    db->left = ward;
    db->right = ward;
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

//testar
int sucessor(node *root){

    if(root == ward) return -1;

    int suc = sucessor(root->right);

    if(suc != -1) return suc;

    else return root->value;
}

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

//função que resolve problema do duplo preto
removeHotfix(node **trueRoot, node* db){
    if(nodeColor(db) == DOUBLE_BLACK){//garante que so vai fazer alterações em duplo preto
        //caso ii)(ambos lados) rotação para o lado do duplo preto e recoloração de irmão -> black, pai -> red (logo antes)
        if(color(db->father) == BLACK &&//pai preto
        (brother(db)) == RED &&  //irmao vermelho
        color(brother(db)->left) == BLACK &&//sobrinhos pretos
        color(brother(db)->right) == BLACK){

            //guarda referência para o pai
            node* auxFather = db->father;

            //faz recolorações
            brother(db)->color = BLACK;
            db->father->color = RED;

            //realiza rotações no pai do duplo preto
            if(isLeftSon(db))  leftRotate(trueRoot, auxFather);
            
            else rightRotate(trueRoot, auxFather);
            
            removeHotfix(trueRoot, db);
            return;
        }
        //caso iii)irmão ,pai e sobrinhos de db pretos
        else if((color(db->father) == BLACK &&//pai preto
        (brother(db)) == BLACK &&  //irmao preto
        color(brother(db)->left) == BLACK &&//sobrinhos pretos
        color(brother(db)->right) == BLACK)){

            //recolore irmão p/vermelho, pai para duplo-preto e db para preto
            brother(db)->color = RED;
            db->color = BLACK;
            db->father->color = DOUBLE_BLACK;
            
            removeHotfix(trueRoot, db->father);
            return;
        }
        //caso iv)pai vermelho, irmão e sobrinhos pretos -> recoloração e remoção duplo-preta
        else if((color(db->father) == RED &&//pai vermelho
        (brother(db)) == BLACK &&  //irmao preto
        color(brother(db)->left) == BLACK &&//sobrinhos pretos
        color(brother(db)->right) == BLACK)){
            //recolore pai p/preto, irmão p/vermelho e duplo-preto pra preto
            db->father->color = BLACK;
            brother(db)->color = RED;
            db->color = BLACK;
            return;
        }
        //caso v-i) pai roxo , irmão preto, sobrinho prox ao eixo de simetria vermelho e outro irmão preto
        else if((brother(db)) == BLACK &&  //irmao preto
        color(brother(db)->left) == RED &&//sobrinho esquerdo vermelho
        color(brother(db)->right) == BLACK){//sobrinho direito preto
            //recolorindo antes de rotacionar irmão para vermelho e sobrinho perto do eixo para preto (novo pai na rotação)
            brother(db)->color = RED;
            brother(db)->left->color = BLACK;
            rightRotate(trueRoot, brother(db));//rotação "para fora" do eixo de simetria
            removeHotfix(trueRoot, db);
            return;
    }
    //caso v-ii) simetrico
        else if((brother(db)) == BLACK &&  //irmao preto
        color(brother(db)->left) == BLACK &&//sobrinho esquerdo preto
        color(brother(db)->right) == RED){//sobrinho direito vermelho
            //recolorindo antes de rotacionar irmão para vermelho e sobrinho perto do eixo para preto (novo pai na rotação)
            brother(db)->color = RED;
            brother(db)->right->color = BLACK;
            leftRotate(trueRoot, brother(db));

            removeHotfix(trueRoot, db);
            return;
    }
    //caso vi-i) pai e sobrinho perto do eixo de simetria roxos, irmão preto e sobrinho de fora do eixo vermelho
    else if((brother(db)) == BLACK &&  //irmao preto
        color(brother(db)->right) == RED){//sobrinho direito vermelho

            //faz recolorações devidamente antes da rotação e no duplo-preto se torna preto
            brother(db)->color = db->father->color;
            db->father->color = BLACK;
            brother(db)->right->color = BLACK;
            db->color = BLACK;

            leftRotate(trueRoot, db->father);
            return;
        }
        //caso vi-ii) simétrico
    else if((brother(db)) == BLACK &&  //irmao preto
        color(brother(db)->left) == RED){//sobrinho esquerdo vermelho

            //faz recolorações devidamente antes da rotação e no duplo-preto se torna preto
            brother(db)->color = db->father->color;
            db->father->color = BLACK;
            brother(db)->left->color = BLACK;
            db->color = BLACK;

            leftRotate(trueRoot, db->father);
            return;
        }
    else printf("erro, esta funcao so deve ser chamada em no duplo-preto\n");
    
    }
}

void removeNode(node** trueRoot, int value){

    node* target = *trueRoot; 

    while (target != ward){
        //valor encontrado
        if(target->value == value){
            //casos onde o target não possui filhos 
            if(target->left == ward && target->right == ward){
                //e é raiz
                if(isRoot(target)){
                    *trueRoot = ward; 
                }
                //ou é vermelho
                else if(nodeColor(target) == RED){
                    if(isLeftSon(target)) target->father->left = ward;
                    else target->father->right = ward;
                } 
                //ou é preto
                else{
                    //atualiza pai de db
                    db->color = DOUBLE_BLACK;
                    db->father = target->father;

                    //atualiza respectivo filho do pai de target para ser db 
                    if(isLeftSon(target)) target->father->left = db;

                    else target->father->right = db; 

                    //realiza correção com função de hotfix apropriada
                    removeHotfix(trueRoot, db);
                }
            }
            //caso apenas um filho esquerdo
            else if(target->left != ward && target->right == ward ){

                //caso raiz, substitui pelo filho
                if(isRoot(target)){
                    *trueRoot = target->left; //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>RAIZ PODERIA SAIR DAQUI DIFERENTE DE PRETA?
                    (*trueRoot)->color = BLACK;//sou inseguro
                }
             

                //do contrario faz substituição cabível
                else if(isLeftSon(target)) target->father->left = target->left;
                
                else target->father->right = target->left;
            }
            //caso apenas um filho direito
            else if(target->left == ward && target->right != ward ){
                
                //caso raiz, substitui pelo filho
                if(isRoot(target)){
                    *trueRoot = target->right;
                    (*trueRoot)->color = BLACK;//sou inseguro
                }    

                //do contrario faz substituição cabível
                else if(isLeftSon(target)) target->father->left = target->right;
                
                else target->father->right = target->right;
            }
            //caso ambos filhos não nulos
            else {
                //substitui valor de target por sucessor da esquerda
                target->value = sucessor(target->left);
                removeNode(trueRoot, target->value);
                break;
            }
            //ponto centralizado que libera a memoria de no removido
            free(target);
            break;
        }
        //itera na árvore
        else if(value > target->value) target = target->right;

        else target = target->left;

    }
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