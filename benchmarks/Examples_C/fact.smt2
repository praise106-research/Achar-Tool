(set-logic LIA)

( declare-const __multiply_arg1_res Int )
( declare-const __multiply_arg1_res! Int )
( declare-const __multiply_arg2_k Int )
( declare-const __multiply_arg2_k! Int )
( declare-const factorial_arg1_n Int )
( declare-const factorial_arg1_n! Int )
( declare-const k Int )
( declare-const k! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const res Int )
( declare-const res! Int )

( declare-const __multiply_arg1_res_0 Int )
( declare-const __multiply_arg2_k_0 Int )
( declare-const factorial_arg1_n_0 Int )
( declare-const k_0 Int )
( declare-const k_1 Int )
( declare-const k_2 Int )
( declare-const k_3 Int )
( declare-const n_0 Int )
( declare-const res_0 Int )
( declare-const res_1 Int )
( declare-const res_2 Int )
( declare-const res_3 Int )

( define-fun inv-f( ( __multiply_arg1_res Int )( __multiply_arg2_k Int )( factorial_arg1_n Int )( k Int )( n Int )( res Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( __multiply_arg1_res Int )( __multiply_arg2_k Int )( factorial_arg1_n Int )( k Int )( n Int )( res Int )( __multiply_arg1_res_0 Int )( __multiply_arg2_k_0 Int )( factorial_arg1_n_0 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int ) ) Bool
	( and
		( = k k_1 )
		( = res res_1 )
		( = k_1 1 )
		( = res_1 1 )
	)
)

( define-fun trans-f ( ( __multiply_arg1_res Int )( __multiply_arg2_k Int )( factorial_arg1_n Int )( k Int )( n Int )( res Int )( __multiply_arg1_res! Int )( __multiply_arg2_k! Int )( factorial_arg1_n! Int )( k! Int )( n! Int )( res! Int )( __multiply_arg1_res_0 Int )( __multiply_arg2_k_0 Int )( factorial_arg1_n_0 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int ) ) Bool
	( or
		( and
			( = k_2 k )
			( = res_2 res )
			( = k_2 k! )
			( = res_2 res! )
			( = n n_0 )
			( = n! n_0 )
			( = __multiply_arg1_res __multiply_arg1_res! )
			( = __multiply_arg2_k __multiply_arg2_k! )
			( = factorial_arg1_n factorial_arg1_n! )
			( = res res! )
		)
		( and
			( = k_2 k )
			( = res_2 res )
			( not ( = k_2 n_0 ) )
			( = k_3 ( + k_2 1 ) )
			( = res_3 ( + __multiply_arg1_res_0 __multiply_arg2_k_0 ) )
			( = k_3 k! )
			( = res_3 res! )
			(= __multiply_arg1_res __multiply_arg1_res_0 )
			(= __multiply_arg1_res! __multiply_arg1_res_0 )
			(= __multiply_arg2_k __multiply_arg2_k_0 )
			(= __multiply_arg2_k! __multiply_arg2_k_0 )
			(= factorial_arg1_n factorial_arg1_n_0 )
			(= factorial_arg1_n! factorial_arg1_n_0 )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( __multiply_arg1_res Int )( __multiply_arg2_k Int )( factorial_arg1_n Int )( k Int )( n Int )( res Int )( __multiply_arg1_res_0 Int )( __multiply_arg2_k_0 Int )( factorial_arg1_n_0 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int ) ) Bool
	( or
		( not
			( and
				( = __multiply_arg1_res __multiply_arg1_res_0 )
				( = __multiply_arg2_k __multiply_arg2_k_0 )
				( = factorial_arg1_n factorial_arg1_n_0 )
				( = k k_2)
				( = n n_0 )
				( = res res_2)
			)
		)
		( not
			( and
				( not ( not ( = k_2 n_0 ) ) )
				( not ( = res_2 factorial_arg1_n_0 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f __multiply_arg1_res __multiply_arg2_k factorial_arg1_n k n res __multiply_arg1_res_0 __multiply_arg2_k_0 factorial_arg1_n_0 k_0 k_1 k_2 k_3 n_0 res_0 res_1 res_2 res_3  )
		( inv-f __multiply_arg1_res __multiply_arg2_k factorial_arg1_n k n res )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f __multiply_arg1_res __multiply_arg2_k factorial_arg1_n k n res )
			( trans-f __multiply_arg1_res __multiply_arg2_k factorial_arg1_n k n res __multiply_arg1_res! __multiply_arg2_k! factorial_arg1_n! k! n! res! __multiply_arg1_res_0 __multiply_arg2_k_0 factorial_arg1_n_0 k_0 k_1 k_2 k_3 n_0 res_0 res_1 res_2 res_3 )
		)
		( inv-f __multiply_arg1_res! __multiply_arg2_k! factorial_arg1_n! k! n! res! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f __multiply_arg1_res __multiply_arg2_k factorial_arg1_n k n res  )
		( post-f __multiply_arg1_res __multiply_arg2_k factorial_arg1_n k n res __multiply_arg1_res_0 __multiply_arg2_k_0 factorial_arg1_n_0 k_0 k_1 k_2 k_3 n_0 res_0 res_1 res_2 res_3 )
	)
))

