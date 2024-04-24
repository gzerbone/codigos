#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* Definição da estrutura do nó da árvore */
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

/* Variáveis */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int nextToken;
FILE *in_fp;

int aceitacao;

/* Classes de caracteres */
#define LETRA 0
#define NUMERO 1
#define DESCONHECIDO 99

/* Códigos dos tokens */
#define INT_LIT 10
#define ID 11
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define PAREN_ESQ 25
#define PAREN_DIR 26
#define END_LINE 27

// FUNÇÕES
int lookup(char ch);
void addChar();
void getChar();
void getNonBlank();
int lex();

// Funções da análise sintática
Node* expr();
Node* term();
Node* factor();
void error(int valor);

/* Função para criar um novo nó da árvore */
Node* newNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Função para imprimir a árvore em pré-ordem e preencher a lista de produções */
void printPreOrder(Node* root) {
    if (root != NULL) {
        printf(" %d ", root->value); // Imprime o valor do nó
        printPreOrder(root->left); // Chama recursivamente para o filho esquerdo
        printPreOrder(root->right); // Chama recursivamente para o filho direito
    }
}

/*INÍCIO ANALISADOR LÉXICO*/

/*****************************************************/
/* lookup - uma função para procurar operadores e parênteses e retornar o token */
int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = PAREN_ESQ;
            break;
        case ')':
            addChar();
            nextToken = PAREN_DIR;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '$':
            addChar();
            nextToken = END_LINE;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - uma função para adicionar nextChar ao lexema */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Erro - lexema esta muito longo \n");
    }
}

/*****************************************************/
/* getChar - uma função para obter o próximo caractere de entrada e determinar sua
 * classe de caractere */
void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETRA;
        else if (isdigit(nextChar))
            charClass = NUMERO;
        else
            charClass = DESCONHECIDO;
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - uma funcao para chamar getChar ate que ele retorne um caractere que nao seja de espaco em branco
 */
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

/*****************************************************/
/* lex - um analisador lexico simples para expressoes aritmeticas */
int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        /* Analisar identificadores */
        case LETRA:
            addChar();
            getChar();
            while (charClass == LETRA || charClass == NUMERO) {
                addChar();
                getChar();
            }
            nextToken = ID;
            break;
        /* Analisar literais inteiros */
        case NUMERO:
            addChar();
            getChar();
            while (charClass == NUMERO) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
        /* ParEnteses e operadores */
        case DESCONHECIDO:
            lookup(nextChar);
            getChar();
            break;
        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* Fim do switch */

    printf("Proximo token e: %d -- Proximo lexema e: %s\n", nextToken, lexeme);
    return nextToken;
} /* Fim da função lex */
/*FIM ANALISADOR LÉXICO*/

/* Funções da análise sintática */

Node* expr() {
    Node* node = term();
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        int token = nextToken;
        lex();
        Node* newNode = malloc(sizeof(Node));
        newNode->value = token;
        newNode->left = node;
        newNode->right = term();
        node = newNode;
    }
    return node;
}

Node* term() {
    Node* node = factor();
    while (nextToken == MULT_OP || nextToken == DIV_OP) {
        int token = nextToken;
        lex();
        Node* newNode = malloc(sizeof(Node));
        newNode->value = token;
        newNode->left = node;
        newNode->right = factor();
        node = newNode;
    }
    return node;
}

Node* factor() {
    Node* node = NULL;
    if (nextToken == ID || nextToken == INT_LIT) {
        node = newNode(nextToken);
        lex();
    }    
    /* Se a RHS é (<expr>), chame lex para passar o parêntese 
    esquerdo, chame expr e verifique pelo parêntese 
    direito */
    else{
        if (nextToken == PAREN_ESQ) {
            lex();
            node = expr();
            if (nextToken == PAREN_DIR) {
                lex();
            } else {
                error(1);
            }
        } 
        else {
            error(2);
        }
    }
    return node;
}

void error(int valor){
    aceitacao = 1;
    switch (valor){
    case 1:
        printf("ERRO!!\nEXPLICACAO: Esperava um parentese direito \n");
        break;
    case 2:
        printf("\nERRO!!\n*EXPLICACAO* Nao era um id, um literal inteiro, ou um parentese esquerdo\n");
        break;
    default:
    printf("\nERRO!!\n");
        break;
    }
}

/******************************************************/
/* Função principal */
int main() {
    /* Abra o arquivo de dados de entrada e processe seu conteúdo */
    if ((in_fp = fopen("input.txt", "r")) == NULL) {
        printf("ERRO, nao foi possível abrir o arquivo \n");
    } else {
        getChar();
        do {
            printf("\n");
            lex();
            Node* root = expr(); // Recebe a raiz da árvore de análise sintática

            if (aceitacao == 0) {
                printf("\n");
                printf("        - ANALISE EM PRE-ORDEM - \n");
                printf("       VETOR DOS TOKENS EM PRE-ORDEM\n         [");
                // Função para imprimir a árvore em pré-ordem
                printPreOrder(root);
                printf("]");
                printf("\n\n--->>> ACEITA!!\n****************************************");
            }else{
                printf("##################################\n");
            }
            aceitacao = 0;
        } while (nextToken != EOF);
    }return 0;
}
