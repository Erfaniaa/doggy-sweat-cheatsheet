int cap[MAXN][MAXN],n;
vector<int>  adj[MAXN]; 
int BFS(int s, int e)
{
	bool v[MAXN]={0};
	int p[MAXN], i, t, k, c;
	for(i=1;i<=n;i++)
		p[i] = -1;
	queue <int> q;
	q.push(s);
	v[s]=1;
	while(!q.empty())
	{
		t=q.front();
		q.pop();
		for(i=0;i<adj[t].size();i++)
		{
			k=adj[t][i];
			if(v[k]==0 && cap[t][k]>0)
			{
				q.push(k);
				v[k]=1;
				p[k]=t;
				if(k==e)
					break;
			}
		}
		if(i<adj[t].size())
			break;
	}
	k=e,c=1<<28;
	while(p[k]>-1)
	{
		c=min(c,cap[p[k]][k]);
		k=p[k];
	}
	k=e;
	while(p[k]>-1)
	{
		cap[p[k]][k]-=c;
		cap[k][p[k]]+=c;
		k=p[k];
	}
	if(c==1<<28)
		return 0;
	return c;
}
int max_flow(int s, int e)
{
	int ans=0, c;
	while(1)
	{
		c=BFS(s, e);
		if(c==0)
			break;
		ans+=c;
	}
	return ans;
}
void add_edge(int u, int v, int c)
{
	adj[u].push_back(v), adj[v].push_back(u);
	if(c!=MOD) cap[u][v]+=c;
	else cap[u][v]=MOD;
}