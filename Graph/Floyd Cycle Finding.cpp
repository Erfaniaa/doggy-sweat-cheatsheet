ll a, b, c;
vector<ll> vec;
ll f(ll x)
{
	return (a*x+(x%b))%c;
}
pii floydCycleFinding(ll x0) 
{ 
	// mu : start of cycle , lambda : lenght of cycle, cnt for seting limits
	// 1st part: finding k*mu, hareís speed is 2x tortoiseís
	ll tortoise = f(x0), hare = f(f(x0)); // f(x0) is the element/node next to x0
	int cnt=0;
	while (tortoise != hare && cnt<=20000000)
	{ tortoise = f(tortoise); hare = f(f(hare)); cnt++;}
	if(cnt>20000000) return MP(-1, -1);
	// 2nd part: finding mu, hare and tortoise move at the same speed
	ll mu = 0; hare = x0;
	while (tortoise != hare) { tortoise = f(tortoise); hare = f(hare); mu++; }
	
	// 3rd part: finding lambda, hare moves, tortoise stays
	ll lambda = 1;  hare = f(tortoise);
	while (tortoise != hare)
	{ hare = f(hare); lambda++; }
	return pii(mu, lambda);
}
int main(){
	cin>>a>>b>>c;
	pii ans=floydCycleFinding(1);
	if(ans.first!=-1) cout<<ans.first+ans.second<<endl;
	else cout<<-1<<endl;
	return 0;
}