/*
    Aluna: Gabriela Zerbone MAgno BAptista
 */

#include <stdio.h>

#define TAMANHO_MAX 1024
#define PALAVRA_MAX 100
#define TAM_POLONESA 50

char arvore[TAMANHO_MAX];
int pilhaDeIndices[PALAVRA_MAX];
char pilhaDeSimbolos[PALAVRA_MAX];
char entrada[PALAVRA_MAX];
char polonesaInversa[TAM_POLONESA];

int topoPilha = 0;
int topoSimbolos = 0;
int proximoSimbolo = 0;
int topoPolonesa = 0;


int desempilharIndice(){
    return pilhaDeIndices[--topoPilha];
}

void empilharIndice(int valor){
    pilhaDeIndices[topoPilha++] = valor;
}
int lerTopoIndice(){
    return pilhaDeIndices[topoPilha - 1];
}

void inicializarArvore(char *arvore){
    for (int i = 0; i < TAMANHO_MAX; i++)
        arvore[i] = ' ';
}

void adicionarNaArvore(int p){
    if (p == 0)
    {
        arvore[0] = 'E';
        empilharIndice(0);
    }
    else
    {
        int noAtual = desempilharIndice();
        switch (p)
        {
            case 1:
                arvore[5 * noAtual + 1] = '(';
                arvore[5 * noAtual + 2] = 'E';
                arvore[5 * noAtual + 3] = 'X';
                arvore[5 * noAtual + 4] = 'E';
                arvore[5 * noAtual + 5] = ')';
                empilharIndice(5 * noAtual + 4);
                empilharIndice(5 * noAtual + 3);
                empilharIndice(5 * noAtual + 2);
                break;
            case 2:
                arvore[5 * noAtual + 1] = '0';
                break;
            case 3:
                arvore[5 * noAtual + 1] = '1';
                break;
            case 4:
                arvore[5 * noAtual + 1] = 'a';
                break;
            case 5:
                arvore[5 * noAtual + 1] = 'b';
                break;
            case 6:
                arvore[5 * noAtual + 1] = 'c';
                break;
            case 7:
                arvore[5 * noAtual + 1] = '+';
                break;
            case 8:
                arvore[5 * noAtual + 1] = '-';
                break;
            case 9:
                arvore[5 * noAtual + 1] = '*';
                break;
            case 10:
                arvore[5 * noAtual + 1] = '/';
                break;
        }
    }
}

void transformarParaBinaria(char *novaArvore)
{
    int pai, ancestral;

    inicializarArvore(novaArvore);

    for (int i = TAMANHO_MAX; i >= 0; i--)
    {
        if (arvore[i] == 'a' || arvore[i] == 'b' || arvore[i] == 'c' || arvore[i] == '0' || arvore[i] == '1')
        {
            pai = (i - 1) / 5;
            novaArvore[pai] = arvore[i];
            novaArvore[i] = ' ';
        }
        else if (arvore[i] == '+' || arvore[i] == '-' || arvore[i] == '*' || arvore[i] == '/')
        {
            pai = (i - 1) / 5;
            ancestral = (pai - 1) / 5;
            novaArvore[pai] = ' ';
            novaArvore[ancestral] = arvore[i];
            novaArvore[i] = ' ';
        }
    }
}

void percursoPosOrdem(char *arvore, int indice)
{
    if (arvore[indice] != ' ')
    {
        percursoPosOrdem(arvore, 5 * indice + 2);
        percursoPosOrdem(arvore, 5 * indice + 4);
        polonesaInversa[topoPolonesa++] = arvore[indice];
    }
}

void gerarPcode()
{
    for (int i = 0; polonesaInversa[i] != '\0'; i++)
    {
        switch (polonesaInversa[i])
        {
            case 'a':
                printf(" LOD 0 3");
                break;
            case 'b':
                printf(" LOD 0 4");
                break;
            case 'c':
                printf(" LOD 0 5");
                break;
            case '1':
                printf(" LIT 0 1");
                break;
            case '+':
                printf(" OPR 0 2");
                break;
            case '-':
                printf(" OPR 0 3");
                break;
            case '*':
                printf(" OPR 0 4");
                break;
            case '/':
                printf(" OPR 0 5");
                break;
            default:
                break;
        }
        printf("\n");
    }
}

