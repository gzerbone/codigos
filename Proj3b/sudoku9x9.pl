%Aluna: Gabriela Zerbone M. Baptista

% Regra 1
sudoku9x9(A11,A12,A13,A14,A15,A16,A17,A18,A19,
          A21,A22,A23,A24,A25,A26,A27,A28,A29,
          A31,A32,A33,A34,A35,A36,A37,A38,A39,
          A41,A42,A43,A44,A45,A46,A47,A48,A49,
          A51,A52,A53,A54,A55,A56,A57,A58,A59,
          A61,A62,A63,A64,A65,A66,A67,A68,A69,
          A71,A72,A73,A74,A75,A76,A77,A78,A79,
          A81,A82,A83,A84,A85,A86,A87,A88,A89,
          A91,A92,A93,A94,A95,A96,A97,A98,A99) :-
          
    p9(A11,A12,A13,A14,A15,A16,A17,A18,A19),
    p9(A21,A22,A23,A24,A25,A26,A27,A28,A29),
    p9(A31,A32,A33,A34,A35,A36,A37,A38,A39),
    p9(A41,A42,A43,A44,A45,A46,A47,A48,A49),
    p9(A51,A52,A53,A54,A55,A56,A57,A58,A59),
    p9(A61,A62,A63,A64,A65,A66,A67,A68,A69),
    p9(A71,A72,A73,A74,A75,A76,A77,A78,A79),
    p9(A81,A82,A83,A84,A85,A86,A87,A88,A89),
    p9(A91,A92,A93,A94,A95,A96,A97,A98,A99),

    % Permutação de colunas
    p9(A11,A21,A31,A41,A51,A61,A71,A81,A91),
    p9(A12,A22,A32,A42,A52,A62,A72,A82,A92),
    p9(A13,A23,A33,A43,A53,A63,A73,A83,A93),
    p9(A14,A24,A34,A44,A54,A64,A74,A84,A94),
    p9(A15,A25,A35,A45,A55,A65,A75,A85,A95),
    p9(A16,A26,A36,A46,A56,A66,A76,A86,A96),
    p9(A17,A27,A37,A47,A57,A67,A77,A87,A97),
    p9(A18,A28,A38,A48,A58,A68,A78,A88,A98),
    p9(A19,A29,A39,A49,A59,A69,A79,A89,A99),

    % Permutação dos quadrados 3x3
    p9(A11,A12,A13,A21,A22,A23,A31,A32,A33),
    p9(A14,A15,A16,A24,A25,A26,A34,A35,A36),
    p9(A17,A18,A19,A27,A28,A29,A37,A38,A39),
    p9(A41,A42,A43,A51,A52,A53,A61,A62,A63),
    p9(A44,A45,A46,A54,A55,A56,A64,A65,A66),
    p9(A47,A48,A49,A57,A58,A59,A67,A68,A69),
    p9(A71,A72,A73,A81,A82,A83,A91,A92,A93),
    p9(A74,A75,A76,A84,A85,A86,A94,A95,A96),
    p9(A77,A78,A79,A87,A88,A89,A97,A98,A99),

    prow(A11,A12,A13,A14,A15,A16,A17,A18,A19), nl,
    prow(A21,A22,A23,A24,A25,A26,A27,A28,A29), nl,
    prow(A31,A32,A33,A34,A35,A36,A37,A38,A39), nl,
    prow(A41,A42,A43,A44,A45,A46,A47,A48,A49), nl,
    prow(A51,A52,A53,A54,A55,A56,A57,A58,A59), nl,
    prow(A61,A62,A63,A64,A65,A66,A67,A68,A69), nl,
    prow(A71,A72,A73,A74,A75,A76,A77,A78,A79), nl,
    prow(A81,A82,A83,A84,A85,A86,A87,A88,A89), nl,
    prow(A91,A92,A93,A94,A95,A96,A97,A98,A99), nl.

prow(X1,X2,X3,X4,X5,X6,X7,X8,X9) :-
    write(X1), write(' '), write(X2), write(' '), write(X3), write('  '),
    write(X4), write(' '), write(X5), write(' '), write(X6), write('  '),
    write(X7), write(' '), write(X8), write(' '), write(X9).

%Regra 2: Definição de permutação para nove elementos
p9(A,B,C,D,E,F,G,H,I) :-
    d(A,B), d(A,C), d(A,D), d(A,E), d(A,F), d(A,G), d(A,H), d(A,I),
    d(B,C), d(B,D), d(B,E), d(B,F), d(B,G), d(B,H), d(B,I),
    d(C,D), d(C,E), d(C,F), d(C,G), d(C,H), d(C,I),
    d(D,E), d(D,F), d(D,G), d(D,H), d(D,I),
    d(E,F), d(E,G), d(E,H), d(E,I),
    d(F,G), d(F,H), d(F,I),
    d(G,H), d(G,I),
    d(H,I).

%FATOS = Predicado(arg1, arg2).
d(1,2). d(1,3). d(1,4). d(1,5). d(1,6). d(1,7). d(1,8). d(1,9).
d(2,1). d(2,3). d(2,4). d(2,5). d(2,6). d(2,7). d(2,8). d(2,9).
d(3,1). d(3,2). d(3,4). d(3,5). d(3,6). d(3,7). d(3,8). d(3,9).
d(4,1). d(4,2). d(4,3). d(4,5). d(4,6). d(4,7). d(4,8). d(4,9).
d(5,1). d(5,2). d(5,3). d(5,4). d(5,6). d(5,7). d(5,8). d(5,9).
d(6,1). d(6,2). d(6,3). d(6,4). d(6,5). d(6,7). d(6,8). d(6,9).
d(7,1). d(7,2). d(7,3). d(7,4). d(7,5). d(7,6). d(7,8). d(7,9).
d(8,1). d(8,2). d(8,3). d(8,4). d(8,5). d(8,6). d(8,7). d(8,9).
d(9,1). d(9,2). d(9,3). d(9,4). d(9,5). d(9,6). d(9,7). d(9,8).
