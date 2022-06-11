(set-logic LIA)

( declare-const b Int )
( declare-const b! Int )
( declare-const orig_x Int )
( declare-const orig_x! Int )
( declare-const s Int )
( declare-const s! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const b_0 Int )
( declare-const b_1 Int )
( declare-const b_2 Int )
( declare-const orig_x_0 Int )
( declare-const orig_x_1 Int )
( declare-const s_0 Int )
( declare-const s_1 Int )
( declare-const s_2 Int )
( declare-const s_3 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_3 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )
( declare-const y_2 Int )
( declare-const y_3 Int )
( declare-const y_4 Int )
( declare-const y_5 Int )

( define-fun inv-f( ( b Int )( orig_x Int )( s Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( b Int )( orig_x Int )( s Int )( x Int )( y Int )( b_0 Int )( b_1 Int )( b_2 Int )( orig_x_0 Int )( orig_x_1 Int )( s_0 Int )( s_1 Int )( s_2 Int )( s_3 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int )( y_4 Int )( y_5 Int ) ) Bool
	( and
		( = orig_x orig_x_1 )
		( = s s_1 )
		( = x x_0 )
		( = y y_1 )
		( >= x_0 0 )
		( = y_1 0 )
		( = s_1 30 )
		( = orig_x_1 x_0 )
	)
)

( define-fun trans-f ( ( b Int )( orig_x Int )( s Int )( x Int )( y Int )( b! Int )( orig_x! Int )( s! Int )( x! Int )( y! Int )( b_0 Int )( b_1 Int )( b_2 Int )( orig_x_0 Int )( orig_x_1 Int )( s_0 Int )( s_1 Int )( s_2 Int )( s_3 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int )( y_4 Int )( y_5 Int ) ) Bool
	( or
		( and
			( = b_1 b )
			( = s_2 s )
			( = x_1 x )
			( = y_2 y )
			( = b_1 b! )
			( = s_2 s! )
			( = x_1 x! )
			( = y_2 y! )
			( = b b! )
			( = orig_x orig_x! )
			( = x x! )
			( = y y! )
		)
		( and
			( = b_1 b )
			( = s_2 s )
			( = x_1 x )
			( = y_2 y )
			( >= s_2 0 )
			( = y_3 ( * 2 y_2 ) )
			( = b_2 ( << ( + ( * ( * 3 y_3 ) ( + y_3 1 ) ) 1 ) s_2 ) )
			( = s_3 ( - s_2 3 ) )
			( >= x_1 b_2 )
			( = x_2 ( - x_1 b_2 ) )
			( = y_4 ( + y_3 1 ) )
			( = x_3 x_2 )
			( = y_5 y_4 )
			( = b_2 b! )
			( = s_3 s! )
			( = x_3 x! )
			( = y_5 y! )
			(= orig_x orig_x_1 )
			(= orig_x! orig_x_1 )
		)
		( and
			( = b_1 b )
			( = s_2 s )
			( = x_1 x )
			( = y_2 y )
			( >= s_2 0 )
			( = y_3 ( * 2 y_2 ) )
			( = b_2 ( << ( + ( * ( * 3 y_3 ) ( + y_3 1 ) ) 1 ) s_2 ) )
			( = s_3 ( - s_2 3 ) )
			( not ( >= x_1 b_2 ) )
			( = x_3 x_1 )
			( = y_5 y_3 )
			( = b_2 b! )
			( = s_3 s! )
			( = x_3 x! )
			( = y_5 y! )
			(= orig_x orig_x_1 )
			(= orig_x! orig_x_1 )
		)
	)
)

( define-fun post-f ( ( b Int )( orig_x Int )( s Int )( x Int )( y Int )( b_0 Int )( b_1 Int )( b_2 Int )( orig_x_0 Int )( orig_x_1 Int )( s_0 Int )( s_1 Int )( s_2 Int )( s_3 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int )( y_4 Int )( y_5 Int ) ) Bool
	( or
		( not
			( and
				( = b b_1)
				( = orig_x orig_x_1)
				( = s s_2)
				( = x x_1)
				( = y y_2)
			)
		)
		( not
			( and
				( not ( >= s_2 0 ) )
				( not ( >= orig_x_1 ( * ( * y_2 y_2 ) y_2 ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f b orig_x s x y b_0 b_1 b_2 orig_x_0 orig_x_1 s_0 s_1 s_2 s_3 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 y_4 y_5  )
		( inv-f b orig_x s x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f b orig_x s x y )
			( trans-f b orig_x s x y b! orig_x! s! x! y! b_0 b_1 b_2 orig_x_0 orig_x_1 s_0 s_1 s_2 s_3 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 y_4 y_5 )
		)
		( inv-f b! orig_x! s! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f b orig_x s x y  )
		( post-f b orig_x s x y b_0 b_1 b_2 orig_x_0 orig_x_1 s_0 s_1 s_2 s_3 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 y_4 y_5 )
	)
))

