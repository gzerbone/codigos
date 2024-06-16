(defun inserir (x lista)
  "Insere o elemento X na posição correta de uma lista ordenada."
  (cond ((null lista) (list x))
        ((<= x (car lista)) (cons x lista))
        (t (cons (car lista) (inserir x (cdr lista))))))

(defun insertion-sort (lista)
  "Ordena uma LISTA usando o algoritmo Insertion Sort."
  (if (null lista)
      nil
      (inserir (car lista) (insertion-sort (cdr lista)))))

;; Exemplo de uso
(let ((lista (list 5 3 8 1 4)))
  (format t "Lista original: ~a~%" lista)
  (format t "Lista ordenada: ~a~%" (insertion-sort lista)))