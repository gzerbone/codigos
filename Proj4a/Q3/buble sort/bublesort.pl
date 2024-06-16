% Predicado para trocar dois elementos em uma lista
trocar([X,Y|T], [Y,X|T]) :- X > Y.
trocar([Z|T1], [Z|T2]) :- trocar(T1, T2).

% Predicado para aplicar o Bubble Sort na lista
bubble_sort(Lista, Sorted) :-
    trocar(Lista, Lista1),
    !, bubble_sort(Lista1, Sorted).
bubble_sort(Sorted, Sorted).
