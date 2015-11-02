;; marge sort

(defun marge (a b) (if (not a) b (if (< (car a) (car b))
										 (cons (car a)(marge (cdr a) b))
										 (cons (car b)(marge (cdr b) a)))))

(defun en (n) (last n (/ (length n) 2)))
(defun beg (n) (ldiff n (en n)))

(diff '(1 2) '(1))

(defun marge-sort (n)
	(if (cdr n) (marge (marge-sort (beg n))(marge-sort (en n)))
		n ))

;; quick sort

(defun qsort (n)
	(if (not n) n (cons (car n)
											(append (qsort (select (cdr n) (car n) '<=))
											(qsort (select (cdr n) (car n) '>))))))

(defun select (l v cmp) (if (not l)
														l (if (funcall cmp (car l) v)
																	(cons (car l) (select (cdr l) v cmp))
																(select (cdr l) v cmp))))

(defun ens (s) (subseq s (/ (length s) 2) (length s)))
(defun begs (s) (subseq s 0 (/ (length s) 2)))

;; match open and close (ex '(' and ')')

(defun match (s co cc) (if (= (length s) 1) (if (string= s cc) (cons 0 1) (if (string= s co) (cons 1 0) (cons 0 0)))
									 (if (= (length s) 0) (cons 0 0) (cons (+ (car (match (ens s) co cc))
												(if (> (- (car (match (begs s) co cc))(cdr (match (ens s) co cc))) 0)
														(- (car (match (begs s) co cc))(cdr (match (ens s) co cc))) 0))
										 (+ (cdr (match (begs s) co cc))
												(if (< (- (car (match (begs s) co cc))(cdr (match (ens s) co cc))) 0)
														(- (cdr (match (ens s) co cc))(car (match (begs s) co cc))) 0))))))

;; factorial

(defun fac (n) (if (= n 0) 1 (* n (fac (- n 1)))))

;; gcd and lcm

(defun gcd (a b) (if (< a b) (if (= (% b a) 0) a (gcd a (% b a)))
									 (if (= (% a b) 0) b (gcd b (% a b)))))

(defun lcm (a b) (/ (* a b) (gcd a b)))

;; evaluate polynome

(defun eval_pol (n x)
	(if (not n) 0 (+ (car n) (* (eval_pol (cdr n) x) x))))

;; 
