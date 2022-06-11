(set-logic LIA)

( declare-const size Int )
( declare-const size! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )
( declare-const z Int )
( declare-const z! Int )

( declare-const size_0 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_3 Int )
( declare-const y_0 Int )
( declare-const z_0 Int )

( define-fun inv-f( ( size Int )( x Int )( y Int )( z Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( size Int )( x Int )( y Int )( z Int )( size_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( z_0 Int ) ) Bool
	( and
		( = x x_1 )
		( = x_1 0 )
	)
)

( define-fun trans-f ( ( size Int )( x Int )( y Int )( z Int )( size! Int )( x! Int )( y! Int )( z! Int )( size_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( z_0 Int ) ) Bool
	( or
		( and
			( = x_2 x )
			( = x_2 x! )
			( = size size_0 )
			( = size! size_0 )
			( = y y! )
			( = z z! )
		)
		( and
			( = x_2 x )
			( < x_2 size_0 )
			( = x_3 ( + x_2 1 ) )
			( <= z_0 y_0 )
			( = 1 0 )
			( = x_3 x! )
			(= size size_0 )
			(= size! size_0 )
			(= y y_0 )
			(= y! y_0 )
			(= z z_0 )
			(= z! z_0 )
		)
		( and
			( = x_2 x )
			( < x_2 size_0 )
			( = x_3 ( + x_2 1 ) )
			( not ( <= z_0 y_0 ) )
			( = x_3 x! )
			(= size size_0 )
			(= size! size_0 )
			(= y y_0 )
			(= y! y_0 )
			(= z z_0 )
			(= z! z_0 )
		)
	)
)

( define-fun post-f ( ( size Int )( x Int )( y Int )( z Int )( size_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( z_0 Int ) ) Bool
	( or
		( not
			( and
				( = size size_0 )
				( = x x_2)
				( = y y_0 )
				( = z z_0 )
			)
		)
		( not
			( and
				( not ( < x_2 size_0 ) )
				( > size_0 0 )
				( not ( >= z_0 y_0 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f size x y z size_0 x_0 x_1 x_2 x_3 y_0 z_0  )
		( inv-f size x y z )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f size x y z )
			( trans-f size x y z size! x! y! z! size_0 x_0 x_1 x_2 x_3 y_0 z_0 )
		)
		( inv-f size! x! y! z! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f size x y z  )
		( post-f size x y z size_0 x_0 x_1 x_2 x_3 y_0 z_0 )
	)
))

