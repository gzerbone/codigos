#include <stdio.h>

#define amax 2047      // maximo endereco
#define levmax 3       // maxima profundidade de aninhamento de funcoes
#define cxmax 200      // numero maximo de instrucoes que podem ser armazenadas code[]
#define stacksize 500

// Aluna: Gabriela Zerbone Magno Baptista

enum fct{lit, opr, lod, sto, cal, INT, jmp, jpc};

typedef struct {
    enum fct f; //tipo da funcoo
    int l;      //nivel
    int a;      //argumento
} instruction;

instruction code[cxmax];

/***
 *     FUNCAO "base()":
 *         responsavel por encontrar o endereco base de uma variavel ou
 *         funcao dentro da cadeia de blocos aninhados em execucao, percorrendo
 *         blocos ancestrais na cadeia de blocos ate chegar ao nivel lexico desejado,
 *         atualizando o endereco base caso necessario
 *     VARIAVEIS:
 *         l : nivel da variavel ou funcao que queremos encontrar
 *         b : o valor do registrador "b" (base) no momento em que a funcao e chamada.
 *             'b' representa o inicio do bloco atual em execucao
 *         b1 : copia do valor de 'b'. Dentro do loop, b1 e atualizado para apontar
 *              para o "bloco pai" (um nivel acima na cadeia de blocos) de b1. Isso e
 *              feito acessando o stack, que e uma representacao da cadeia de blocos aninhados na memoria.
 * ***/
int base(int l) {
    int b1 = 1; // encontra base l níveis abaixo

    while (l > 0) {
        b1 = code[b1].a;
        l--;
    }
    return b1;
}
void interpret() {
    int p = 0, b = 1, t = 0; // registros , base, topo da pilha
    instruction i; // registro de instrucao
    int s[stacksize];

    //espacos reservados
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;

    // Instrucoes:
    code[0].f = opr;
    code[0].l = 0;
    code[0].a = 0;

    printf("\n| p |  b |  t |");
    printf("\n|---|----|----|");

    do {
        printf("\n|%2d | %2d | %2d | ", p, b, t);

        i = code[p++];

        switch (i.f) {
            case lit: // Coloca no topo o valor de 'i.a'
                t++;
                s[t] = i.a;
                printf("\nlit %d, %d\n", i.l, i.a);
                break;
            case opr: // operacoes
                switch(i.a){
                    case 0: // Return
                        t = b - 1;
                        p = s[t + 3];
                        b = s[t + 2];
                        break;
                    case 1: // neg
                        s[t] = -s[t];
                        break;
                    case 2: // Soma
                        t--;
                        s[t] = s[t] + s[t + 1];
                        break;
                    case 3: // Subtracao
                        t--;
                        s[t] = s[t] - s[t + 1];
                        break;
                    case 4: // Multiplicacao
                        t--;
                        s[t] = s[t] * s[t + 1];
                        break;
                    case 5: // Divisao
                        t--;
                        s[t] = s[t] / s[t + 1];
                        break;
                    case 6: // Resto por 2
                        s[t] = (s[t]) % 2;
                        break;
                    case 8: // Igualdade
                        t--;
                        s[t] = (s[t] == s[t + 1]);
                        break;
                    case 9: // Diferenca
                        t--;
                        s[t] = (s[t] != s[t + 1]);
                        break;
                    case 10: // Menor que
                        t--;
                        s[t] = (s[t] < s[t + 1]);
                        break;
                    case 11: // Menor igual
                        t--;
                        s[t] = (s[t] <= s[t + 1]);
                        break;
                    case 12: // Maior que
                        t--;
                        s[t] = (s[t] > s[t + 1]);
                        break;
                    case 13: // Maior igual
                        t--;
                        s[t] = (s[t] >= s[t + 1]);
                        break;
                }
                break;
            case lod:
                t++;
                s[t] = s[base(i.l) + i.a];
                printf("lod %d, %d\n", i.l, i.a);
                break;
            case sto:
                s[base(i.l) + i.a] = s[t];
                printf("sto %d, %d\n", i.l, i.a);
                t--;
                break;
            case cal:
                s[t + 1] = base(i.l);
                s[t + 2] = b;
                s[t + 3] = p;
                b = t + 1;
                p = i.a;
                printf("cal %d, %d\n", i.l, i.a);
                break;
            case INT:
                t += i.a;
                printf("INT %d\n", i.a);
                break;
            case jmp:
                p = i.a;
                printf("jmp %d\n", i.a);
                break;
            case jpc:
                if (s[t] == 0){
                    p = i.a;
                    t--;
                    printf("jpc %d\n", i.a);
                }
                break;
        }

        //imprime o conteudo da pilha
        for (int j = 1; j <= t; j++){
            printf("%d ", s[j]);
        }
    } while (p != 0);
}
int main() {
    interpret();
    return 0;
}

