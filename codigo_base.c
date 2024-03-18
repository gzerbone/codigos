#include <stdio.h>

#define amax 2047      // m�ximo endere�o
#define levmax 3       // m�xima profundidade de aninhamento de fun��es
#define cxmax 200      // n�mero m�ximo de instru��es que podem ser armazenadas code[]
#define stacksize 500

// Aluna: Gabriela Zerbone Magno Baptista

enum fct{lit, opr, lod, sto, cal, INT, jmp, jpc};

typedef struct {
    enum fct f; //tipo da fun��o
    int l;      //nivel
    int a;      //argumento
} instruction;

instruction code[cxmax];

void interpret() {
    int p = 0, b = 1, t = 0; // registros , base, topo da pilha
    instruction i; // registro de instru��o
    int s[stacksize];

    //espa�os reservados
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;

    // Instru��es:
    code[0].f = opr;
    code[0].l = 0;
    code[0].a = 0;

    /***
        FUN��O "base()":
            respons�vel por encontrar o endere�o base de uma vari�vel ou
            fun��o dentro da cadeia de blocos aninhados em execu��o, percorrendo
            blocos ancestrais na cadeia de blocos at� chegar ao n�vel l�xico desejado,
            atualizando o endere�o base caso necess�rio.

        VARI�VEIS:
            l : n�vel da vari�vel ou fun��o que queremos encontrar.

            b : o valor do registrador "b" (base) no momento em que a fun��o � chamada.
                'b' representa o on�cio do bloco atual em execu��o.

            b1 : c�pia do valor de 'b'. Dentro do loop, b1 � atualizado para apontar
                 para o "bloco pai" (um n�vel acima na cadeia de blocos) de b1. Isso �
                 feito acessando o stack, que � uma representa��o da cadeia de blocos aninhados na mem�ria.
    ***/
    int base(int l) {  //fun��o interna
        int b1 = b; // encontra base l n�veis abaixo

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
            case opr: // opera��es
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
                    case 3: // Subtra��o
                        t--;
                        s[t] = s[t] - s[t + 1];
                        break;
                    case 4: // Multiplica��o
                        t--;
                        s[t] = s[t] * s[t + 1];
                        break;
                    case 5: // Divis�o
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
                    case 9: // Diferen�a
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

