(set-logic LIA)

( declare-const x Int )
( declare-const x! Int )

( declare-const x_0 Int )
( declare-const x_1 Int )

( define-fun inv-f( ( x Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( x Int )( x_0 Int )( x_1 Int ) ) Bool
	( and
		( = x x_1 )
		( = x_1 0 )
	)
)

( define-fun trans-f ( ( x Int )( x! Int )( x_0 Int )( x_1 Int ) ) Bool
	( or
		( and
			( = x x_1 )
			( = x! x_1 )
		)
		( and
			( < x_1 100 )
			( = 1 2 )
			(= x x_1 )
			(= x! x_1 )
		)
	)
)

( define-fun post-f ( ( x Int )( x_0 Int )( x_1 Int ) ) Bool
	( or
		( not
			( = x x_1)
		)
		( not
			( and
				( not ( < x_1 100 ) )
				( not ( = x_1 100 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f x x_0 x_1  )
		( inv-f x )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f x )
			( trans-f x x! x_0 x_1 )
		)
		( inv-f x! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f x  )
		( post-f x x_0 x_1 )
	)
))

