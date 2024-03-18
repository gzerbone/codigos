#include <stdio.h>

#define amax 2047      // máximo endereço
#define levmax 3       // máxima profundidade de aninhamento de funções
#define cxmax 200      // número máximo de instruções que podem ser armazenadas code[]
#define stacksize 500

// Aluna: Gabriela Zerbone Magno Baptista

enum fct{lit, opr, lod, sto, cal, INT, jmp, jpc};

typedef struct {
    enum fct f; //tipo da função
    int l;      //nivel
    int a;      //argumento
} instruction;

instruction code[cxmax];

void interpret() {
    int p = 0, b = 1, t = 0; // registros , base, topo da pilha
    instruction i; // registro de instrução
    int s[stacksize];

    //espaços reservados
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;

    // Instruções:
    code[0].f = opr;
    code[0].l = 0;
    code[0].a = 0;

    /***
        FUNÇÃO "base()":
            responsável por encontrar o endereço base de uma variável ou
            função dentro da cadeia de blocos aninhados em execução, percorrendo
            blocos ancestrais na cadeia de blocos até chegar ao nível léxico desejado,
            atualizando o endereço base caso necessário.

        VARIÁVEIS:
            l : nível da variável ou função que queremos encontrar.

            b : o valor do registrador "b" (base) no momento em que a função é chamada.
                'b' representa o onício do bloco atual em execução.

            b1 : cópia do valor de 'b'. Dentro do loop, b1 é atualizado para apontar
                 para o "bloco pai" (um nível acima na cadeia de blocos) de b1. Isso é
                 feito acessando o stack, que é uma representação da cadeia de blocos aninhados na memória.
    ***/
    int base(int l) {  //função interna
        int b1 = b; // encontra base l níveis abaixo

        while (l > 0) {
            b1 = s[b1];
            l--;
        }
        return b1;
    }


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
            case opr: // operações
                switch(i.a){
                    case 0: // Return
                        return 0;
                        break;
                    case 1: // neg
                        s[t] = -s[t];
                        break;
                    case 2: // Soma
                        t--;
                        s[t] = s[t] + s[t + 1];
                        break;
                    case 3: // Subtração
                        t--;
                        s[t] = s[t] - s[t + 1];
                        break;
                    case 4: // Multiplicação
                        t--;
                        s[t] = s[t] * s[t + 1];
                        break;
                    case 5: // Divisão
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
                    case 9: // Diferença
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