void imprimirArvore(char *arvore, int indice, int nivel) 
{
    if (indice < TAMANHO_MAX && arvore[indice] != ' ') 
    {
        for (int i = 0; i < nivel; i++) 
            printf("   ");

        printf("|-- %c\n", arvore[indice]);

        imprimirArvore(arvore, 5 * indice + 1, nivel + 1); 
        imprimirArvore(arvore, 5 * indice + 2, nivel + 1); 
        imprimirArvore(arvore, 5 * indice + 3, nivel + 1); 
        imprimirArvore(arvore, 5 * indice + 4, nivel + 1); 
        imprimirArvore(arvore, 5 * indice + 5, nivel + 1); 
    }
}

int tamanhoPalavra(char *palavra)
{
    int tamanho = -1;
    for (int i = 0; palavra[i] != '\0'; i++)
        tamanho++;

    return tamanho;
}

void exibirCabecalho()
{
    int tamPalavra = tamanhoPalavra(entrada);

    printf("Tabela de Parsing:\n\n");
    printf("  i ||  q  ||");

    for (int i = 0; i < tamPalavra; i++)
    {
        if (i == tamPalavra / 2)
            printf(".w");
    
        printf(" ");
    }

    printf("  ||  t  ||  p  || Pilha\n");
    for (int i = 0; i < tamPalavra + 40; i++)
        printf("=");
}

void empilharSimbolo(char *valor)
{
    int tam = tamanhoPalavra(valor);

    for (int i = 0; valor[i] != '\0'; i++)
    {
        pilhaDeSimbolos[topoSimbolos] = valor[tam - i];
        topoSimbolos++;
    }
}

void desempilharSimbolo()
{
    topoSimbolos--;
}

char lerTopoSimbolo()
{
    return pilhaDeSimbolos[topoSimbolos - 1];
}

char obterProximoSimbolo()
{
    proximoSimbolo++;
    char token = entrada[proximoSimbolo];
    return token;
}

void exibirErro(int i)
{
    if (i == 1)
    {
        printf("\n\n\tErro: palavra nao reconhecida\n");
    }
}

void exibirEstado(int i, char *estado, char *transicao, char *simbolo)
{
    printf("\n");
    printf("%3d || ", i);
    printf("%3s || ", estado);

    for (int j = 0; entrada[j] != '\0'; j++)
    {
        if (j == proximoSimbolo)
        {
            printf(".");
        }
        printf("%c", entrada[j]);
    }

    if (entrada[proximoSimbolo] == '\0')
        printf(".");

    printf(" || ");
    printf("%3s || ", transicao);
    printf("%3s || ", simbolo);

    if (topoSimbolos == 0)
        printf("None");
    else
        for (int j = topoSimbolos - 1; j >= 0; j--)
            printf("%c", pilhaDeSimbolos[j]);
}


