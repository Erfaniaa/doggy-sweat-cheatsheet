//Bipartite Matching is O(M * N)
#define M 128
#define N 128
bool graph[M][N];
bool seen[N];
int matchL[M], matchR[N];
int n, m;
bool bpm( int u )
{
    for( int v = 0; v < n; v++ ) if( graph[u][v] )
    {
        if( seen[v] ) continue;
        seen[v] = true;
		
        if( matchR[v] < 0 || bpm( matchR[v] ) )
        {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}
vector<int> vertex_cover()
{
	// Comment : Vertices on the left side (n side) are labeled like this : m+i where i is the index
	set<int> s, t, um; // um = UnMarked
	vector<int> vc;
	for(int i = 0; i < m; i++)
		if(matchL[i]==-1)
			s.insert(i), um.insert(i);
	while( um.size() )
	{
		int v = *(um.begin());
		for(int i = 0; i < n; i++)
			if( graph[v][i] && matchL[v]!=i)
			{
				t.insert(i);
				if( s.find(matchR[i]) == s.end())
					s.insert(matchR[i]), um.insert(matchR[i]);
			}
		um.erase(v);
	}
	for(int i = 0; i < m; i++)
		if( s.find(i) == s.end() )
			vc.push_back(i);
	for(set<int>::iterator i = t.begin(); i != t.end(); i++)
		vc.push_back((*i) + m);
	return vc;
}
int main()
{
    // Read input and populate graph[][]
    // Set m, n
    memset( matchL, -1, sizeof( matchL ) );
    memset( matchR, -1, sizeof( matchR ) );
    int cnt = 0;
    for( int i = 0; i < m; i++ )
    {
        memset( seen, 0, sizeof( seen ) );
        if( bpm( i ) ) cnt++;
    }
    vector<int> vc = vertex_cover();
    // cnt contains the number of happy pigeons
    // matchL[i] contains the hole of pigeon i or -1 if pigeon i is unhappy
    // matchR[j] contains the pigeon in hole j or -1 if hole j is empty
    // vc contains the Vertex Cover
    return 0;
}
// SHAMIR:::::
const int maxn = 555;
vector <int> adjL[maxn], adjR[maxn];
int toLeft[maxn], toRight[maxn]; // adj to Left &&& adj to Right
int n, m;
int color[maxn];
int selected[maxn][2];// for finding the minCover
int colors[maxn][2];// for finding the minCover

// u is on the left
// v is on the right
void addEdge(int u, int v) {
	adjR[u].pB(v);
	adjL[v].pB(u);
}

void clear() {
	for (int i = 0; i < max(n, m); i++) {
		adjR[i].clear();
		adjL[i].clear();
	}
}

// u is always on the right
bool DFS(int u) {
	color[u] = 1;
	for (int i = 0; i < sz(adjL[u]); i++) {
		int v = adjL[u][i];
		if (toRight[v] == -1 || (color[toRight[v]] == 0 && DFS(toRight[v]))) {
			toRight[v] = u;
			toLeft[u] = v;
			return true;
		}
	}
	return false;
}
int getMaxMatch() {
	for (int i = 0; i < max(n, m); i++) {
		toLeft[i] = toRight[i] = -1;
	}
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < m; i++) {
			color[i] = 0; // color of the right's nodes is enough
		}
		if (toLeft[j] == -1) {
			DFS(j);
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (toRight[i] != -1) {
			ans ++;
		}
	}
	return ans;
}
// for finding minCover
void goAndPaintNodes(int u, int side, int targetSide) {
	colors[u][side] = 1;
	if (side == targetSide) {
		selected[u][side] = 1;
	}
	if (side == 0) { // u is on the left
		if (side == targetSide) {
			goAndPaintNodes(toRight[u], 1 - side, targetSide);
		}
		else {
			for (int i = 0; i < sz(adjR[u]); i++) {
				int v = adjR[u][i];
				if (colors[v][1 - side] == 0) {
					goAndPaintNodes(v, 1 - side, targetSide);
				}
			}
		}
	}
	else {
		// u is on the right
		if (side == targetSide) {
			goAndPaintNodes(toLeft[u], 1 - side, targetSide);
		}
		else {
			for (int i = 0; i < sz(adjL[u]); i++) {
				int v = adjL[u][i];
				if (colors[v][1 - side] == 0) {
					goAndPaintNodes(v, 1 - side, targetSide);
				}
			}
		}
	}
}
void minCover() {
	int maxi = getMaxMatch(); // we have matching here!!
	// cout << "max matching is " << maxi << endl;
	
	memset(selected, 0, sizeof selected);
	memset(colors, 0, sizeof colors);
	for (int i = 0; i < n; i++) { // looking for a naked node!!
		if (toRight[i] == -1 && colors[i][0] == 0) {
			goAndPaintNodes(i, 0, 1);
		}
	}
	for (int i = 0; i < m; i++) {
		if (toLeft[i] == -1 && colors[i][1] == 0) {
			goAndPaintNodes(i, 1, 0);
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (toRight[i] != -1 && selected[i][0] == 0 && selected[toRight[i]][1] == 0) {
			selected[i][0] = 1;
		}
	}
}