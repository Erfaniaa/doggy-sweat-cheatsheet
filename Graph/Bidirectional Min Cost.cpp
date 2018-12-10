define MAX_V 1+2*100
#define MAX_E 2*10001
typedef long long edge_type;
struct edge
{
	int start, to;
	ll cap, cost;
	edge(int _s, int _d, ll _c, ll _co)
	{
		start=_s, to=_d, cost=_co, cap=_c;
	}
	edge(){}
};
const edge_type INF = 1ll<<60;
int V,E,prevee[MAX_V],last[MAX_V];
edge_type flowVal, flowCost, pot[MAX_V], dist[MAX_V];
vector<int> adj[MAX_V];
vector<edge> yal;
void add(edge b)
{
	yal.push_back(b);
	adj[b.start].push_back(yal.size()-1);
	swap(b.start, b.to);
	b.cost*=-1, b.cap=0;
	yal.push_back(b);
	adj[b.start].push_back(yal.size()-1);
}
bool Bellman_Ford (int s)
{
	bool f;
	Rep(i, V+1) pot[i]=INF;
	pot[s]=0;
	for(int i=1;i<V;i++)
	{
		f=0;
		for(int j=0;j<yal.size();j++)
		{
			int k1=yal[j].start, k2=yal[j].to,w=yal[j].cost;
			if(pot[k2]>w+pot[k1])
			{
				pot[k2]=w+pot[k1];
				f=1;
			}
		}
		if(f==0)
			break;
	}
	for(int i=0;i<yal.size();i++)
	{
		int k1=yal[i].start,k2=yal[i].to,w=yal[i].cost;
		if(pot[k2]>w+pot[k1])
			return 0;
	}
	return 1;
}
void mcmf(int s, int t){
	flowVal = flowCost = 0;
	memset(pot,0,sizeof(pot));
	Bellman_Ford(s);
	while(true){
		for(int i = 0;i<V;++i) dist[i] = INF, prevee[i]=-1;
		priority_queue<pair<ll, ll> > q;
		q.push(MP(0, s));
		dist[s] = prevee[s] = 0;
      	
		while(!q.empty()){
			int aux = q.top().second; q.pop();

			for(int i = 0;i<adj[aux].size(); i++){
				int e=adj[aux][i];
				if(yal[e].cap<=0) continue;

				edge_type new_dist = dist[aux]+yal[e].cost+pot[aux]-pot[yal[e].to];

				if(new_dist<dist[yal[e].to]){
					dist[yal[e].to] = new_dist;
					prevee[yal[e].to] = e;
					q.push(MP(-1*new_dist, yal[e].to));
				}
			}
		}

		if (prevee[t]==-1) break;

		edge_type f = INF;

		for(int i = t;i!=s;i = yal[prevee[i]^1].to) 
			f = min(f,yal[prevee[i]].cap);

		for(int i = t;i!=s;i = yal[prevee[i]^1].to){
			yal[prevee[i]].cap -= f;
			yal[prevee[i]^1].cap += f;
		}

		flowVal += f;
		flowCost += f*(dist[t]-pot[s]+pot[t]);
		for(int i = 0;i<V;++i) if (prevee[i]!=-1) pot[i] += dist[i];
	}
}

int main(){
	int N,M,u[5000],v[5000];
	long long cst[5000],D,K;
	freopen("a.in", "r", stdin);
	while(scanf("%d %d",&N,&M)==2){
		yal.clear();
		V = 2*N+1;
		for(int i=0; i<=V; i++) adj[i].clear();
		for(int i = 0;i<M;++i){
			scanf("%d %d %lld",&u[i],&v[i],&cst[i]);
			--u[i]; --v[i];
		}
		scanf("%lld %lld",&D,&K);
		E=0;
		add(edge(0, 1, D, 0));
		for(int i = 0;i<N;++i) add(edge(1+2*i,1+2*i+1,INF,0));

		for(int i = 0;i<M;++i){
			add(edge(1+2*u[i]+1,1+2*v[i],K,cst[i]));
			add(edge(1+2*v[i]+1,1+2*u[i],K,cst[i]));
		}

		mcmf(0,2*N-1);

		if(flowVal!=D) printf("Impossible.\n");
		else printf("%lld\n",flowCost);
	}

	return 0;
}