%Gabriela Zerbone Magno Baptista

/* Desenvolver programas PROLOG para encontrar permutações de 8
elementos*/
perm(A,B,C,D,E,F,G,H):- neq8(A,B,C,D,E,F,G,H).
neq8(A,B,C,D,E,F,G,H):- neq(A,B),neq(A,C),neq(A,D),neq(A,E),neq(A,F),neq(A,G),neq(A,H),
    			  	neq(B,C),neq(B,D),neq(B,E),neq(B,F),neq(B,G),neq(B,H),
    			  	neq(C,D), neq(C,E),neq(C,F),neq(C,G),neq(C,H),
				  	neq(D,E),neq(D,F),neq(D,G),neq(D,H),
    			  	neq(E,F),neq(E,G),neq(E,H),
    				neq(F,G),neq(F,H),
    				neq(G,H).
neq(1,2).
neq(1,3).
neq(1,4).
neq(1,5).
neq(1,6).
neq(1,7).
neq(1,8).
neq(2,1).
neq(2,3).
neq(2,4).
neq(2,5).
neq(2,6).
neq(2,7).
neq(2,8).
neq(3,1).
neq(3,2).
neq(3,4).
neq(3,5).
neq(3,6).
neq(3,7).
neq(3,8).
neq(4,1).
neq(4,2).
neq(4,3).
neq(4,5).
neq(4,6).
neq(4,7).
neq(4,8).
neq(5,1).
neq(5,2).
neq(5,3).
neq(5,4).
neq(5,6).
neq(5,7).
neq(5,8).
neq(6,1).
neq(6,2).
neq(6,3).
neq(6,4).
neq(6,5).
neq(6,7).
neq(6,8).
neq(7,1).
neq(7,2).
neq(7,3).
neq(7,4).
neq(7,5).
neq(7,6).
neq(7,8).
neq(8,1).
neq(8,2).
neq(8,3).
neq(8,4).
neq(8,5).
neq(8,6).
neq(8,7).