;(set-logic ALL)
; (set-option :produce-proofs true)
; (set-option :produce-models true)
(set-logic HORN)
(declare-rel itp (Int Int))
(declare-rel simplequery ())
(declare-var A Int)
(declare-var B Int)
(declare-var C Int)
(declare-var D Int)
(rule (=> (and (not (<= A B)) (= B 0)) (itp B A)))
(rule (=> (and (itp D C) (= A (+ 2 C)) (= B (+ 1 D))) (itp B A)))
(rule (=> (and (itp A B) (<= B 20) (not (<= A 10))) simplequery))
;(query simple!!query :print-certificate true)
(query simplequery)
