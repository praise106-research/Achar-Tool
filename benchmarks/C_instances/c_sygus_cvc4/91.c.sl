(set-logic LIA)


( synth-inv inv-f( ( x Int )( y Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) )

( define-fun pre-f ( ( x Int )( y Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( and
		( = x x_1 )
		( = y y_1 )
		( = x_1 0 )
		( = y_1 0 )
	)
)

( define-fun trans-f ( ( x Int )( y Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int )( x! Int )( y! Int )( x_0! Int )( x_1! Int )( y_0! Int )( y_1! Int )( y_2! Int )( y_3! Int ) ) Bool
	( or
		( and
			( = y_2 y )
			( = y_2 y! )
			( = x x! )
		)
		( and
			( = y_2 y )
			( >= y_2 0 )
			( = y_3 ( + y_2 x_1 ) )
			( = y_3 y! )
			(= x x_1 )
			(= x! x_1 )
		)
	)
)

( define-fun post-f ( ( x Int )( y Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( or
		( not
			( and
				( = x x_1)
				( = y y_2)
			)
		)
		( not
			( and
				( not ( >= y_2 0 ) )
				( not ( >= y_2 0 ) )
			)
		)
	)
)

( inv-constraint inv-f pre-f trans-f post-f )
( check-synth )
