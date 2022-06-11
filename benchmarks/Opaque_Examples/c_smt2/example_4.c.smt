(set-logic LIA)

( declare-const c Int )
( declare-const c! Int )
( declare-const i Int )
( declare-const i! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const c_0 Int )
( declare-const c_1 Int )
( declare-const c_2 Int )
( declare-const c_3 Int )
( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const n_0 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_3 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )
( declare-const y_2 Int )
( declare-const y_3 Int )

( define-fun inv-f( ( c Int )( i Int )( n Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( c Int )( i Int )( n Int )( x Int )( y Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( i_0 Int )( i_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( and
		( = c c_1 )
		( = i i_1 )
		( = n n_0 )
		( = x x_1 )
		( = y y_1 )
		( > n_0 0 )
		( = x_1 0 )
		( = y_1 1 )
		( = i_1 0 )
		( = c_1 0 )
	)
)

( define-fun trans-f ( ( c Int )( i Int )( n Int )( x Int )( y Int )( c! Int )( i! Int )( n! Int )( x! Int )( y! Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( i_0 Int )( i_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( or
		( and
			( = c_2 c )
			( = x_2 x )
			( = y_2 y )
			( = c_2 c! )
			( = x_2 x! )
			( = y_2 y! )
			( = i i_1 )
			( = i! i_1 )
			( = n n_0 )
			( = n! n_0 )
			( = c c! )
			( = x x! )
			( = y y! )
		)
		( and
			( = c_2 c )
			( = x_2 x )
			( = y_2 y )
			( < i_1 n_0 )
			( = c_3  )
			( = x_3 y_2 )
			( = y_3 c_3 )
			( = c_3 c! )
			( = x_3 x! )
			( = y_3 y! )
			(= i i_1 )
			(= i! i_1 )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( c Int )( i Int )( n Int )( x Int )( y Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( i_0 Int )( i_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = c c_2)
					( = i i_1)
					( = n n_0)
					( = x x_2)
					( = y y_2)
				)
			)
			( not
				( and
					( not ( < i_1 n_0 ) )
					( <= ( <= 0 i_1 ) n_0 )
					( not ( and ( <= ( <= 0 i_1 ) n_0 ) ( = x_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = c c_2)
					( = i i_1)
					( = n n_0)
					( = x x_2)
					( = y y_2)
				)
			)
			( not
				( and
					( not ( < i_1 n_0 ) )
					( not ( <= ( <= 0 i_1 ) n_0 ) )
					( not ( and ( <= ( <= 0 i_1 ) n_0 ) ( = x_2  ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f c i n x y c_0 c_1 c_2 c_3 i_0 i_1 n_0 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3  )
		( inv-f c i n x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f c i n x y )
			( trans-f c i n x y c! i! n! x! y! c_0 c_1 c_2 c_3 i_0 i_1 n_0 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 )
		)
		( inv-f c! i! n! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f c i n x y  )
		( post-f c i n x y c_0 c_1 c_2 c_3 i_0 i_1 n_0 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 )
	)
))

