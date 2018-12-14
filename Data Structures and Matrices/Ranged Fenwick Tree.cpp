//not tested
#define LSOne(S) (S & (-S))
vector<ll> fen[2];
void ft_create(int n) { fen[0].assign(n + 1, 0), fen[1].assign(n + 1, 0); }
ll ft_rsq(int b, bool bl) 
{
	ll sum = 0; 
	for (; b; b -= LSOne(b)) sum += fen[bl][b];
	return sum; 
}
void ft_adjust(ll k, ll v, bool bl) 
{
	for (; k <= (int)fen[bl].size(); k += LSOne(k)) fen[bl][k] += v;
}
void range_adjust(ll l, ll r, ll v)
{
	ft_adjust(l, v, 0), ft_adjust(r+1, -v, 0);
	ft_adjust(l, v*(l-1), 1), ft_adjust(r+1, -v*r, 1);
}
ll range_rsq(ll l, ll r)
{
	ll x=0, a, b;
	if(l)
	{
		a=ft_rsq(l-1, 0), b=ft_rsq(l-1, 1);
		x=(l-1)*a-b;
	}
	a=ft_rsq(r, 0), b=ft_rsq(r, 1);
	ll y=r*a-b;
	return y-x;
}