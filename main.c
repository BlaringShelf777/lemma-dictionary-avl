#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl.h" // AVL_TAD

#define ARGS 4 // Numero de argumentos esperados
#define READ 2000 // Comprimento da linha

int main(int argc, char *argv[]){
    clock_t start_t, end_t, dicEnd_t, txtStart_t; // Variaveis de controle do tempo
    FILE *inputFile, *outputFile, *dictionaryFile; // Arquivos in, out e dicionario
    char *word, *lemma; // Palavra e Lema
    char line[READ], tokens[]= {" ,_-——.&*%\?!;/'@\"$#=><()][}{:\n\t"}; // Linha e tokens
    node_t *avlRoot = initialize(); // Raiz da AVL
    int inserted = 0; // Flag de inserção da AVL
    unsigned long long wordsTxt = 0, wordsDict = 0; // Numero de palavras no texto e dicionario

    // Confere se o numero parametros esta correto
    if (argc != ARGS){
        printf ("ERROR! Numero incorreto de parametros.\nPara chamar o programa digite: exemplo <arq_dicionario> <arq_entrada> <arq_saida>\n");
        return 1;
    }
    // Abre o arquivo do dicionario de nome/endereço argv[1]
    dictionaryFile = fopen(argv[1], "r");
    if (!dictionaryFile){
        printf ("Error! Arquivo %s nao encontrado.\n",argv[1]);
        return 2;
    }
    // Abre o arquivo de entrada de nome/endereço argv[2]
    inputFile = fopen (argv[2], "r");
    if (!inputFile){
        fclose(dictionaryFile);
        printf ("Error! Arquivo %s nao encontrado.\n",argv[2]);
        return 3;
    }
    //inicia a contagem do tempo
    start_t = clock();
    // Cria a AVL com as palavras e lemas do dicionario
    while(fgets(line, READ, dictionaryFile)){
        inserted = 0;
        word = strtok(line, tokens);
        lemma = strtok(NULL, tokens);
        avlRoot = insertAVL(avlRoot, &inserted, word, lemma);
        wordsDict++;
    }
    // Fecha arquivo do dicionario
    fclose(dictionaryFile);
    // Terminou o tempo de criação do deque
    dicEnd_t = clock();
    // Inicia o tempo de criação do arquivo de saida
    txtStart_t = clock();
    // cria o arquivo de saida
    outputFile = fopen (argv[3], "w");
    //percorre todo o arquivo lendo linha por linha
    while(fgets(line,READ,inputFile)){
        word = strtok (line, tokens);
        while(word){
            char *wordToLower = strlwr(word);
            node_t *aux = query(avlRoot, wordToLower);
            wordsTxt++;
            if (!aux)
                fprintf(outputFile,"%s ", wordToLower);
            else
                fprintf(outputFile,"%s ", aux->lemma);
            word = strtok (NULL, tokens);
        }
        fprintf(outputFile,"\n");
    }
    // Fecha os arquivos de entrada e saida
    fclose (inputFile); fclose (outputFile);
    printf("\nArquivo %s gerado com sucesso.\n\n", argv[3]);
    // Encerra a contagem
    end_t = clock();
    // Calcula e imprime o tempo de execução
    printf("Tempo de execucao total: %.5lf ms\n", (double)(end_t - start_t) / CLOCKS_PER_SEC * 1000);
    printf("Tempo de criacao da AVL: %.5lf ms\n", (double)(dicEnd_t - start_t) / CLOCKS_PER_SEC * 1000);
    printf("Tempo de criacao do arquivo %s: %.5lf ms\n\n", argv[3], (double)(end_t - txtStart_t) / CLOCKS_PER_SEC * 1000);
    //-- Numero de comparacoes
    counterIns(1);
    counterCmp(1);
    //-- Numero de palavras
    printf("\nPalavras no dicionario: %llu\nPalavras no Texto: %llu\n\n", wordsDict, wordsTxt);

    return 0;
}
