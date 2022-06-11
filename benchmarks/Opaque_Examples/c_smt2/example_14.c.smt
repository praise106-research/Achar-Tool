(set-logic LIA)

( declare-const k Int )
( declare-const k! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const res Int )
( declare-const res! Int )

( declare-const k_0 Int )
( declare-const k_1 Int )
( declare-const k_2 Int )
( declare-const k_3 Int )
( declare-const n_0 Int )
( declare-const res_0 Int )
( declare-const res_1 Int )

( define-fun inv-f( ( k Int )( n Int )( res Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( k Int )( n Int )( res Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int ) ) Bool
	( and
		( = k k_1 )
		( = res res_1 )
		( = k_1 1 )
		( = res_1 1 )
	)
)

( define-fun trans-f ( ( k Int )( n Int )( res Int )( k! Int )( n! Int )( res! Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int ) ) Bool
	( or
		( and
			( = k_2 k )
			( = k_2 k! )
			( = n n_0 )
			( = n! n_0 )
			( = res res! )
		)
		( and
			( = k_2 k )
			( not ( = k_2 n_0 ) )
			( = k_3 ( + k_2 1 ) )
			( = k_3 k! )
			(= n n_0 )
			(= n! n_0 )
			(= res res_1 )
			(= res! res_1 )
		)
	)
)

( define-fun post-f ( ( k Int )( n Int )( res Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( res_0 Int )( res_1 Int ) ) Bool
	( or
		( not
			( and
				( = k k_2)
				( = n n_0 )
				( = res res_1)
			)
		)
		( not
			( and
				( not ( not ( = k_2 n_0 ) ) )
				( not ( = res_1  ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f k n res k_0 k_1 k_2 k_3 n_0 res_0 res_1  )
		( inv-f k n res )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f k n res )
			( trans-f k n res k! n! res! k_0 k_1 k_2 k_3 n_0 res_0 res_1 )
		)
		( inv-f k! n! res! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f k n res  )
		( post-f k n res k_0 k_1 k_2 k_3 n_0 res_0 res_1 )
	)
))