int main()
{
    char tokenAtual;
    int contador = 0;
    FILE *arquivoEntrada;
    char arvoreBinaria[TAMANHO_MAX];

    arquivoEntrada = fopen("input.txt", "r");
    if (arquivoEntrada == NULL)
    {
        printf("Erro na leitura do arquivo\n");
        return 0;
    }

    fscanf(arquivoEntrada, "%s", entrada);
    fclose(arquivoEntrada);

    inicializarArvore(arvore);
    exibirCabecalho();

    // Estado inicial
    q0:
        exibirEstado(contador, "q0", "t0", "-");
        tokenAtual = entrada[topoSimbolos];
        empilharSimbolo("E");
        adicionarNaArvore(0);
        goto q1;
    q1:
        contador++;
        if (tokenAtual == '(' && lerTopoSimbolo() == 'E') {
            exibirEstado(contador, "q1", "t1", "p1"); desempilharSimbolo(); empilharSimbolo("(EXE)"); adicionarNaArvore(1); goto q1;
        } else if (tokenAtual == '0' && lerTopoSimbolo() == 'E') {
            exibirEstado(contador, "q1", "t2", "p2"); desempilharSimbolo(); empilharSimbolo("0"); adicionarNaArvore(2); goto q1;
        } else if (tokenAtual == '1' && lerTopoSimbolo() == 'E') {
            exibirEstado(contador, "q1", "t3", "p3"); desempilharSimbolo(); empilharSimbolo("1"); adicionarNaArvore(3); goto q1;
        } else if (tokenAtual == 'a' && lerTopoSimbolo() == 'E') {
            exibirEstado(contador, "q1", "t4", "p4"); desempilharSimbolo(); empilharSimbolo("a"); adicionarNaArvore(4); goto q1;
        } else if (tokenAtual == 'b' && lerTopoSimbolo() == 'E') {
            exibirEstado(contador, "q1", "t5", "p5"); desempilharSimbolo(); empilharSimbolo("b"); adicionarNaArvore(5); goto q1;
        } else if (tokenAtual == 'c' && lerTopoSimbolo() == 'E') {
            exibirEstado(contador, "q1", "t6", "p6"); desempilharSimbolo(); empilharSimbolo("c"); adicionarNaArvore(6); goto q1;
        } else if (tokenAtual == '+' && lerTopoSimbolo() == 'X') {
            exibirEstado(contador, "q1", "t7", "p7"); desempilharSimbolo(); empilharSimbolo("+"); adicionarNaArvore(7); goto q1;
        } else if (tokenAtual == '-' && lerTopoSimbolo() == 'X') {
            exibirEstado(contador, "q1", "t8", "p8"); desempilharSimbolo(); empilharSimbolo("-"); adicionarNaArvore(8); goto q1;
        } else if (tokenAtual == '*' && lerTopoSimbolo() == 'X') {
            exibirEstado(contador, "q1", "t9", "p9"); desempilharSimbolo(); empilharSimbolo("*"); adicionarNaArvore(9); goto q1;
        } else if (tokenAtual == '/' && lerTopoSimbolo() == 'X') {
            exibirEstado(contador, "q1", "t10", "p10"); desempilharSimbolo(); empilharSimbolo("/"); adicionarNaArvore(10); goto q1;
        } else if (tokenAtual == 'a' && lerTopoSimbolo() == 'a') {
            exibirEstado(contador, "q1", "t11", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == 'b' && lerTopoSimbolo() == 'b') {
            exibirEstado(contador, "q1", "t12", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == 'c' && lerTopoSimbolo() == 'c') {
            exibirEstado(contador, "q1", "t13", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == '0' && lerTopoSimbolo() == '0') {
            exibirEstado(contador, "q1", "t14", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == '1' && lerTopoSimbolo() == '1') {
            exibirEstado(contador, "q1", "t15", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == '(' && lerTopoSimbolo() == '(') {
            exibirEstado(contador, "q1", "t16", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == ')' && lerTopoSimbolo() == ')') {
            exibirEstado(contador, "q1", "t17", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == '+' && lerTopoSimbolo() == '+') {
            exibirEstado(contador, "q1", "t18", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == '-' && lerTopoSimbolo() == '-') {
            exibirEstado(contador, "q1", "t19", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == '*' && lerTopoSimbolo() == '*') {
            exibirEstado(contador, "q1", "t20", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == '/' && lerTopoSimbolo() == '/') {
            exibirEstado(contador, "q1", "t21", "-"); desempilharSimbolo(); tokenAtual = obterProximoSimbolo(); goto q1;
        } else if (tokenAtual == '\0' && topoSimbolos == 0) {
            exibirEstado(contador, "q1", "-", "-"); goto fim;
        } else {
            exibirErro(1);
            return 0;
        }
    fim:
        printf("\n\nArvore N-aria:\n");
        imprimirArvore(arvore, 0, 0);
        transformarParaBinaria(arvoreBinaria);
        percursoPosOrdem(arvoreBinaria, 0);
        polonesaInversa[topoPolonesa] = '\0';
        printf("\n\nP-code Polones Reverso:\n %s\n\n", polonesaInversa);
        gerarPcode();
        printf(" OPR 0 0");

    return 0;
}

