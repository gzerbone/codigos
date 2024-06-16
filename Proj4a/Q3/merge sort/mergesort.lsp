(defun merge-sort (lista)
  "Ordena a LISTA usando o algoritmo Merge Sort."
  (if (pequena lista)
      lista  ; Se a lista for pequena (vazia ou um único elemento), retorna a lista.
      (merge-list
       (merge-sort (metade-esquerda lista))
       (merge-sort (metade-direita lista)))))

(defun pequena (lista)
  "Verifica se a LISTA é pequena, ou seja, se está vazia ou tem apenas um elemento."
  (or (null lista) (null (cdr lista))))

(defun metade-direita (lista)
  "Retorna a metade direita da LISTA."
  (last lista (ceiling (/ (length lista) 2))))

(defun metade-esquerda (lista)
  "Retorna a metade esquerda da LISTA."
  (ldiff lista (metade-direita lista)))

(defun merge-list (lista1 lista2)
  "Combina duas listas ordenadas LISTA1 e LISTA2 em uma única lista ordenada."
  (merge 'list lista1 lista2 #'<))


(print (merge-sort '(3 4 8 0 6 7 4 2 1 9 4 5)))
