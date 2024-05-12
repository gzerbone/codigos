// Aluna: Gabriela Zerbone Magno Baptista

import java.util.Scanner;

public class Main {
    public static int fatorial(int n) {
        // Verificar se o fatorial extrapola a capacidade do int
        if (n > 12) {
            System.out.println("IMPORTANTE: O valor do fatorial extrapola a capacidade do int");
            return -1; // retorno que indica o estouro da capacidade
        }
        if (n <= 1)
            return 1;
        else
            return n * fatorial(n - 1);
    }
    
    // calculo da quantidade de permutacoes
    public static int calcularPermutacoes(int quantidade) {
        return fatorial(quantidade);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite a quantidade de elementos do vetor: ");
        int quantidade = scanner.nextInt();

        int permutacoes = calcularPermutacoes(quantidade);

        // Verificar se o valor do fatorial é válido
        if (permutacoes != -1) {
            System.out.println("O numero de permutacoes possiveis e: " + permutacoes);
        }
        scanner.close();
    }
}