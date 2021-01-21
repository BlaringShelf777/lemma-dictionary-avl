#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"

node_t *initialize(){
    return NULL;
}

// Insere em uma AVL
node_t *insertAVL(node_t *root, int *inserted, char *word, char *lemma){
    counterIns(0); // Comparação com elemento da estrutura (if)
    if (!root){
        int lemmaSize = strlen(lemma);
        int wordSize = strlen(word);

        root = (node_t *) malloc(sizeof(node_t));
        root->factor = 0;
        root->left = root->right = NULL;
        root->word = (char *) malloc(wordSize + 1); strncpy(root->word, word, wordSize + 1);
        root->lemma = (char *) malloc(lemmaSize + 1); strncpy(root->lemma, lemma, lemmaSize + 1);
        *inserted = 1;

        return root;
    }
    int wordCmp = strcmp(word, root->word); // Comparação com elemento da estrutura (strcmp)

    if (wordCmp >= 1){
        root->right = insertAVL(root->right, inserted, word, lemma);
        if (*inserted)
            switch (root->factor){
                case 0:
                    root->factor = -1;
                break;
                case 1:
                    root->factor = *inserted = 0;
                break;

                case -1:
                    counterIns(0); // Comparação com elemento da estrutura (if)
                    if (root->right->factor == -1)
                        root = simpleRoL(root);
                    else
                        root = doubleRoL(root);
                    root->factor = *inserted = 0;
                break;
            }
    }else if (wordCmp <= -1){
        root->left = insertAVL(root->left, inserted, word, lemma);
        if (*inserted)
            switch(root->factor){
                case 0:
                    root->factor = 1;
                break;
                case -1:
                    root->factor = *inserted = 0;
                break;
                case 1:
                    counterIns(0); // Comparação com elemento da estrutura (if)
                    if (root->left->factor == 1)
                        root = simpleRoR(root);
                    else
                        root = doubleRoR(root);
                    root->factor = *inserted = 0;
                break;
            }
    }

    return root;
}

// Procura uma palavra em uma AVL
node_t *query(node_t *root, const char *word){
    while(root){
        counterCmp(0); // Comparação com elemento da estrutura
        if (strcmp(word, root->word) == 0){
            counterCmp(0); // Comparação com elemento da estrutura
            return root;
        }else{
            counterCmp(0); // Comparação com elemento da estrutura
            if (strcmp(word, root->word) > 0)
                root = root->right;
            else
                root = root->left;
        }
    }

    return NULL;
}

// ROTACOES:
// Rotação Simples à direita ++
node_t *simpleRoR(node_t *root){
    node_t *aux = root->left;

    root->left = aux->right;
    aux->right = root;
    root->factor = 0;
    root = aux;

    return root;
}
// Rotação Simples à esquerda --
node_t *simpleRoL(node_t *root){
    node_t *aux = root->right;

    root->right = aux->left;
    aux->left = root;
    root->factor = 0;
    root = aux;

    return root;
}
// Rotação Dupla à direita +-
node_t *doubleRoR(node_t *root){
    node_t *aux1 = root->left, *aux2 = aux1->right;

    aux1->right = aux2->left;
    aux2->left = aux1;
    root->left = aux2->right;
    aux2->right = root;
    root->factor = aux2->factor == 1 ? -1 : 0;
    aux1->factor = aux2->factor == -1 ? 1 : 0;
    root = aux2;

    return root;
}
// Rotação Dupla à esquerda -+
node_t *doubleRoL(node_t *root){
    node_t *aux1 = root->right, *aux2 = aux1->left;

    aux1->left = aux2->right;
    aux2->right = aux1;
    root->right = aux2->left;
    aux2->left = root;
    root->factor = aux2->factor == -1 ? 1 : 0;
    aux1->factor = aux2->factor == 1 ? -1: 0;
    root = aux2;

    return root;
}

// Conta cmp's
void counterCmp(int flag){
    static unsigned long long countCmp = 0;

    countCmp++;
    if(flag)
        printf("Numero de comparacoes na criacao do arquivo: %llu\n", --countCmp);
}

// Conta ins's
void counterIns(int flag){
    static unsigned long long countIns = 0;

    countIns++;
    if(flag)
        printf("Numero de comparacoes na insercao: %llu\n", --countIns);
}
