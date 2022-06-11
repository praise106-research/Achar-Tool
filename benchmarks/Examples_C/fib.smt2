(set-logic LIA)

( declare-const add_sum_arg1_x Int )
( declare-const add_sum_arg1_x! Int )
( declare-const add_sum_arg2_y Int )
( declare-const add_sum_arg2_y! Int )
( declare-const c Int )
( declare-const c! Int )
( declare-const fib_arg1_n Int )
( declare-const fib_arg1_n! Int )
( declare-const i Int )
( declare-const i! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const add_sum_arg1_x_0 Int )
( declare-const add_sum_arg2_y_0 Int )
( declare-const c_0 Int )
( declare-const c_1 Int )
( declare-const c_2 Int )
( declare-const c_3 Int )
( declare-const fib_arg1_n_0 Int )
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

( define-fun inv-f( ( add_sum_arg1_x Int )( add_sum_arg2_y Int )( c Int )( fib_arg1_n Int )( i Int )( n Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( add_sum_arg1_x Int )( add_sum_arg2_y Int )( c Int )( fib_arg1_n Int )( i Int )( n Int )( x Int )( y Int )( add_sum_arg1_x_0 Int )( add_sum_arg2_y_0 Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( fib_arg1_n_0 Int )( i_0 Int )( i_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
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

( define-fun trans-f ( ( add_sum_arg1_x Int )( add_sum_arg2_y Int )( c Int )( fib_arg1_n Int )( i Int )( n Int )( x Int )( y Int )( add_sum_arg1_x! Int )( add_sum_arg2_y! Int )( c! Int )( fib_arg1_n! Int )( i! Int )( n! Int )( x! Int )( y! Int )( add_sum_arg1_x_0 Int )( add_sum_arg2_y_0 Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( fib_arg1_n_0 Int )( i_0 Int )( i_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
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
			( = add_sum_arg1_x add_sum_arg1_x! )
			( = add_sum_arg2_y add_sum_arg2_y! )
			( = c c! )
			( = fib_arg1_n fib_arg1_n! )
			( = x x! )
			( = y y! )
		)
		( and
			( = c_2 c )
			( = x_2 x )
			( = y_2 y )
			( < i_1 n_0 )
			( = c_3 ( + add_sum_arg1_x_0 add_sum_arg2_y_0 ) )
			( = x_3 y_2 )
			( = y_3 c_3 )
			( = c_3 c! )
			( = x_3 x! )
			( = y_3 y! )
			(= add_sum_arg1_x add_sum_arg1_x_0 )
			(= add_sum_arg1_x! add_sum_arg1_x_0 )
			(= add_sum_arg2_y add_sum_arg2_y_0 )
			(= add_sum_arg2_y! add_sum_arg2_y_0 )
			(= fib_arg1_n fib_arg1_n_0 )
			(= fib_arg1_n! fib_arg1_n_0 )
			(= i i_1 )
			(= i! i_1 )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( add_sum_arg1_x Int )( add_sum_arg2_y Int )( c Int )( fib_arg1_n Int )( i Int )( n Int )( x Int )( y Int )( add_sum_arg1_x_0 Int )( add_sum_arg2_y_0 Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( fib_arg1_n_0 Int )( i_0 Int )( i_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = add_sum_arg1_x add_sum_arg1_x_0 )
					( = add_sum_arg2_y add_sum_arg2_y_0 )
					( = c c_2)
					( = fib_arg1_n fib_arg1_n_0 )
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
					( not ( and ( <= ( <= 0 i_1 ) n_0 ) ( = x_2 fib_arg1_n_0 ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = add_sum_arg1_x add_sum_arg1_x_0 )
					( = add_sum_arg2_y add_sum_arg2_y_0 )
					( = c c_2)
					( = fib_arg1_n fib_arg1_n_0 )
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
					( not ( and ( <= ( <= 0 i_1 ) n_0 ) ( = x_2 fib_arg1_n_0 ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f add_sum_arg1_x add_sum_arg2_y c fib_arg1_n i n x y add_sum_arg1_x_0 add_sum_arg2_y_0 c_0 c_1 c_2 c_3 fib_arg1_n_0 i_0 i_1 n_0 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3  )
		( inv-f add_sum_arg1_x add_sum_arg2_y c fib_arg1_n i n x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f add_sum_arg1_x add_sum_arg2_y c fib_arg1_n i n x y )
			( trans-f add_sum_arg1_x add_sum_arg2_y c fib_arg1_n i n x y add_sum_arg1_x! add_sum_arg2_y! c! fib_arg1_n! i! n! x! y! add_sum_arg1_x_0 add_sum_arg2_y_0 c_0 c_1 c_2 c_3 fib_arg1_n_0 i_0 i_1 n_0 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 )
		)
		( inv-f add_sum_arg1_x! add_sum_arg2_y! c! fib_arg1_n! i! n! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f add_sum_arg1_x add_sum_arg2_y c fib_arg1_n i n x y  )
		( post-f add_sum_arg1_x add_sum_arg2_y c fib_arg1_n i n x y add_sum_arg1_x_0 add_sum_arg2_y_0 c_0 c_1 c_2 c_3 fib_arg1_n_0 i_0 i_1 n_0 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 )
	)
))

