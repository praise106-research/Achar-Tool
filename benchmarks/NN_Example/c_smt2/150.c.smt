(set-logic LIA)

( declare-const arr Int )
( declare-const arr! Int )
( declare-const i Int )
( declare-const i! Int )
( declare-const index Int )
( declare-const index! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const sum Int )
( declare-const sum! Int )

( declare-const arr_0 Int )
( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const index_0 Int )
( declare-const index_1 Int )
( declare-const index_2 Int )
( declare-const index_3 Int )
( declare-const n_0 Int )
( declare-const n_1 Int )
( declare-const sum_0 Int )
( declare-const sum_1 Int )
( declare-const sum_2 Int )
( declare-const sum_3 Int )

( define-fun inv-f( ( arr Int )( i Int )( index Int )( n Int )( sum Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( arr Int )( i Int )( index Int )( n Int )( sum Int )( arr_0 Int )( i_0 Int )( i_1 Int )( index_0 Int )( index_1 Int )( index_2 Int )( index_3 Int )( n_0 Int )( n_1 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int ) ) Bool
	( and
		( = arr arr_0 )
		( = i i_1 )
		( = index index_1 )
		( = n n_1 )
		( = sum sum_1 )
		( = arr_0  )
		( = sum_1 0 )
		( = i_1 0 )
		( = n_1 100 )
		( = index_1 0 )
	)
)

( define-fun trans-f ( ( arr Int )( i Int )( index Int )( n Int )( sum Int )( arr! Int )( i! Int )( index! Int )( n! Int )( sum! Int )( arr_0 Int )( i_0 Int )( i_1 Int )( index_0 Int )( index_1 Int )( index_2 Int )( index_3 Int )( n_0 Int )( n_1 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int ) ) Bool
	( or
		( and
			( = index_2 index )
			( = sum_2 sum )
			( = index_2 index! )
			( = sum_2 sum! )
			( = n n_1 )
			( = n! n_1 )
			( = arr arr! )
			( = i i! )
			( = sum sum! )
		)
		( and
			( = index_2 index )
			( = sum_2 sum )
			( < index_2 n_1 )
			( = index_3 ( + index_2 1 ) )
			( = sum_3 ( + sum_2  ) )
			( = index_3 index! )
			( = sum_3 sum! )
			(= arr arr_0 )
			(= arr! arr_0 )
			(= i i_1 )
			(= i! i_1 )
			(= n n_1 )
			(= n! n_1 )
		)
	)
)

( define-fun post-f ( ( arr Int )( i Int )( index Int )( n Int )( sum Int )( arr_0 Int )( i_0 Int )( i_1 Int )( index_0 Int )( index_1 Int )( index_2 Int )( index_3 Int )( n_0 Int )( n_1 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int ) ) Bool
	( or
		( not
			( and
				( = arr arr_0)
				( = i i_1)
				( = index index_2)
				( = n n_1)
				( = sum sum_2)
			)
		)
		( not
			( and
				( not ( < index_2 n_1 ) )
				( not ( = sum_2 450 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f arr i index n sum arr_0 i_0 i_1 index_0 index_1 index_2 index_3 n_0 n_1 sum_0 sum_1 sum_2 sum_3  )
		( inv-f arr i index n sum )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f arr i index n sum )
			( trans-f arr i index n sum arr! i! index! n! sum! arr_0 i_0 i_1 index_0 index_1 index_2 index_3 n_0 n_1 sum_0 sum_1 sum_2 sum_3 )
		)
		( inv-f arr! i! index! n! sum! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f arr i index n sum  )
		( post-f arr i index n sum arr_0 i_0 i_1 index_0 index_1 index_2 index_3 n_0 n_1 sum_0 sum_1 sum_2 sum_3 )
	)
))

