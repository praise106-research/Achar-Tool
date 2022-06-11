(set-logic LIA)

( declare-const c Int )
( declare-const c! Int )
( declare-const x1 Int )
( declare-const x1! Int )
( declare-const x2 Int )
( declare-const x2! Int )
( declare-const x3 Int )
( declare-const x3! Int )
( declare-const y Int )
( declare-const y! Int )
( declare-const z Int )
( declare-const z! Int )
( declare-const tmp Int )
( declare-const tmp! Int )

( declare-const c_0 Int )
( declare-const c_1 Int )
( declare-const c_2 Int )
( declare-const c_3 Int )
( declare-const x1_0 Int )
( declare-const x2_0 Int )
( declare-const x3_0 Int )
( declare-const y_0 Int )
( declare-const z_0 Int )
( declare-const z_1 Int )
( declare-const z_2 Int )
( declare-const z_3 Int )
( declare-const z_4 Int )

( define-fun inv-f( ( c Int )( x1 Int )( x2 Int )( x3 Int )( y Int )( z Int )( tmp Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( c Int )( x1 Int )( x2 Int )( x3 Int )( y Int )( z Int )( tmp Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( x1_0 Int )( x2_0 Int )( x3_0 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int )( z_4 Int ) ) Bool
	( and
		( = x1 x1_0 )
		( = x2 x2_0 )
		( = x3 x3_0 )
		( = y y_0 )
		( = z z_1 )
		( = x1_0 0 )
		( = x2_0 0 )
		( = x3_0 0 )
		( = 1 2 )
		( >= y_0 0 )
		( >= y_0 127 )
		( = z_1 ( * 36 y_0 ) )
	)
)

( define-fun trans-f ( ( c Int )( x1 Int )( x2 Int )( x3 Int )( y Int )( z Int )( tmp Int )( c! Int )( x1! Int )( x2! Int )( x3! Int )( y! Int )( z! Int )( tmp! Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( x1_0 Int )( x2_0 Int )( x3_0 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int )( z_4 Int ) ) Bool
	( or
		( and
			( = c_1 c )
			( = z_2 z )
			( = c_1 c! )
			( = z_2 z! )
			( = c c! )
			( = x1 x1! )
			( = x2 x2! )
			( = x3 x3! )
			( = y y! )
			( = z z! )
			(= tmp tmp! )
		)
		( and
			( = c_1 c )
			( = z_2 z )
			( < c_1 36 )
			( = z_3 ( + z_2 1 ) )
			( = c_2 ( + c_1 1 ) )
			( = c_3 c_2 )
			( = z_4 z_3 )
			( = c_3 c! )
			( = z_4 z! )
			(= x1 x1_0 )
			(= x1! x1_0 )
			(= x2 x2_0 )
			(= x2! x2_0 )
			(= x3 x3_0 )
			(= x3! x3_0 )
			(= y y_0 )
			(= y! y_0 )
			(= tmp tmp! )
		)
		( and
			( = c_1 c )
			( = z_2 z )
			( not ( < c_1 36 ) )
			( = c_3 c_1 )
			( = z_4 z_2 )
			( = c_3 c! )
			( = z_4 z! )
			(= x1 x1_0 )
			(= x1! x1_0 )
			(= x2 x2_0 )
			(= x2! x2_0 )
			(= x3 x3_0 )
			(= x3! x3_0 )
			(= y y_0 )
			(= y! y_0 )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( c Int )( x1 Int )( x2 Int )( x3 Int )( y Int )( z Int )( tmp Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( x1_0 Int )( x2_0 Int )( x3_0 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int )( z_4 Int ) ) Bool
	( or
		( not
			( and
				( = c c_1)
				( = x1 x1_0)
				( = x2 x2_0)
				( = x3 x3_0)
				( = y y_0)
				( = z z_2)
			)
		)
		( not
			( and
				( < c_1 36 )
				( not ( < z_2 4608 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f c x1 x2 x3 y z tmp c_0 c_1 c_2 c_3 x1_0 x2_0 x3_0 y_0 z_0 z_1 z_2 z_3 z_4  )
		( inv-f c x1 x2 x3 y z tmp )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f c x1 x2 x3 y z tmp )
			( trans-f c x1 x2 x3 y z tmp c! x1! x2! x3! y! z! tmp! c_0 c_1 c_2 c_3 x1_0 x2_0 x3_0 y_0 z_0 z_1 z_2 z_3 z_4 )
		)
		( inv-f c! x1! x2! x3! y! z! tmp! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f c x1 x2 x3 y z tmp  )
		( post-f c x1 x2 x3 y z tmp c_0 c_1 c_2 c_3 x1_0 x2_0 x3_0 y_0 z_0 z_1 z_2 z_3 z_4 )
	)
))

