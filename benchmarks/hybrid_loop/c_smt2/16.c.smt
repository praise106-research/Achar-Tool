(set-logic LIA)

( declare-const m Int )
( declare-const m! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const tmp Int )
( declare-const tmp! Int )

( declare-const m_0 Int )
( declare-const m_1 Int )
( declare-const n_0 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_3 Int )

( define-fun inv-f( ( m Int )( n Int )( x Int )( tmp Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( m Int )( n Int )( x Int )( tmp Int )( m_0 Int )( m_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) Bool
	( and
		( = m m_1 )
		( = x x_1 )
		( = x_1 0 )
		( = m_1 0 )
	)
)

( define-fun trans-f ( ( m Int )( n Int )( x Int )( tmp Int )( m! Int )( n! Int )( x! Int )( tmp! Int )( m_0 Int )( m_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) Bool
	( or
		( and
			( = x_2 x )
			( = x_2 x! )
			( = n n_0 )
			( = n! n_0 )
			( = m m! )
			(= tmp tmp! )
		)
		( and
			( = x_2 x )
			( < x_2 n_0 )
			( = 1 0 )
			( = x_3 ( + x_2 1 ) )
			( = x_3 x! )
			(= m m_1 )
			(= m! m_1 )
			(= n n_0 )
			(= n! n_0 )
			(= tmp tmp! )
		)
		( and
			( = x_2 x )
			( < x_2 n_0 )
			( = x_3 ( + x_2 1 ) )
			( = x_3 x! )
			(= m m_1 )
			(= m! m_1 )
			(= n n_0 )
			(= n! n_0 )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( m Int )( n Int )( x Int )( tmp Int )( m_0 Int )( m_1 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) Bool
	( or
		( not
			( and
				( = m m_1)
				( = n n_0 )
				( = x x_2)
			)
		)
		( not
			( and
				( not ( < x_2 n_0 ) )
				( > n_0 0 )
				( not ( >= m_1 0 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f m n x tmp m_0 m_1 n_0 x_0 x_1 x_2 x_3  )
		( inv-f m n x tmp )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f m n x tmp )
			( trans-f m n x tmp m! n! x! tmp! m_0 m_1 n_0 x_0 x_1 x_2 x_3 )
		)
		( inv-f m! n! x! tmp! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f m n x tmp  )
		( post-f m n x tmp m_0 m_1 n_0 x_0 x_1 x_2 x_3 )
	)
))

