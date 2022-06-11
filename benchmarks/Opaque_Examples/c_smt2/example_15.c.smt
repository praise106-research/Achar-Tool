(set-logic LIA)

( declare-const i Int )
( declare-const i! Int )
( declare-const lin_sum Int )
( declare-const lin_sum! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const sum Int )
( declare-const sum! Int )

( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const i_3 Int )
( declare-const lin_sum_0 Int )
( declare-const lin_sum_1 Int )
( declare-const lin_sum_2 Int )
( declare-const lin_sum_3 Int )
( declare-const n_0 Int )
( declare-const sum_0 Int )
( declare-const sum_1 Int )
( declare-const sum_2 Int )
( declare-const sum_3 Int )

( define-fun inv-f( ( i Int )( lin_sum Int )( n Int )( sum Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( i Int )( lin_sum Int )( n Int )( sum Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( lin_sum_0 Int )( lin_sum_1 Int )( lin_sum_2 Int )( lin_sum_3 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int ) ) Bool
	( and
		( = i i_1 )
		( = lin_sum lin_sum_1 )
		( = n n_0 )
		( = sum sum_1 )
		( = i_1 0 )
		( = sum_1 0 )
		( = lin_sum_1 0 )
		( >= n_0 0 )
	)
)

( define-fun trans-f ( ( i Int )( lin_sum Int )( n Int )( sum Int )( i! Int )( lin_sum! Int )( n! Int )( sum! Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( lin_sum_0 Int )( lin_sum_1 Int )( lin_sum_2 Int )( lin_sum_3 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int ) ) Bool
	( or
		( and
			( = i_2 i )
			( = lin_sum_2 lin_sum )
			( = sum_2 sum )
			( = i_2 i! )
			( = lin_sum_2 lin_sum! )
			( = sum_2 sum! )
			( = n n_0 )
			( = n! n_0 )
			( = lin_sum lin_sum! )
			( = sum sum! )
		)
		( and
			( = i_2 i )
			( = lin_sum_2 lin_sum )
			( = sum_2 sum )
			( < i_2 n_0 )
			( = i_3 ( + i_2 1 ) )
			( = lin_sum_3 ( + lin_sum_2 i_3 ) )
			( = sum_3  )
			( = i_3 i! )
			( = lin_sum_3 lin_sum! )
			( = sum_3 sum! )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( i Int )( lin_sum Int )( n Int )( sum Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( lin_sum_0 Int )( lin_sum_1 Int )( lin_sum_2 Int )( lin_sum_3 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int ) ) Bool
	( or
		( not
			( and
				( = i i_2)
				( = lin_sum lin_sum_2)
				( = n n_0)
				( = sum sum_2)
			)
		)
		( not
			( and
				( not ( < i_2 n_0 ) )
				( not ( = sum_2 ( * lin_sum_2 lin_sum_2 ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f i lin_sum n sum i_0 i_1 i_2 i_3 lin_sum_0 lin_sum_1 lin_sum_2 lin_sum_3 n_0 sum_0 sum_1 sum_2 sum_3  )
		( inv-f i lin_sum n sum )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f i lin_sum n sum )
			( trans-f i lin_sum n sum i! lin_sum! n! sum! i_0 i_1 i_2 i_3 lin_sum_0 lin_sum_1 lin_sum_2 lin_sum_3 n_0 sum_0 sum_1 sum_2 sum_3 )
		)
		( inv-f i! lin_sum! n! sum! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f i lin_sum n sum  )
		( post-f i lin_sum n sum i_0 i_1 i_2 i_3 lin_sum_0 lin_sum_1 lin_sum_2 lin_sum_3 n_0 sum_0 sum_1 sum_2 sum_3 )
	)
))

