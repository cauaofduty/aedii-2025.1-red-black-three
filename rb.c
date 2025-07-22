#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

//declaração do ponteiro sentinela para tornar seguras as checagens de null ao decorrer do código (nós nulos devem ser tratados como pretos)
node Ward;
node* ward = &Ward; 

node doubleBlack;
node* db = &doubleBlack;


void igniteDoubleBlack(){
    
    db->value = -2;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<DEBUG

    db->color = DOUBLE_BLACK;
    db->father = ward;
    db->left = ward;
    db->right = ward;

}
void igniteWard(){
    ward->value = -1;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<DEBUG 
    
    ward->color = BLACK;
    ward->father = ward;
    ward->left = ward;
    ward->right = ward;

}

//SRP kk
void bootstrap(){//inicializa o ponteiro sentinela e o no db no inicio do programa
    igniteWard();
    igniteDoubleBlack();
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

        } else {//rotações,tio preto
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

//desconecta o duplo preto da arvore (faz ignite de novo)
void removeDoubleBlack(){
    //atualiza pais
    if (isLeftSon(db)) db->father->left = ward;
    
    else db->father->right = ward;
    
    igniteDoubleBlack();
}

//função que resolve problema do duplo preto
void removeHotfix(node **trueRoot, node* db){
    

    
    if(nodeColor(db) == DOUBLE_BLACK){//garante que so vai fazer alterações em duplo preto
        //caso i- raiz
        if(isRoot(db)) {
            printf("caso oi, sim ele e util.\n");
            db->color = BLACK;
        }
        //caso ii)(ambos lados) rotação para o lado do duplo preto e recoloração de irmão -> black, pai -> red (logo antes)
        else if(nodeColor(db->father) == BLACK &&//pai preto
        nodeColor(brother(db)) == RED &&  //irmao vermelho
        nodeColor(brother(db)->left) == BLACK &&//sobrinhos pretos
        nodeColor(brother(db)->right) == BLACK){
            printf("passou no hotfix remove caso ii\n");//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEBUG
            //guarda referência para o pai
            node* auxFather = db->father;

            //faz recolorações
            brother(db)->color = BLACK;
            db->father->color = RED;

            //realiza rotações no pai do duplo preto
            if(isLeftSon(db))  leftRotate(trueRoot, auxFather);
            
            else rightRotate(trueRoot, auxFather);
            
            removeHotfix(trueRoot, db);
        }
        //caso iii)irmão ,pai e sobrinhos de db pretos
        else if((nodeColor(db->father) == BLACK &&//pai preto
        nodeColor(brother(db)) == BLACK &&  //irmao preto
        nodeColor(brother(db)->left) == BLACK &&//sobrinhos pretos
        nodeColor(brother(db)->right) == BLACK)){
            printf("passou no hotfix remove caso iii\n");//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEBUG
            //recolore irmão p/vermelho, pai para duplo-preto e db para preto (removido)
            brother(db)->color = RED;
            db->color = BLACK;
            db->father->color = DOUBLE_BLACK;

            removeHotfix(trueRoot, db->father);
            removeDoubleBlack();
        }
        //caso iv)pai vermelho, irmão e sobrinhos pretos -> recoloração e remoção duplo-preta
        else if((nodeColor(db->father) == RED &&//pai vermelho
        nodeColor(brother(db)) == BLACK &&  //irmao preto
        nodeColor(brother(db)->left) == BLACK &&//sobrinhos pretos
        nodeColor(brother(db)->right) == BLACK)){
            printf("passou no hotfix remove caso iv\n");//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEBUG

            //recolore pai p/preto, irmão p/vermelho e duplo-preto pra preto, removendo-o
            db->father->color = BLACK;
            brother(db)->color = RED;
            removeDoubleBlack();
        }
        //caso v-i) pai roxo , irmão preto, sobrinho prox ao eixo de simetria vermelho e outro irmão preto
        else if(isLeftSon(db) && nodeColor(brother(db)) == BLACK &&  //irmao preto
        nodeColor(brother(db)->left) == RED &&//sobrinho esquerdo vermelho
        nodeColor(brother(db)->right) == BLACK){//sobrinho direito preto
            printf("passou no hotfix remove caso v-i\n");//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEBUG
            //recolorindo antes de rotacionar irmão para vermelho e sobrinho perto do eixo para preto (novo pai na rotação)
            brother(db)->color = RED;
            brother(db)->left->color = BLACK;
            rightRotate(trueRoot, brother(db));//rotação "para fora" do eixo de simetria
            removeHotfix(trueRoot, db);
    }
    //caso v-ii) simetrico
        else if(!isLeftSon(db) && nodeColor(brother(db)) == BLACK &&  //irmao preto
        nodeColor(brother(db)->left) == BLACK &&//sobrinho esquerdo preto
        nodeColor(brother(db)->right) == RED){//sobrinho direito vermelho
            printf("passou no hotfix remove caso v-ii\n");//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEBUG
            //recolorindo antes de rotacionar irmão para vermelho e sobrinho perto do eixo para preto (novo pai na rotação)
            brother(db)->color = RED;
            brother(db)->right->color = BLACK;
            leftRotate(trueRoot, brother(db));
            removeHotfix(trueRoot, db);
    }
    //caso vi-i) pai e sobrinho perto do eixo de simetria roxos, irmão preto e sobrinho de fora do eixo vermelho
    else if(isLeftSon(db) && nodeColor(brother(db)) == BLACK &&  //irmao preto
        nodeColor(brother(db)->right) == RED){//sobrinho direito vermelho
            printf("passou no hotfix remove caso vi-i\n");//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEBUG

            //faz recolorações devidamente antes da rotação e no duplo-preto se torna preto (removido)
            brother(db)->color = db->father->color;
            db->father->color = BLACK;
            brother(db)->right->color = BLACK;
            
            leftRotate(trueRoot, db->father);
            removeDoubleBlack();
        }
        //caso vi-ii) simétrico
    else if(!isLeftSon(db) && nodeColor(brother(db)) == BLACK &&  //irmao preto
        nodeColor(brother(db)->left) == RED){//sobrinho esquerdo vermelho
            printf("passou no hotfix remove caso vi-ii\n");//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEBUG
            //chegou
            printf("chegou\n");
            //faz recolorações devidamente antes da rotação e no duplo-preto se torna preto
            brother(db)->color = db->father->color;
            db->father->color = BLACK;
            brother(db)->left->color = BLACK;
            
            rightRotate(trueRoot, db->father);
            removeDoubleBlack();
        }
    }
}
//adicionei raiz relativa para poder usar a função recursivamente 
void removeNode(node** trueRoot,node* root, int value){
    //para minimizar gargalos, recebe o no por onde começar a procurar (conteudo da raiz absoluta por default)
    node* target = root; 

    while (target->value != value){
        //itera na árvore
        if(target == ward) break;
        if(value > target->value) target = target->right;

        else target = target->left;
    }
    if(target == ward) {//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEBUG
        printf("valor %d nao encontrado\n", value);
        return;
    }

    //valor encontrado
    if(target->value == value){
        //casos onde o target não possui filhos 
        if(target->left == ward && target->right == ward){
            //e é raiz
            if(isRoot(target)){//isso elimina a necessidade da verificação duplo preta na raiz.
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
                db->father = target->father;
                db->color = DOUBLE_BLACK;

                //atualiza respectivo filho do pai de target para ser db 
                if(isLeftSon(target)) target->father->left = db;

                else target->father->right = db; 

                //realiza correção com função de hotfix apropriada
                removeHotfix(trueRoot, db);
            }
            //libera no
            free(target);
        }
        //caso apenas um filho esquerdo
        else if(target->left != ward && target->right == ward ){

            //caso raiz, substitui pelo filho
            if(isRoot(target)) *trueRoot = target->left; 
            
            //copia valor do no filho e remove-o na subarvore
            target->value = target->left->value;
            removeNode(trueRoot, target->left ,target->value);
            return;
            
        }
        //caso apenas um filho direito
        else if(target->left == ward && target->right != ward ){
            
            //caso raiz, substitui pelo filho
            if(isRoot(target)) *trueRoot = target->right;
                
            //copia valor do no filho e remove-o na subarvore
            target->value = target->right->value;
            removeNode(trueRoot, target->right ,target->value);
            return;
        }
        //caso ambos filhos não nulos
        else {
            //substitui valor de target por sucessor da esquerda
            target->value = sucessor(target->left);
            removeNode(trueRoot, target->left, target->value);
            return;
        }

    }
}

void preOrder(node* root){
    
    if(root == ward) return;

    
    printf("[%d ", root->value, root->color);

    switch(root->color){
        case RED: 
            printf("R]");
            break;
        case BLACK: 
            printf("B]");
            break;
        case DOUBLE_BLACK: //para debug
            printf("DB]");
            break;
    }
    

    preOrder(root->left);

    preOrder(root->right);
    
}