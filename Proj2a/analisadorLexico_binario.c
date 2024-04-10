// Aluna: Gabriela Zerbone Magno Baptista

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char cadeia[200];
    int i;
    int estado;
    
    FILE *arquivo = fopen("input_AL_binario.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fscanf(arquivo, "%s", cadeia) != EOF) {
        i = 0;      // reinicializa o indice para cada cadeia
        estado = 0; // reinicializa o estado para cada cadeia
        
        // Analisador lexico
        while (cadeia[i] != '\0') {
            if (cadeia[i] == '0' || cadeia[i] == '1') {
                estado = 1;
                i++;
            } else {
                estado = 0;
                break;
            }
        }

        // Verifica o estado final
        if (estado == 1) {
            printf("%s ----- RECONHECIDA\n", cadeia);
        } else {
            printf("%s ----- Rejeitada\n", cadeia);
        }
    }
    fclose(arquivo);
    return 0;
}
