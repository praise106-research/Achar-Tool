(set-logic LIA)

( declare-primed-var m Int )
( declare-primed-var n Int )
( declare-primed-var x Int )
( declare-primed-var tmp Int )

( declare-primed-var m_0 Int )
( declare-primed-var m_1 Int )
( declare-primed-var m_2 Int )
( declare-primed-var m_3 Int )
( declare-primed-var m_4 Int )
( declare-primed-var n_0 Int )
( declare-primed-var x_0 Int )
( declare-primed-var x_1 Int )
( declare-primed-var x_2 Int )
( declare-primed-var x_3 Int )

( synth-inv inv-f( ( m Int )( n Int )( x Int )( tmp Int )( m_0 Int )( m_1 Int )( m_2 Int )( m_3 Int )( m_4 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) )

( define-fun pre-f ( ( m Int )( n Int )( x Int )( tmp Int )( m_0 Int )( m_1 Int )( m_2 Int )( m_3 Int )( m_4 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) Bool
	( and
		( = m m_1 )
		( = x x_1 )
		( = x_1 1 )
		( = m_1 1 )
	)
)

( define-fun trans-f ( ( m Int )( n Int )( x Int )( tmp Int )( m_0 Int )( m_1 Int )( m_2 Int )( m_3 Int )( m_4 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( m! Int )( n! Int )( x! Int )( tmp! Int )( m_0! Int )( m_1! Int )( m_2! Int )( m_3! Int )( m_4! Int )( n_0! Int )( x_0! Int )( x_1! Int )( x_2! Int )( x_3! Int ) ) Bool
	( or
		( and
			( = m_2 m )
			( = x_2 x )
			( = m_2 m! )
			( = x_2 x! )
			( = n n_0 )
			( = n! n_0 )
			( = m m! )
			(= tmp tmp! )
		)
		( and
			( = m_2 m )
			( = x_2 x )
			( < x_2 n_0 )
			( = m_3 x_2 )
			( = m_4 m_3 )
			( = x_3 ( + x_2 1 ) )
			( = m_4 m! )
			( = x_3 x! )
			(= n n_0 )
			(= n! n_0 )
			(= tmp tmp! )
		)
		( and
			( = m_2 m )
			( = x_2 x )
			( < x_2 n_0 )
			( = m_4 m_2 )
			( = x_3 ( + x_2 1 ) )
			( = m_4 m! )
			( = x_3 x! )
			(= n n_0 )
			(= n! n_0 )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( m Int )( n Int )( x Int )( tmp Int )( m_0 Int )( m_1 Int )( m_2 Int )( m_3 Int )( m_4 Int )( n_0 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) Bool
	( or
		( not
			( and
				( = m m_2)
				( = n n_0 )
				( = x x_2)
			)
		)
		( not
			( and
				( not ( < x_2 n_0 ) )
				( > n_0 1 )
				( not ( >= m_2 1 ) )
			)
		)
	)
)

( inv-constraint inv-f pre-f trans-f post-f )
( check-synth )
