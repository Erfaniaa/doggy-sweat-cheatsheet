//From "You Know Izad?" team cheat sheet
struct rib {  
    int b, u, c, f;  
    size_t back;  
};  
void add_rib (vector < vector<rib> > & g, int a, int b, int u, int c) {  
    // u = capacity  
    // c = cost per flow (maybe double)  
    // add edge between a and b  
    rib r1 = { b, u, c, 0, g[b].size() };  
    rib r2 = { a, 0, -c, 0, g[a].size() };  
    g[a].push_back (r1);  
    g[b].push_back (r2);  
}  
int main() {  
    // k = the exact amount of flow (cost is calculated according to this)  
    // set k to infinity --> gives maxFlow (in flow variable)  
    int n, m, k;  
    vector < vector<rib> > g (n);  
    int s, t;  
    //reading the graph  
    int flow = 0,  cost = 0;  
    while (flow < k) {  
        vector<int> id (n, 0);  
        vector<int> d (n, INF);  
        vector<int> q (n);  
        vector<int> p (n);  
        vector<size_t> p_rib (n);  
        int qh=0, qt=0;  
        q[qt++] = s;  
        d[s] = 0;  
        while (qh != qt) {  
            int v = q[qh++];  
            id[v] = 2;  
            if (qh == n)  qh = 0;  
            for (size_t i=0; i<g[v].size(); ++i) {  
                rib & r = g[v][i];  
                if (r.f < r.u && d[v] + r.c < d[r.b]) {  
                    d[r.b] = d[v] + r.c;  
                    if (id[r.b] == 0) {  
                        q[qt++] = r.b;  
                        if (qt == n)  qt = 0;  
                    }  
                    else if (id[r.b] == 2) {  
                        if (--qh == -1)  qh = n-1;  
                        q[qh] = r.b;  
                    }  
                    id[r.b] = 1;  
                    p[r.b] = v;  
                    p_rib[r.b] = i;  
                }  
            }  
        }  
        if (d[t] == INF)  break;  
        int addflow = k - flow;  
        for (int v=t; v!=s; v=p[v]) {  
            int pv = p[v];  size_t pr = p_rib[v];  
            addflow = min (addflow, g[pv][pr].u - g[pv][pr].f);  
        }  
        for (int v=t; v!=s; v=p[v]) {  
            int pv = p[v];  size_t pr = p_rib[v],  r = g[pv][pr].back;  
            g[pv][pr].f += addflow;  
            g[v][r].f -= addflow;  
            cost += g[pv][pr].c * addflow;  
        }  
        flow += addflow;  
    }  
    // output the result  
}