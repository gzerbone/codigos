
// Gabriela Zerbone Magno Baptista

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_TREE_SIZE 100

int tree[MAX_TREE_SIZE];
int tree_index = 0;

char stack[MAX_STACK_SIZE];
int top, indice;

void push(char *stack, char c){
    top++;
    stack[top] = c;
}

// Obter o proximo caracter
char lerSimbolo(const char* str){
    return str[indice++];
}

void pop(){
    top--;
}

// Visualizar a pilha
void print_stack() {
    printf("Pilha: ");
    for (int i = top; i >= 0; i--) {
        printf("%c ", stack[i]);
    }
    printf("\n");
}

// Valida se uma string pertence a gramatica especificada
const char* validacaoCadeias(const char* str) { 
    top = -1; 
    indice = 0;
    char token; // token atual

    ESTADO_INICIAL:
        push(stack, 'S'); 
        token = lerSimbolo(str); 
        print_stack();
    goto ESTADO_FINAL;

    ESTADO_FINAL:
        // Verifica as transicoes possiveis e atualiza a pilha conforme a gramatica
        if(token == 'a' && stack[top] == 'S'){ 
            pop(); 
            push(stack, 'b'); 
            push(stack, 'S'); 
            push(stack, 'a'); 
            printf("p1: S -> aSb\n");
        }
        else if (token == 'b' && stack[top] == 'S'){ 
            pop(); 
            push(stack, 'b'); 
            push(stack, 'S'); 
            push(stack, 'a'); 
            printf("p1: S -> aSb\n");
        } 
        else if (token == 'c' && stack[top] == 'S') { 
            pop(); 
            push(stack, 'c'); 
            printf("p2: S -> c\n");
        }
        else if (token == 'a' && stack[top] == 'a') { 
            pop(); 
            token = lerSimbolo(str);
        } 
        else if (token == 'b' && stack[top] == 'b') { 
            pop(); 
            token = lerSimbolo(str);
        } 
        else if (token == 'c' && stack[top] == 'c') { 
            pop(); 
            token = lerSimbolo(str);
        } 
        else if (token == '\0') { 
            if (top == -1) {
                return "Aceita"; // Se a pilha estiver vazia a cadeia pertence
            }
            return "REJEITADA"; 
        } 
        else {
            return "REJEITADA";
        //print_stack();
        }
    goto ESTADO_FINAL; // Vai para o estado final para ler o proximo token
}


int main() {
    FILE *FILE;
    char cadeia[50];
    FILE = fopen("input.txt", "r");
    if (FILE == NULL) {
        printf("Falha ao abrir o arquivo.\n");
        return 1;
    }    
    // Le cada cadeia do arquivo
    while (fscanf(FILE, "%s", cadeia) != EOF) {
        const char* resultado = validacaoCadeias(cadeia);
        printf("CADEIA -->>  %s\nResultado: %s\n", cadeia, resultado);

        printf("\n");
    }
    fclose(FILE);
    return 0;
}