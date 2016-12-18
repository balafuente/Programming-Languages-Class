;Blake LaFuente
;Assignment 5

; Function 1: returns the number of lists in a given list L

(defun f1 (L)
  (cond ((null L) 0)                           ;if L is empty, there are zero lists
        ((listp (car L)) ( + 1 (f1 (cdr L))))  ;if first element of L is a list
                                               ;then count lists in cdr of L
                                               ;and add 1
        (T (f1 (cdr L)))                       ;else count lists in cdr of L
  )
)

; Function 2: Decides whether a given list L has an atom inside

(defun f2 (L)
  (cond ((null L) nil)                    ; return nil if L is empty
        ((atom (car L))T)                 ; return True if the head is an atom
        (T (f2 (cdr L)))                  ; else check the rest of L for atoms
  )
)

; Function 3: Takes a list of integers L and returns a list
;             containing only odd integers in L

(defun f3 (L)
  (cond ((null L) nil)                     ;if L is empty, there are no odd integers
        ((oddp(car L)) (cons (car L)  (f3(cdr L))))
                                           ;if first integer of L is odd then
                                           ;add it to the returned list
        (T (f3 (cdr L)))                   ;else check the rest of L for odds
  ) 
)

; Function 4: Returns the last element in a given list L

(defun f4 (L)
  (cond ((null L) nil)                     ;nil if L is empty
        ((equal (length L) 1) (car L))     ;if L has length 1 the last element
                                           ; is first element of L
        (T (f4 (cdr L)))                   ;else find last element of cdr of L
  )
)

; Function 5: Returns the reverse of a given list L

(defun f5 (L)
  (cond ((null L) L)                 ;if L is empty, then reverse is empty
        (T (append (f5 (cdr L)) (list (car L))))
                                     ; else reverse cdr of L and append first
                                     ; element of L at the end
  )
)

; Function 6: returns the first list of a given list L

(defun f6 (L)
  (cond ((null L) L)                  ;if L is empty, return L
        ((listp (car L)) (car L))     ;if car L is a list, return car L
        (T (f6(cdr L)))               ;else look for the first list in cdr L
  )
)

; Function 7: returns the list containing the lists of a given list L

(defun f7 (L)
  (cond ((null L) nil)                  ;if L is empty, return nil
        ((listp (car L)) (cons (car L) (f7(cdr L))))
                                        ;if first element of L is a list, then insert
                                        ;it into returned list
        (T (f7(cdr L)))                 ;else find list of lists in cdr of L
  )
)

; Function 8: returns the product of all integers everywhere in a given list L

(defun f8 (L)
  (cond ((null L) 1)                      ; if L is empty, return nil
        (T (* (car L) (f8(cdr L))))       ; else multiply the head of L
                                          ; by the rest of L
  )
)


;in_list: Function 9 and 10 helper function that checks
; if an element i has a duplicate in list L
(defun in_list(i L)
(cond ((null L) L)                    ;if list L is null, return L
    ((equal i (car L)) T)             ;if i equals car L, return T
    (T (in_list i (cdr L))))          ;else check the rest of the list
)

; Function 9: removes duplicates from a given list L

(defun f9 (L)
 (cond ((null L) L)  						;if L is empty, return L
  ((in_list (car L) (cdr L )) (f9 (cdr L)))
                                            ; if the head of L is in the rest
                                            ; of L, skip it
         (T (cons (car L) (f9 (cdr L))))    ; else include it
                                            ; and check the rest of L
  )
)

; Function 10: returns the intersection of two lists L and M

(defun f10 (L M)
  (cond ((null L) nil)              ;if L is empty, return L
  		((in_list (car L) M) (cons (car L) (f10(cdr L) M)))
                                	;if the head of L is in M, add to returned list
  		(T(f10(cdr L)  M))          ;else check the rest of L
  )
)
