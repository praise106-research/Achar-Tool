(set-logic LIA)

( declare-const power Int )
( declare-const power! Int )
( declare-const result Int )
( declare-const result! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const x_0 Int )
( declare-const x_0! Int )
( declare-const y Int )
( declare-const y! Int )
( declare-const y_power Int )
( declare-const y_power! Int )

( declare-const power_0 Int )
( declare-const power_1 Int )
( declare-const result_0 Int )
( declare-const result_1 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_0_0 Int )
( declare-const x_0_1 Int )
( declare-const y_0 Int )
( declare-const y_power_0 Int )
( declare-const y_power_1 Int )

( define-fun inv-f( ( power Int )( result Int )( x Int )( x_0 Int )( y Int )( y_power Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( power Int )( result Int )( x Int )( x_0 Int )( y Int )( y_power Int )( power_0 Int )( power_1 Int )( result_0 Int )( result_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_0_0 Int )( x_0_1 Int )( y_0 Int )( y_power_0 Int )( y_power_1 Int ) ) Bool
	( and
		( = power power_1 )
		( = result result_1 )
		( = x x_0 )
		( = x_0 x_0_1 )
		( = y y_0 )
		( = y_power y_power_1 )
		( >= x_0 0 )
		( not ( = y_0 0 ) )
		( >= y_power_0 0 )
		( = x_0_1 x_0 )
		( = result_1 0 )
		( = power_1 32 )
		( = y_power_1 ( << y_0 power_1 ) )
	)
)

( define-fun trans-f ( ( power Int )( result Int )( x Int )( x_0 Int )( y Int )( y_power Int )( power! Int )( result! Int )( x! Int )( x_0! Int )( y! Int )( y_power! Int )( power_0 Int )( power_1 Int )( result_0 Int )( result_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_0_0 Int )( x_0_1 Int )( y_0 Int )( y_power_0 Int )( y_power_1 Int ) ) Bool
	( or
		( and
			( = x_1 x )
			( = x_1 x! )
			( = y y_0 )
			( = y! y_0 )
			( = power power! )
			( = result result! )
			( = x_0 x_0! )
			( = y_power y_power! )
		)
		( and
			( = x_1 x )
			( >= x_1 y_0 )
			( = x_2 ( - x_1 y_power_1 ) )
			( = x_2 x! )
			(= power power_1 )
			(= power! power_1 )
			(= result result_1 )
			(= result! result_1 )
			(= x_0 x_0_1 )
			(= x_0! x_0_1 )
			(= y y_0 )
			(= y! y_0 )
			(= y_power y_power_1 )
			(= y_power! y_power_1 )
		)
	)
)

( define-fun post-f ( ( power Int )( result Int )( x Int )( x_0 Int )( y Int )( y_power Int )( power_0 Int )( power_1 Int )( result_0 Int )( result_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_0_0 Int )( x_0_1 Int )( y_0 Int )( y_power_0 Int )( y_power_1 Int ) ) Bool
	( or
		( not
			( and
				( = power power_1)
				( = result result_1)
				( = x x_1)
				( = x_0 x_0_1)
				( = y y_0)
				( = y_power y_power_1)
			)
		)
		( not
			( and
				( not ( >= x_1 y_0 ) )
				( not ( = x_0_1 ( + x_1 ( * y_0 result_1 ) ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f power result x x_0 y y_power power_0 power_1 result_0 result_1 x_0 x_1 x_2 x_0_0 x_0_1 y_0 y_power_0 y_power_1  )
		( inv-f power result x x_0 y y_power )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f power result x x_0 y y_power )
			( trans-f power result x x_0 y y_power power! result! x! x_0! y! y_power! power_0 power_1 result_0 result_1 x_0 x_1 x_2 x_0_0 x_0_1 y_0 y_power_0 y_power_1 )
		)
		( inv-f power! result! x! x_0! y! y_power! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f power result x x_0 y y_power  )
		( post-f power result x x_0 y y_power power_0 power_1 result_0 result_1 x_0 x_1 x_2 x_0_0 x_0_1 y_0 y_power_0 y_power_1 )
	)
))

