int n, arr[MAXN], table[MAXN][20], table2[MAXN][20];
int Log[MAXN];
vector<int> tmp, best;
int GCD(int a, int b)
{
	if(b==0) return a;
	return GCD(b, a%b);
}
void init(int n)
{
	int mx=0, l=0, r=n+1, lim=2, lg=0;
	Rep(i, MAXN)
	{
		if(i==lim)
		{
			lg++;
			lim*=2;
		}
		Log[i]=lg;
	}
	Rep(i, n) table[i][0]=table2[i][0]=arr[i];
	For(i, 1, Log[n]+1) for(int j=0; j+(1<<i)-1< n; j++) 
	{
		table[j][i]=GCD(table[j][i-1], table[j+(1<<(i-1))][i-1]);
		table2[j][i]=min(table2[j][i-1], table2[j+(1<<(i-1))][i-1]);
	}
}
int get_gcd(int l, int r)
{
	int lg=Log[r-l+1];
	return GCD(table[l][lg], table[r-(1<<lg)+1][lg]);
}