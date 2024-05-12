// Aluna: Gabriela Zerbone Magno Baptista

#include <stdio.h>

int fatorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * fatorial(n - 1);
}
int calcularPermutacoes(int quantidade) {
    // Verificar se a quantidade de elementos excede a capacidade do tipo de dados int
    if (quantidade > 12) {
        printf("IMPORTANTE: O valor do fatorial extrapola a capacidade do int.\n");
        return -1;
    }
    return fatorial(quantidade);
}

int main() {
    int quantidade, permutacoes;

    printf("Digite a quantidade de elementos do vetor: ");
    scanf("%d", &quantidade);

    permutacoes = calcularPermutacoes(quantidade);

    if (permutacoes != -1) {
        printf("O numero de permutacoes possiveis e: %d permutacoes\n", permutacoes);
    }
    return 0;
}
