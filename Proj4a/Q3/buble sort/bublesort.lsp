(defun trocar-elementos (lista)
  "Realiza uma passagem de Bubble Sort, trocando elementos fora de ordem."
  (if (or (null lista) (null (cdr lista)))
      lista
      (let ((primeiro (car lista))
            (segundo (cadr lista))
            (resto (cddr lista)))
        (if (> primeiro segundo)
            (cons segundo (cons primeiro (trocar-elementos resto)))
            (cons primeiro (trocar-elementos (cons segundo resto)))))))

(defun bubble-sort (lista)
  "Ordena a LISTA usando o algoritmo Bubble Sort."
  (let ((nova-lista lista))
    (loop 
      for i from 0 below (length lista) do
      (setf nova-lista (trocar-elementos nova-lista)))
    nova-lista))

;; Exemplo de uso
(let ((lista (list 5 3 8 1 4)))
  (format t "Lista original: ~a~%" lista)
  (format t "Lista ordenada: ~a~%" (bubble-sort lista)))
