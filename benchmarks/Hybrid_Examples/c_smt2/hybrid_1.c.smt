(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const b Int )
( declare-const b! Int )
( declare-const r Int )
( declare-const r! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const a_0 Int )
( declare-const b_0 Int )
( declare-const b_1 Int )
( declare-const b_2 Int )
( declare-const r_0 Int )
( declare-const r_1 Int )
( declare-const r_2 Int )
( declare-const r_3 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )

( define-fun inv-f( ( a Int )( b Int )( r Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( b Int )( r Int )( x Int )( y Int )( a_0 Int )( b_0 Int )( b_1 Int )( b_2 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( = a a_0 )
		( = b b_0 )
		( = r r_1 )
		( = x x_1 )
		( = y y_1 )
		( >= b_0 0 )
		( = x_1 a_0 )
		( = y_1 b_0 )
		( = r_1 0 )
	)
)

( define-fun trans-f ( ( a Int )( b Int )( r Int )( x Int )( y Int )( a! Int )( b! Int )( r! Int )( x! Int )( y! Int )( a_0 Int )( b_0 Int )( b_1 Int )( b_2 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( and
			( = b_1 b )
			( = r_2 r )
			( = b_1 b! )
			( = r_2 r! )
			( = a a! )
			( = r r! )
			( = x x! )
			( = y y! )
		)
		( and
			( = b_1 b )
			( = r_2 r )
			( not ( = b_1 0 ) )
			( = r_3 ( + r_2 a_0 ) )
			( = b_2 ( - b_1 1 ) )
			( = b_2 b! )
			( = r_3 r! )
			(= a a_0 )
			(= a! a_0 )
			(= x x_1 )
			(= x! x_1 )
			(= y y_1 )
			(= y! y_1 )
		)
	)
)

( define-fun post-f ( ( a Int )( b Int )( r Int )( x Int )( y Int )( a_0 Int )( b_0 Int )( b_1 Int )( b_2 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( not
			( and
				( = a a_0)
				( = b b_1)
				( = r r_2)
				( = x x_1)
				( = y y_1)
			)
		)
		( not
			( and
				( not ( not ( = b_1 0 ) ) )
				( not ( = r_2 ( * x_1 y_1 ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a b r x y a_0 b_0 b_1 b_2 r_0 r_1 r_2 r_3 x_0 x_1 y_0 y_1  )
		( inv-f a b r x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a b r x y )
			( trans-f a b r x y a! b! r! x! y! a_0 b_0 b_1 b_2 r_0 r_1 r_2 r_3 x_0 x_1 y_0 y_1 )
		)
		( inv-f a! b! r! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a b r x y  )
		( post-f a b r x y a_0 b_0 b_1 b_2 r_0 r_1 r_2 r_3 x_0 x_1 y_0 y_1 )
	)
))

