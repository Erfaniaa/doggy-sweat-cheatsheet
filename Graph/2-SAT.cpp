//fill the v array
//e.g. to push (p v !q) use the following code:
//    v[VAR(p)].push_back( NOT( VAR(q) ) )
//    v[NOT( VAR(q) )].push_back( VAR(p) )
//the result will be in color array
#define VAR(X) (X << 1)
#define NOT(X) (X ^ 1)
#define CVAR(X,Y) (VAR(X) | (Y))z
#define COL(X) (X & 1)
#define NVAR 400

int n;
vector<int> v[2 * NVAR];
int color[2 * NVAR];
int bc[2 * NVAR];


bool dfs( int a, int col ) {
	color[a] = col;
	int num = CVAR( a, col );
	for( int i = 0; i < v[num].size(); i++ ) {
		int adj = v[num][i] >> 1;
		int ncol = NOT( COL( v[num][i] ) );
		if( ( color[adj] == -1 && !dfs( adj, ncol ) ) ||
		   ( color[adj] != -1 && color[adj] != ncol ) ) {
			color[a] = -1;
			return false;
		}
	}
	return true;
}
bool twosat() {
	memset( color, -1, sizeof color );
	for( int i = 0; i < n; i++ ){
		if( color[i] == -1 ){
			memcpy(bc, color, sizeof color);
			if( !dfs( i, 0 )){
				memcpy(color, bc, sizeof color);
				if(!dfs( i, 1 ))
					return false;
			}
		}
	}
	return true;
}
// Vertices are numbered 0..n­1 for true states.
// False state of the variable i is i+n (i.e. other(i))
// For SCC 'n', 'adj' and 'adjrev' need to be filled.
// For 2­Sat set 'n' and use add_edge
// 0<=val[i]<=1 is the value for binary variable i in 2­Sat
// 0<=group[i]<2*n is the scc number of vertex i.

int n;
vector<int> adj[maxn*2];
vector<int> adjrev[maxn*2];
int val[maxn];
int marker,dfst,dfstime[maxn*2],dfsorder[maxn*2];
int group[maxn*2];
// For 2SAT Only
inline int other(int v){return v<n?v+n:v­n;}
inline int var(int v){return v<n?v:v­n;}
inline int type(int v){return v<n?1:0;}
void satclear() {
	for(int i=0;i<maxn+maxn;i++) {
		adj[i].resize(0);
		adjrev[i].resize(0);
	}
}
void dfs(int v){
	if(dfstime[v] != -1)
		return;
	dfstime[v] = -2;
	int deg = adjrev[v].size();
	for(int i=0;i<deg;i++)
		dfs(adjrev[v][i]);
	dfstime[v] = dfst++;
}
void dfsn(int v) {
	if(group[v] != -1)
		return;
	group[v]=marker;
	int deg=adj[v].size();
	for(int i=0;i<deg;i++)
		dfsn(adj[v][i]);
}
// For 2SAT Only
void add_edge(int a,int b) {
	adj[other(a)].push_back(b);
	adjrev[a].push_back(other(b));
	adj[other(b)].push_back(a);
	adjrev[b].push_back(other(a));
}
int solve() {
	dfst=0;
	memset(dfstime,-1,sizeof dfstime);
	for(int i=0;i<n+n;i++)
		dfs(i);
	memset(val,-1,sizeof val);
	for(int i=0;i<n+n;i++)
		dfsorder[n+n-dfstime[i]-1]=i;
	memset(group,-1,sizeof group);
	for(int i=0;i<n+n;i++) {
		marker=i;
		dfsn(dfsorder[i]);
	}
	// For 2SAT Only
	for(int i=0;i<n;i++) {
		if(group[i] == group[i+n])
			return 0;
		val[i] = (group[i]>group[i+n]) ? 0 : 1;
	}
	return 1;
}