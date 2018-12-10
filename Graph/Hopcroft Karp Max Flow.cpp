/// e*sqrt(v)
vector<int> adj[MAXN];
int dis1[MAXN], dis2[MAXN], g1[MAXN], g2[MAXN], n, inf=1<<30, n1, n2;
queue<int> q;
bool BFS()
{
	for(int i=0; i<n1; i++) dis1[i]=0;
	for(int i=0; i<n2; i++) dis2[i]=0;
	for(int i=0; i<n1; i++) if(g1[i]==-1) q.push(i);
	bool f=0;
	int v, u;
	while (!q.empty())
	{
		v=q.front(), q.pop();
		for(int i=0; i<adj[v].size(); i++)
		{
			u=adj[v][i];
			if(dis2[u]==0)
			{
				dis2[u]=dis1[v]+1;
				if(g2[u]==-1) f=1;
				else
				{
					dis1[g2[u]]=dis2[u]+1;
		 			q.push(g2[u]);
				}
			}
		}
	}
	return f;
}
bool DFS(int v)
{
	int u;
	for(int i=0; i<adj[v].size(); i++)
	{
		u=adj[v][i];
		if(dis2[u]==dis1[v]+1)
		{
			dis2[u]=0;
			if(g2[u]==-1 ||  DFS(g2[u]))
			{
				g1[v]=u;
				g2[u]=v;
				return 1;
			}
		}
	}
	return 0;
}
int Hopcroft_Karp()
{
	for(int i=0; i<n1; i++) g1[i]=-1;
	for(int i=0; i<n2; i++) g2[i]=-1;
	int matching=0;
	while (BFS()) for(int i=0; i<n1; i++) 
		if(g1[i]==-1 && DFS(i)) matching++;
	return matching;
}
int col[MAXN];
int ind[MAXN];

void paint_geraph()
{
	memset(col, -1, sizeof col);
	int c, k;
	ind[0]=0;
	col[n1++]=1;
	q.push(0);
	while (!q.empty())
	{
		c=q.front(), q.pop();
		for(int i=0; i<adj[c].size(); i++)
		{
			k=adj[c][i];
			if(col[k]!=-1) continue;
			col[k]=!col[c];
			if(col[k]) ind[k]=n1++;
			else ind[k]=n2++;
			q.push(k);
		}
	}
}
int main(){
	int m, u, v;
	vector<pii> ed;
	cin>>n>>m;
	for(int i=0; i<m; i++)
	{
		cin>>u>>v;
		ed.push_back(make_pair(u-1, v-1));
		adj[u-1].push_back(v-1);
		adj[v-1].push_back(u-1);
	}
	n1=n2=0;
	paint_geraph();
	for(int i=0; i<n; i++) adj[i].clear();
	for(int i=0; i<m; i++)
	{
		u=ind[ed[i].first], v=ind[ed[i].second];
		if(col[ed[i].first]) adj[u].push_back(v);
		else adj[v].push_back(u);
	}
	int ans=Hopcroft_Karp();
	cout<<ans<<endl;
	bool f;
	for(int i=0; i<m; i++)
	{
		u=ind[ed[i].first], v=ind[ed[i].second];
		f=0;
		if(col[ed[i].first])
		{
			if(g1[u]==v) 
				f=1;
		}
		else if(g2[u]==v) f=1;
		if(f) cout<<ed[i].first+1<<' '<<ed[i].second+1<<endl;
	}
	return 0;
}
