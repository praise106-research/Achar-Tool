(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const b Int )
( declare-const b! Int )
( declare-const i Int )
( declare-const i! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const res Int )
( declare-const res! Int )

( declare-const a_0 Int )
( declare-const b_0 Int )
( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const n_0 Int )
( declare-const res_0 Int )
( declare-const res_1 Int )
( declare-const res_2 Int )

( define-fun inv-f( ( a Int )( b Int )( i Int )( n Int )( res Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( b Int )( i Int )( n Int )( res Int )( a_0 Int )( b_0 Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int ) ) Bool
	( and
		( = a a_0 )
		( = b b_0 )
		( = n n_0 )
		( >= n_0 0 )
		( < ( + ( + a_0 b_0 ) n_0 ) 10000 )
	)
)

( define-fun trans-f ( ( a Int )( b Int )( i Int )( n Int )( res Int )( a! Int )( b! Int )( i! Int )( n! Int )( res! Int )( a_0 Int )( b_0 Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int ) ) Bool
	( or
		( and
			( = i_1 i )
			( = res_1 res )
			( = i_1 i! )
			( = res_1 res! )
			( = n n_0 )
			( = n! n_0 )
			( = a a! )
			( = b b! )
			( = res res! )
		)
		( and
			( = i_1 i )
			( = res_1 res )
			( <= i_1 n_0 )
			( = res_2 ( + ( + ( + ( + ( + ( + ( + ( + ( +   )  ) ( * ( * 3 ( * a_0 a_0 ) ) b_0 ) ) ( * ( * 3 a_0 ) ( * b_0 b_0 ) ) ) ( * ( * ( * 3 a_0 ) a_0 ) i_1 ) ) ( * ( * ( * 3 a_0 ) i_1 ) i_1 ) ) ( * ( * ( * 3 b_0 ) b_0 ) i_1 ) ) ( * ( * ( * 3 b_0 ) i_1 ) i_1 ) ) ( * ( * ( * 6 a_0 ) b_0 ) i_1 ) ) )
			( = i_2 ( + i_1 1 ) )
			( = i_2 i! )
			( = res_2 res! )
			(= a a_0 )
			(= a! a_0 )
			(= b b_0 )
			(= b! b_0 )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( a Int )( b Int )( i Int )( n Int )( res Int )( a_0 Int )( b_0 Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( res_0 Int )( res_1 Int )( res_2 Int ) ) Bool
	( or
		( not
			( and
				( = a a_0)
				( = b b_0)
				( = i i_1)
				( = n n_0)
				( = res res_1)
			)
		)
		( not
			( and
				( not ( <= i_1 n_0 ) )
				( not ( = res_1 ( * ( * ( + ( + a_0 b_0 ) n_0 ) ( + ( + a_0 b_0 ) n_0 ) ) ( + ( + a_0 b_0 ) n_0 ) ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a b i n res a_0 b_0 i_0 i_1 i_2 n_0 res_0 res_1 res_2  )
		( inv-f a b i n res )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a b i n res )
			( trans-f a b i n res a! b! i! n! res! a_0 b_0 i_0 i_1 i_2 n_0 res_0 res_1 res_2 )
		)
		( inv-f a! b! i! n! res! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a b i n res  )
		( post-f a b i n res a_0 b_0 i_0 i_1 i_2 n_0 res_0 res_1 res_2 )
	)
))

