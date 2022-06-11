(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const b Int )
( declare-const b! Int )
( declare-const result Int )
( declare-const result! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const a_0 Int )
( declare-const a_1 Int )
( declare-const a_2 Int )
( declare-const b_0 Int )
( declare-const b_1 Int )
( declare-const b_2 Int )
( declare-const result_0 Int )
( declare-const result_1 Int )
( declare-const result_2 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )

( define-fun inv-f( ( a Int )( b Int )( result Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( b Int )( result Int )( x Int )( y Int )( a_0 Int )( a_1 Int )( a_2 Int )( b_0 Int )( b_1 Int )( b_2 Int )( result_0 Int )( result_1 Int )( result_2 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( = a a_0 )
		( = b b_0 )
		( = x x_1 )
		( = y y_1 )
		( = x_1 a_0 )
		( = y_1 b_0 )
	)
)

( define-fun trans-f ( ( a Int )( b Int )( result Int )( x Int )( y Int )( a! Int )( b! Int )( result! Int )( x! Int )( y! Int )( a_0 Int )( a_1 Int )( a_2 Int )( b_0 Int )( b_1 Int )( b_2 Int )( result_0 Int )( result_1 Int )( result_2 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( and
			( = a_1 a )
			( = b_1 b )
			( = result_1 result )
			( = a_1 a! )
			( = b_1 b! )
			( = result_1 result! )
			( = result result! )
			( = x x! )
			( = y y! )
		)
		( and
			( = a_1 a )
			( = b_1 b )
			( = result_1 result )
			( not ( = ( mod a_1 b_1 ) 0 ) )
			( = result_2  )
			( = a_2 b_1 )
			( = b_2 result_2 )
			( = a_2 a! )
			( = b_2 b! )
			( = result_2 result! )
			(= x x_1 )
			(= x! x_1 )
			(= y y_1 )
			(= y! y_1 )
		)
	)
)

( define-fun post-f ( ( a Int )( b Int )( result Int )( x Int )( y Int )( a_0 Int )( a_1 Int )( a_2 Int )( b_0 Int )( b_1 Int )( b_2 Int )( result_0 Int )( result_1 Int )( result_2 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( not
			( and
				( = a a_1)
				( = b b_1)
				( = result result_1)
				( = x x_1)
				( = y y_1)
			)
		)
		( not
			( and
				( not ( not ( = ( mod a_1 b_1 ) 0 ) ) )
				( not ( = b_1  ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a b result x y a_0 a_1 a_2 b_0 b_1 b_2 result_0 result_1 result_2 x_0 x_1 y_0 y_1  )
		( inv-f a b result x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a b result x y )
			( trans-f a b result x y a! b! result! x! y! a_0 a_1 a_2 b_0 b_1 b_2 result_0 result_1 result_2 x_0 x_1 y_0 y_1 )
		)
		( inv-f a! b! result! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a b result x y  )
		( post-f a b result x y a_0 a_1 a_2 b_0 b_1 b_2 result_0 result_1 result_2 x_0 x_1 y_0 y_1 )
	)
))

