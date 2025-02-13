;1st 
(define (A m n)
  (cond
    ((= m 0) (+ n 1))
    ((= n 0) (A (- m 1) 1))
    (else (A (- m 1) (A m (- n 1))))))
;2nd
( define (T p q a b)
  (cond
    ((and (= p 1) (= q 1)) (* a b))
    ((and (= p 1) (= q 2))(* (+ a b)))
    ((and (= p 2) (= q 1))(* 3.14 (* a a)))
    ((and(= p 2)(= q 2))(* 2 3.14 a))
    (else (/ (* a b) 2))))

;4th

(define (fact n)
    (if (= n 0) 1
    (* n(fact(- n 1)))))
;5th
( define (fib n)
  ( if (<= n 1) n
      (+ (fib (- n 1)(fib - n 2)))))
;6th
(define (findLargest ls)
    (if (null? (cdr ls))(car ls)
        (max (car ls)(findLargest (cdr ls)))))



;7th
( define (sumN n)
  ( if (= n 0) 0
    (+ n (sumN(- n 1)))))


(display(fact 5))
(newline)