; 1st 
(define (A m n)
  (cond
    ((= m 0) (+ n 1))
    ((= n 0) (A (- m 1) 1))
    (else (A (- m 1) (A m (- n 1))))))

; 2nd 
(define (T p q a b)
  (cond
    ((and (= p 1) (= q 1)) (* a b))
    ((and (= p 1) (= q 2)) (* 2 (+ a b))) 
    ((and (= p 2) (= q 1)) (* 3.14 (* a a)))
    ((and (= p 2) (= q 2)) (* 2 3.14 a))
    (else (/ (* a b) 2)))) 

; 3rd 
(define (addcomplex c1 c2)
  (cons (+ (car c1) (car c2)) (+ (cdr c1) (cdr c2))))

; 4th 
(define (fact n)
  (if (= n 0) 1
      (* n (fact (- n 1)))))

; 5th 
(define (fib n)
  (if (<= n 1) n
      (+ (fib (- n 1)) (fib (- n 2)))))  

; 6th -
(define (findLargest ls)
  (if (null? (cdr ls)) (car ls)
      (max (car ls) (findLargest (cdr ls)))))

; 7th -
(define (sumN n)
  (if (= n 0) 0
      (+ n (sumN (- n 1)))))

; Test Cases
(display "Ackermann : A(1,2) -> ") (display (A 1 2)) (newline)
(display "T : T(1,2,3,4) -> ") (display (T 1 2 3 4)) (newline)
(display "Complex Addition: (3+4i) + (1+2i) -> ") 
(display (addcomplex (cons 3 4) (cons 1 2))) (newline)
(display "Factorial : 5! -> ") (display (fact 5)) (newline)
(display "Fibonacci : fib(7) -> ") (display (fib 7)) (newline)
(display "Largest Number : (4 7 2 9 1) -> ") 
(display (findLargest '(4 7 2 9 1))) (newline)
(display "Sum of N : sum(5) -> ") (display (sumN 5)) (newline)
