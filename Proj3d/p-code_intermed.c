/*
    ALUNA: Gabriela Zerbone Magno Baptista
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5

void gerador_pcode(FILE *input, int STACK[]);

int main() {
    int STACK[8]; // Endereços de memória para a, b, c, d, e

    // // Solicitando ao usuário os valores para os endereços de memória
    // printf("Digite o valor para a: ");
    // scanf("%d", &STACK[3]);
    // printf("Digite o valor para b: ");
    // scanf("%d", &STACK[4]);
    // printf("Digite o valor para c: ");
    // scanf("%d", &STACK[5]);
    // printf("Digite o valor para d: ");
    // scanf("%d", &STACK[6]);
    // printf("Digite o valor para e: ");
    // scanf("%d", &STACK[7]);

    STACK[3] = 1; // Valor para a
    STACK[4] = 5; // Valor para b
    STACK[5] = 4; // Valor para c
    STACK[6] = 2; // Valor para d
    STACK[7] = 3; // Valor para e

    FILE *ARQUIVO = fopen("input.txt", "r");
    if (ARQUIVO == NULL) {
        printf("Erro ao abrir o arquivo input.txt");
        return -1;
    }

    printf("\nLendo codigo intermediario do arquivo...\n");
    gerador_pcode(ARQUIVO, STACK);
    fclose(ARQUIVO);

    return 0;
}

void gerador_pcode(FILE *input, int STACK[]) {
    char buffer[256];
    int valor, tam_stack, i = 0, codigo=1;

    printf(" ***** CODIGO %d *****\n", codigo);
    printf("INT 0 7\n");
    while (fgets(buffer, sizeof(buffer), input)) {
        char *pos = buffer;

        // usar o ### para adicionar outro codigo intermediario na entrada input.txt
        if (strncmp(pos, "###", 3) == 0) {
            codigo++;
            printf("OPR 0 0\n");
            printf("\nPROXIMO CODIGO INTERMEDIARIO...\n");
            printf(" ***** CODIGO %d *****\n", codigo);
            printf("INT 0 7\n");
            continue;
        }

        if (strncmp(pos, "PUSH(", 5) == 0) {
            pos += 5;
            char variavel;
            sscanf(pos, "%c)", &variavel);
            switch (variavel) {
                case 'a':
                    valor = STACK[3];
                    i = 3;
                    break;
                case 'b':
                    valor = STACK[4];
                    i = 4;
                    break;
                case 'c':
                    valor = STACK[5];
                    i = 5;
                    break;
                case 'd':
                    valor = STACK[6];
                    i = 6;
                    break;
                case 'e':
                    valor = STACK[7];
                    i = 7;
                    break;
                default:
                    break;
            }
            printf("LOD 0 %d\n", i);
        } else if (strncmp(pos, "y=POP(); x=POP(); PUSH(x ADD y)", 31) == 0) {
            printf("OPR 0 %d\n", ADD);
        } else if (strncmp(pos, "y=POP(); x=POP(); PUSH(x SUB y)", 31) == 0) {
            printf("OPR 0 %d\n", SUB);
        } else if (strncmp(pos, "y=POP(); x=POP(); PUSH(x MUL y)", 31) == 0) {
            printf("OPR 0 %d\n", MUL);
        } else if (strncmp(pos, "y=POP(); x=POP(); PUSH(x DIV y)", 31) == 0) {
            printf("OPR 0 %d\n", DIV);
        }
    }
    printf("OPR 0 0\n");
}
