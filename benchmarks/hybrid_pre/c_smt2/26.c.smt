(set-logic LIA)

( declare-const n Int )
( declare-const n! Int )
( declare-const x Int )
( declare-const x! Int )

( declare-const n_0 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )

( define-fun inv-f( ( n Int )( x Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( n Int )( x Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int ) ) Bool
	( and
		( = 1 2 )
	)
)

( define-fun trans-f ( ( n Int )( x Int )( n! Int )( x! Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int ) ) Bool
	( or
		( and
			( = x_1 x )
			( = x_1 x! )
			( = n n! )
		)
		( and
			( = x_1 x )
			( > x_1 1 )
			( = x_2 ( - x_1 1 ) )
			( = x_2 x! )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( n Int )( x Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int ) ) Bool
	( or
		( not
			( = x x_1)
		)
		( not
			( and
				( not ( > x_1 1 ) )
				( not ( = x_1 1 ) )
				( not ( < n_0 0 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f n x n_0 x_0 x_1 x_2  )
		( inv-f n x )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f n x )
			( trans-f n x n! x! n_0 x_0 x_1 x_2 )
		)
		( inv-f n! x! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f n x  )
		( post-f n x n_0 x_0 x_1 x_2 )
	)
))

