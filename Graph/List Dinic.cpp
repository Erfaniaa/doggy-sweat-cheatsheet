//From "You Know Izad?" team cheat sheet
const int MAXN = 300;  
struct Edge  
{  
    int a, b, cap, flow;  
};  
int n, s, t, d[MAXN], ptr[MAXN];  
vector<Edge> e;  
vi adj[MAXN];  
void init(){  
    e.clear();  
    fore(i, 0, MAXN)  
        adj[i].clear();  
}  
void add_edge (int a, int b, int cap) {  
    Edge e1 = { a, b, cap, 0 };  
    Edge e2 = { b, a, 0, 0 };  
    adj[a].push_back ((int) e.size());  
    e.push_back (e1);  
    adj[b].push_back ((int) e.size());  
    e.push_back (e2);  
}  
bool bfs() {  
    queue <int> q;  
    q.push(s);  
    memset(d, -1, sizeof d);  
    d[s] = 0;  
    while (!q.empty() && d[t] == -1){  
        int v = q.front();  
        q.pop();  
        for (int i = 0; i < L(adj[v]); ++i)  
        {  
            int id = adj[v][i],  
                to = e[id].b;  
            if (d[to] == -1 && e[id].flow < e[id].cap)  
            {  
                q.push(to);  
                d[to] = d[v] + 1;  
            }  
        }  
    }  
    return d[t] != -1;  
}  
int dfs (int v, int flow){  
    if (!flow) return 0;  
    if (v == t) return flow;  
    for (; ptr[v] < L(adj[v]); ++ptr[v]){  
        int id = adj[v][ptr[v]],  
            to = e[id].b;  
        if (d[to] != d[v] + 1)  
            continue;  
        int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));  
        if (pushed) {  
            e[id].flow += pushed;  
            e[id ^ 1].flow -= pushed;  
            return pushed;  
        }  
    }  
    return 0;  
}  
int dinic(){  
    int flow = 0;  
    while(true){  
        if (!bfs())  
            break;  
        memset(ptr, 0, sizeof ptr);  
        // overflow?  
        while (int pushed = dfs (s, INF32))  
            flow += pushed;  
    }  
    return flow;  
}  
int main()  
{  
    init();  
    // set n, s, t  
    // add edges using add_edge (directed edge)  
    int result = dinic();  
}  