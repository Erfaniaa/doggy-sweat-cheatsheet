#define LSOne(S) (S & (-S))
vector<int> fen;
void ft_create(int n) { fen.assign(n + 1, 0); }
// initially n + 1 zeroes
int ft_rsq(int b) 
{ // returns RSQ(1, b)
	int sum = 0; 
	for (; b; b -= LSOne(b)) sum += fen[b];
	return sum; 
}
int ft_rsq(int a, int b) 
{ // returns RSQ(a, b)
	return ft_rsq(b) - (a == 1 ? 0 : ft_rsq(a - 1)); 
}
// adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec).
void ft_adjust(int k, int v) 
{
	for (; k <  (int)fen.size(); k += LSOne(k)) fen[k] += v;
}