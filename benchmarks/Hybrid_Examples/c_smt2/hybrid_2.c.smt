(set-logic LIA)

( declare-const i Int )
( declare-const i! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const out Int )
( declare-const out! Int )

( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const n_0 Int )
( declare-const out_0 Int )
( declare-const out_1 Int )
( declare-const out_2 Int )
( declare-const out_3 Int )

( define-fun inv-f( ( i Int )( n Int )( out Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( i Int )( n Int )( out Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( out_0 Int )( out_1 Int )( out_2 Int )( out_3 Int ) ) Bool
	( and
		( = i i_0 )
		( = n n_0 )
		( = out out_0 )
		( >= n_0 0 )
		( = out_0 0 )
		( = i_0 0 )
	)
)

( define-fun trans-f ( ( i Int )( n Int )( out Int )( i! Int )( n! Int )( out! Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( out_0 Int )( out_1 Int )( out_2 Int )( out_3 Int ) ) Bool
	( or
		( and
			( = i_1 i )
			( = out_1 out )
			( = i_1 i! )
			( = out_1 out! )
			( = n n_0 )
			( = n! n_0 )
			( = out out! )
		)
		( and
			( = i_1 i )
			( = out_1 out )
			( < i_1 n_0 )
			( = i_2 ( + i_1 1 ) )
			( = ( mod n_0 2 ) 0 )
			( = 1 0 )
			( = out_2 out_1 )
			( = i_2 i! )
			( = out_2 out! )
			(= n n_0 )
			(= n! n_0 )
		)
		( and
			( = i_1 i )
			( = out_1 out )
			( < i_1 n_0 )
			( = i_2 ( + i_1 1 ) )
			( not ( = ( mod n_0 2 ) 0 ) )
			( = out_3 ( + out_1 2 ) )
			( = out_2 out_3 )
			( = i_2 i! )
			( = out_2 out! )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( i Int )( n Int )( out Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( out_0 Int )( out_1 Int )( out_2 Int )( out_3 Int ) ) Bool
	( or
		( not
			( and
				( = i i_1)
				( = n n_0)
				( = out out_1)
			)
		)
		( not
			( and
				( not ( < i_1 n_0 ) )
				( = i_1 n_0 )
				( not ( = ( mod n_0 2 ) 0 ) )
				( not ( = out_1 ( * 2 n_0 ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f i n out i_0 i_1 i_2 n_0 out_0 out_1 out_2 out_3  )
		( inv-f i n out )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f i n out )
			( trans-f i n out i! n! out! i_0 i_1 i_2 n_0 out_0 out_1 out_2 out_3 )
		)
		( inv-f i! n! out! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f i n out  )
		( post-f i n out i_0 i_1 i_2 n_0 out_0 out_1 out_2 out_3 )
	)
))

