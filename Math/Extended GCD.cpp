template< class Int >
struct Triple
{
	Int d, x, y;
	Triple( Int q, Int w, Int e ) : d( q ), x( w ), y( e ) {}
};

/****************
 * Extended GCD *
 ****************
 * Given nonnegative a and b, computes d = gcd( a, b )
 * along with integers x and y, such that d = ax + by
 * and returns the triple (d, x, y).
 * WARNING: needs a small modification to work on
 * negative integers (operator% fails).
 * REQUIRES: struct Triple
 * USED BY: msolve, inverse, ldioph
 **/

template< class Int >
Triple< Int > egcd( Int a, Int b )
{
	if( !b ) return Triple< Int >( a, Int( 1 ), Int( 0 ) );
	Triple< Int > q = egcd( b, a % b );
	return Triple< Int >( q.d, q.y, q.x - a / b * q.y );
}
