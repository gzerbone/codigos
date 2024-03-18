#include <stdio.h>

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
int s[stacksize];

void interpretador() {
    int p = 0, b = 1, t = 0; // registros program-, base-, topstack-
    instruction i; // registro de instrução


    //espaços reservados
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;

    // INSTRUÇÕES
/***
    int soma = 1;
    for (int i = 2; i <= 100; i++) {
        soma += i * i;
***/
    int k = 0;
    code[k].f = INT; code[k].l = 0; code[k].a = 6; k++;			// 0-  libera 6 espaços de memoria
    code[k].f = lit; code[k].l = 0; code[k].a = 2; k++;			// 1 - Inicia contador com 2
    code[k].f = sto; code[k].l = 0; code[k].a = 3; k++;			// 2 - Salva contador
    code[k].f = lit; code[k].l = 0; code[k].a = 100; k++;		// 3 - Explicita o Limite
    code[k].f = sto; code[k].l = 0; code[k].a = 4; k++;			// 4 - Salva o limite
    code[k].f = lit; code[k].l = 0; code[k].a = 1; k++;			// 5 - Inicia Soma = 1
    code[k].f = sto; code[k].l = 0; code[k].a = 5; k++;			// 6 - Salva Soma
    code[k].f = lod; code[k].l = 0; code[k].a = 3; k++;			// 7 - Inicio do loop (carrega i)
    code[k].f = lod; code[k].l = 0; code[k].a = 3; k++;			// 8 - Prepara quadrado (carrega i)
    code[k].f = opr; code[k].l = 0; code[k].a = 4; k++;			// 9 - i*i
    code[k].f = lod; code[k].l = 0; code[k].a = 5; k++;			// 10 - Load Soma
    code[k].f = opr; code[k].l = 0; code[k].a = 2; k++;			// 11 - Soma + i
    code[k].f = sto; code[k].l = 0; code[k].a = 5; k++;			// 12 - Salva a Soma
    code[k].f = lod; code[k].l = 0; code[k].a = 3; k++;			// 13 - Carrega i
    code[k].f = lod; code[k].l = 0; code[k].a = 4; k++;			// 14 - CArrega Máximo
    code[k].f = opr; code[k].l = 0; code[k].a = 10; k++;		// 15 - Menor que
    code[k].f = jpc; code[k].l = 0; code[k].a = 21; k++;		// 16 - Saida do loop
    code[k].f = lod; code[k].l = 0; code[k].a = 3; k++;			// 17 - carrega i
    code[k].f = opr; code[k].l = 0; code[k].a = 2; k++;			// 18 - i + 1
    code[k].f = sto; code[k].l = 0; code[k].a = 3; k++;			// 19 - Salva i
    code[k].f = jmp; code[k].l = 0; code[k].a = 7; k++;			// 20 - Fim do loop
    code[k].f = opr; code[k].l = 0; code[k].a = 0;				// 21 - Fim do programa

    int base(int l) {  //função interna
        int b1 = b; // encontra base l níveis abaixo

        while (l > 0) {
            b1 = s[b1];
            l--;
        }
        return b1;
    }


    printf("\n| p |  b |  t |                      conteudo da pilha                      |");
    printf("\n|---|----|----|-------------------------------------------------------------|");

    do {
        i = code[p];
        printf("\n|%2d | %2d | %2d | ", p, b, t);
        p=p+1;
        switch (i.f) {
            case lit: // Coloca no topo o valor de 'i.a'
                t++;
                s[t] = i.a;
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
                        //printf("Soma: %d + %d = %d", s[t], s[t+1], s[t]);
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
                //printf("lod %d, %d\n", i.l, i.a);
                break;
            case sto:
                s[base(i.l) + i.a] = s[t];
                //printf("sto %d, %d\n", i.l, i.a);
                t--;
                break;
            case cal:
                s[t + 1] = base(i.l);
                s[t + 2] = b;
                s[t + 3] = p;
                b = t + 1;
                p = i.a;
                //printf("cal %d, %d\n", i.l, i.a);
                break;
            case INT:
                t += i.a;
                //printf("INT %d\n", i.a);
                break;
            case jmp:
                p = i.a;
                //printf("jmp %d\n", i.a);
                break;
            case jpc:
                if (s[t] == 0){
                    p = i.a;
                    t--;
                    //printf("jpc %d\n", i.a);
                }
                break;
        }
        //imprime a pilha
        for (int j = 1; j <= t; j++){
            printf("%7d", s[j]);

        }
    } while (p != 0);
}
int main() {
    interpretador();
    return 0;
}

