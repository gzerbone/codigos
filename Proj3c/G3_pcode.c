/*
    Aluna: Gabriela Zerbone Magno Baptista
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5

void gerador_pcode(FILE *input);

int main() {
    FILE *ARQUIVO = fopen("input.txt", "r");
    if (ARQUIVO == NULL) {
        printf("Erro ao abrir o arquivo input.txt");
        return -1;
    }

    printf("Lendo codigo intermediario do arquivo\n");
    gerador_pcode(ARQUIVO);
    fclose(ARQUIVO);

    return 0;
}

void gerador_pcode(FILE *input) {
    char buffer[256];
    int valor;

    while (fgets(buffer, sizeof(buffer), input)) {
        char *pos = buffer;

        if (strncmp(pos, "PUSH(", 5) == 0) {
            pos += 5;
            sscanf(pos, "%d)", &valor);
            printf("LIT 0 %d\n", valor);
        } else if (strncmp(pos, "y=POP(); x=POP(); PUSH(x ADD y)", 31) == 0) {
            printf("OPR 0 %d\n", ADD);
        } else if (strncmp(pos, "y=POP(); x=POP(); PUSH(x SUB y)", 31) == 0) {
            printf("OPR 0 %d\n", SUB);
        } else if (strncmp(pos, "y=POP(); x=POP(); PUSH(x MUL y)", 31) == 0) {
            printf("OPR 0 %d\n", MUL);
        } else if (strncmp(pos, "y=POP(); x=POP(); PUSH(x DIV y)", 31) == 0) {
            printf("OPR 0 %d\n", DIV);
        }
    }printf("OPR 0 0\n");
}
