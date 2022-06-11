(set-logic LIA)

( declare-primed-var __multiply_arg1_res Int )
( declare-primed-var k Int )
( declare-primed-var n Int )
( declare-primed-var res Int )

( declare-primed-var __multiply_arg1_res_0 Int )
( declare-primed-var __multiply_arg1_res_1 Int )
( declare-primed-var __multiply_arg1_res_2 Int )
( declare-primed-var k_0 Int )
( declare-primed-var k_1 Int )
( declare-primed-var k_2 Int )
( declare-primed-var k_3 Int )
( declare-primed-var n_0 Int )
( declare-primed-var res_0 Int )
( declare-primed-var res_1 Int )
( declare-primed-var res_2 Int )
( declare-primed-var res_3 Int )

( synth-inv inv-f( ( __multiply_arg1_res Int )( k Int )( n Int )( res Int )( __multiply_arg1_res_0 Int )( __multiply_arg1_res_1 Int )( __multiply_arg1_res_2 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int ) ) )

( define-fun pre-f ( ( __multiply_arg1_res Int )( k Int )( n Int )( res Int )( __multiply_arg1_res_0 Int )( __multiply_arg1_res_1 Int )( __multiply_arg1_res_2 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int ) ) Bool
	( and
		( = k k_1 )
		( = res res_1 )
		( = k_1 1 )
		( = res_1 1 )
	)
)

( define-fun trans-f ( ( __multiply_arg1_res Int )( k Int )( n Int )( res Int )( __multiply_arg1_res_0 Int )( __multiply_arg1_res_1 Int )( __multiply_arg1_res_2 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int )( __multiply_arg1_res! Int )( k! Int )( n! Int )( res! Int )( __multiply_arg1_res_0! Int )( __multiply_arg1_res_1! Int )( __multiply_arg1_res_2! Int )( k_0! Int )( k_1! Int )( k_2! Int )( k_3! Int )( n_0! Int )( res_0! Int )( res_1! Int )( res_2! Int )( res_3! Int ) ) Bool
	( or
		( and
			( = __multiply_arg1_res_1 __multiply_arg1_res )
			( = k_2 k )
			( = res_2 res )
			( = __multiply_arg1_res_1 __multiply_arg1_res! )
			( = k_2 k! )
			( = res_2 res! )
			( = n n_0 )
			( = n! n_0 )
			( = __multiply_arg1_res __multiply_arg1_res! )
			( = res res! )
		)
		( and
			( = __multiply_arg1_res_1 __multiply_arg1_res )
			( = k_2 k )
			( = res_2 res )
			( not ( = k_2 n_0 ) )
			( = k_3 ( + k_2 1 ) )
			( = __multiply_arg1_res_2 res_2 )
			( = res_3 ( * res_2 k_3 ) )
			( = __multiply_arg1_res_2 __multiply_arg1_res! )
			( = k_3 k! )
			( = res_3 res! )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( __multiply_arg1_res Int )( k Int )( n Int )( res Int )( __multiply_arg1_res_0 Int )( __multiply_arg1_res_1 Int )( __multiply_arg1_res_2 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int ) ) Bool
	( or
		( not
			( and
				( = __multiply_arg1_res __multiply_arg1_res_1)
				( = k k_2)
				( = n n_0 )
				( = res res_2)
			)
		)
		( not
			( and
				( not ( not ( = k_2 n_0 ) ) )
				( not ( = res_2 ( * k_2 __multiply_arg1_res_1 ) ) )
			)
		)
	)
)

( inv-constraint inv-f pre-f trans-f post-f )
( check-synth )
