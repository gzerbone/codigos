// Aluna: Gabriela Zerbone Magno Baptista

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char cadeia[200];
    int i;
    int estado;
    
    FILE *arquivo = fopen("input_AL_decimal.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fscanf(arquivo, "%s", cadeia) != EOF) {
        i = 0;      // reinicializa o índice para cada cadeia
        estado = 0; // reinicializa o estado para cada cadeia
        
        // Analisador lexico para numeros decimais
        while (cadeia[i] != '\0') {
            if (isdigit(cadeia[i])) {
                estado = 1; // digito encontrado, transita para o estado 1
                i++;
            } else if (cadeia[i] == '.' && estado == 1) {
                estado = 2; // ponto decimal encontrado, transita para o estado 2
                i++;
            } else {
                estado = 0; // caractere invalido, transita para o estado 0 (rejeicao)
                break;
            }
        }

        // Verifica o estado final e emite o resultado
        if (estado == 1 || estado == 2) {
            printf("%s ----- RECONHECIDA\n", cadeia);
        } else {
            printf("%s ----- Rejeitada\n", cadeia);
        }
    }

    fclose(arquivo);
    return 0;
}