(set-logic LIA)

( declare-primed-var i Int )
( declare-primed-var n Int )
( declare-primed-var sum Int )

( declare-primed-var i_0 Int )
( declare-primed-var i_1 Int )
( declare-primed-var i_2 Int )
( declare-primed-var n_0 Int )
( declare-primed-var sum_0 Int )
( declare-primed-var sum_1 Int )
( declare-primed-var sum_2 Int )

( synth-inv inv-f( ( i Int )( n Int )( sum Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int ) ) )

( define-fun pre-f ( ( i Int )( n Int )( sum Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int ) ) Bool
	( and
		( = i i_0 )
		( = n n_0 )
		( = sum sum_0 )
		( >= n_0 0 )
		( = i_0 0 )
		( = sum_0 0 )
	)
)

( define-fun trans-f ( ( i Int )( n Int )( sum Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( i! Int )( n! Int )( sum! Int )( i_0! Int )( i_1! Int )( i_2! Int )( n_0! Int )( sum_0! Int )( sum_1! Int )( sum_2! Int ) ) Bool
	( or
		( and
			( = i_1 i )
			( = sum_1 sum )
			( = i_1 i! )
			( = sum_1 sum! )
			( = n n_0 )
			( = n! n_0 )
			( = sum sum! )
		)
		( and
			( = i_1 i )
			( = sum_1 sum )
			( < i_1 n_0 )
			( = i_2 ( + i_1 1 ) )
			( = sum_2 ( + sum_1 ( * i_2 i_2 ) ) )
			( = i_2 i! )
			( = sum_2 sum! )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( i Int )( n Int )( sum Int )( i_0 Int )( i_1 Int )( i_2 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int ) ) Bool
	( or
		( not
			( and
				( = i i_1)
				( = n n_0)
				( = sum sum_1)
			)
		)
		( not
			( and
				( not ( < i_1 n_0 ) )
				( not ( = sum_1 ( / ( * ( * n_0 ( + n_0 1 ) ) ( + ( * 2 n_0 ) 1 ) ) 6 ) ) )
			)
		)
	)
)

( inv-constraint inv-f pre-f trans-f post-f )
( check-synth )
