#define FORMAT '='

typedef struct node{
    int factor; // fator de balanceamento do nodo
    struct node *left, *right; // filho esquerdo e direito respectivamente
    char *word, *lemma; // palavra e lema respectivamente
}node_t;

//int global = 0;

// Inicializa uma ABP/AVL
node_t *initialize();
// Insere um novo nodo na AVL
node_t *insertAVL(node_t *root, int *inserted, char *word, char *lemma);
// Procura uma palavra em uma ABP/AVL e retorno o nodo caso exista
node_t *query(node_t *root, const char *word);
node_t *simpleRoR(node_t *root);
// Rotação Simples à esquerda (--) - nodo com fator negativo e sub-arvore à direita com fator negativo
node_t *simpleRoL(node_t *root);
// Rotação Dupla à direita (+-) - nodo com fator positivo e sub-arvore à esquerda com fator negativo
node_t *doubleRoR(node_t *root);
// Rotação Dupla à esquerda (-+) - nodo com fator negativo e sub-arvore à esquerda com fator positivo
node_t *doubleRoL(node_t *root);
// Função que conta as comparações feitas na comparação
//      - Se flag, então imprime o numero de comparações
void counterCmp(int flag);
// Função que conta as comparações feitas na inserção
//      - Se flag, então imprime o numero de inserções
void counterIns(int flag);
