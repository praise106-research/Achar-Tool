(set-info :original "/tmp/sea-5LxjqH/71.pp.ms.o.bc")
(set-info :authors "SeaHorn v.0.1.0-rc3")
(declare-rel verifier.error (Bool Bool Bool ))
(declare-rel main@entry (Int ))
(declare-rel main@_bb (Int Int Int ))
(declare-rel main@verifier.error.split ())
(declare-var main@%.not.i_0 Bool )
(declare-var main@%_19_0 Bool )
(declare-var main@%or.cond.i_0 Bool )
(declare-var main@%_20_0 Bool )
(declare-var main@%_10_0 Int )
(declare-var main@%_11_0 Int )
(declare-var main@%_12_0 Bool )
(declare-var main@%_0_0 Int )
(declare-var main@%_2_0 Int )
(declare-var main@%_3_0 Int )
(declare-var main@%_4_0 Int )
(declare-var main@%_6_0 Bool )
(declare-var main@%_7_0 Bool )
(declare-var @unknown_0 Int )
(declare-var main@entry_0 Bool )
(declare-var main@%_8_0 Int )
(declare-var main@_bb_0 Bool )
(declare-var main@%c.0.i_0 Int )
(declare-var main@%z.0.i_0 Int )
(declare-var main@%c.0.i_1 Int )
(declare-var main@%z.0.i_1 Int )
(declare-var main@%_13_0 Bool )
(declare-var main@_bb1_0 Bool )
(declare-var main@_bb2_0 Bool )
(declare-var main@%_16_0 Int )
(declare-var main@%_17_0 Int )
(declare-var main@_bb_1 Bool )
(declare-var |tuple(main@_bb1_0, main@_bb_1)| Bool )
(declare-var main@%c.0.i_2 Int )
(declare-var main@%z.0.i_2 Int )
(declare-var main@%c.0.i_3 Int )
(declare-var main@%z.0.i_3 Int )
(declare-var main@_bb3_0 Bool )
(declare-var main@_bb4_0 Bool )
(declare-var main@verifier.error_0 Bool )
(declare-var main@verifier.error.split_0 Bool )
(rule (verifier.error false false false))
(rule (verifier.error false true true))
(rule (verifier.error true false true))
(rule (verifier.error true true true))
(rule (main@entry @unknown_0))
(rule (let ((a!1 (and (main@entry @unknown_0)
                true
                (= main@%_0_0 @unknown_0)
                (= main@%_2_0 @unknown_0)
                (= main@%_4_0 @unknown_0)
                (= main@%_6_0 (> main@%_3_0 (- 1)))
                main@%_6_0
                (= main@%_7_0 (ite (>= main@%_3_0 0) (< 126 main@%_3_0) true))
                main@%_7_0
                (= main@%_8_0 (* main@%_3_0 36))
                (=> main@_bb_0 (and main@_bb_0 main@entry_0))
                main@_bb_0
                (=> (and main@_bb_0 main@entry_0) (= main@%c.0.i_0 0))
                (=> (and main@_bb_0 main@entry_0) (= main@%z.0.i_0 main@%_8_0))
                (=> (and main@_bb_0 main@entry_0)
                    (= main@%c.0.i_1 main@%c.0.i_0))
                (=> (and main@_bb_0 main@entry_0)
                    (= main@%z.0.i_1 main@%z.0.i_0)))))
  (=> a!1 (main@_bb main@%z.0.i_1 main@%c.0.i_1 @unknown_0))))
(rule (let ((a!1 (and (main@_bb main@%z.0.i_0 main@%c.0.i_0 @unknown_0)
                true
                (= main@%_10_0 @unknown_0)
                (= main@%_12_0 (= main@%_11_0 0))
                (= main@%_13_0 (< main@%c.0.i_0 36))
                (=> main@_bb1_0 (and main@_bb1_0 main@_bb_0))
                (=> (and main@_bb1_0 main@_bb_0) (not main@%_12_0))
                (=> main@_bb2_0 (and main@_bb2_0 main@_bb1_0))
                (=> (and main@_bb2_0 main@_bb1_0) main@%_13_0)
                (=> main@_bb2_0 (= main@%_16_0 (+ main@%z.0.i_0 1)))
                (=> main@_bb2_0 (= main@%_17_0 (+ main@%c.0.i_0 1)))
                (=> |tuple(main@_bb1_0, main@_bb_1)| main@_bb1_0)
                (=> main@_bb_1
                    (or (and main@_bb_1 main@_bb2_0)
                        (and main@_bb1_0 |tuple(main@_bb1_0, main@_bb_1)|)))
                main@_bb_1
                (=> (and main@_bb_1 main@_bb2_0) (= main@%c.0.i_1 main@%_17_0))
                (=> (and main@_bb_1 main@_bb2_0) (= main@%z.0.i_1 main@%_16_0))
                (=> (and main@_bb1_0 |tuple(main@_bb1_0, main@_bb_1)|)
                    (not main@%_13_0))
                (=> (and main@_bb1_0 |tuple(main@_bb1_0, main@_bb_1)|)
                    (= main@%c.0.i_2 main@%c.0.i_0))
                (=> (and main@_bb1_0 |tuple(main@_bb1_0, main@_bb_1)|)
                    (= main@%z.0.i_2 main@%z.0.i_0))
                (=> (and main@_bb_1 main@_bb2_0)
                    (= main@%c.0.i_3 main@%c.0.i_1))
                (=> (and main@_bb_1 main@_bb2_0)
                    (= main@%z.0.i_3 main@%z.0.i_1))
                (=> (and main@_bb1_0 |tuple(main@_bb1_0, main@_bb_1)|)
                    (= main@%c.0.i_3 main@%c.0.i_2))
                (=> (and main@_bb1_0 |tuple(main@_bb1_0, main@_bb_1)|)
                    (= main@%z.0.i_3 main@%z.0.i_2)))))
  (=> a!1 (main@_bb main@%z.0.i_3 main@%c.0.i_3 @unknown_0))))
(rule (let ((a!1 (and (main@_bb main@%z.0.i_0 main@%c.0.i_0 @unknown_0)
                true
                (= main@%_10_0 @unknown_0)
                (= main@%_12_0 (= main@%_11_0 0))
                (= main@%_13_0 (< main@%c.0.i_0 36))
                (=> main@_bb3_0 (and main@_bb3_0 main@_bb_0))
                (=> (and main@_bb3_0 main@_bb_0) main@%_12_0)
                (=> main@_bb3_0 (= main@%.not.i_0 (xor main@%_13_0 true)))
                (=> main@_bb3_0 (= main@%_19_0 (> main@%z.0.i_0 (- 1))))
                (=> main@_bb3_0
                    (= main@%or.cond.i_0 (or main@%_19_0 main@%.not.i_0)))
                (=> main@_bb3_0 (not main@%or.cond.i_0))
                (=> main@_bb3_0 (= main@%_20_0 (xor main@%or.cond.i_0 true)))
                (=> main@_bb4_0 (and main@_bb4_0 main@_bb3_0))
                (=> main@verifier.error_0
                    (and main@verifier.error_0 main@_bb4_0))
                (=> main@verifier.error.split_0
                    (and main@verifier.error.split_0 main@verifier.error_0))
                main@verifier.error.split_0)))
  (=> a!1 main@verifier.error.split)))
(query main@verifier.error.split)

