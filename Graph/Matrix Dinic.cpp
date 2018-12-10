//From "You Know Izad?" team cheat sheet
#define MAXN 400  
struct Edge  
{  
    int a, b;  
    ll cap, flow;  
};  
int n, c[MAXN][MAXN], f[MAXN][MAXN], s, t, d[MAXN], ptr[MAXN];  
bool bfs()  
{  
    queue <int> q;  
    q.push(s);  
    memset (d, -1, sizeof d);  
    d[s] = 0;  
    while(!q.empty()){  
        int v = q.front();  
        q.pop();  
        for (int to=0; to<n; ++to){  
            if (d[to] == -1 && f[v][to] < c[v][to]){  
                q.push(to);  
                d[to] = d[v] + 1;  
            }  
        }  
    }  
    return d[t] != -1;  
}  
int dfs (int v, int flow)  
{  
    if (!flow)  return 0;  
    if (v == t)  return flow;  
    for (int & to=ptr[v]; to<n; ++to){  
        if (d[to] != d[v] + 1)  continue;  
        int pushed = dfs (to, min (flow, c[v][to] - f[v][to]));  
        if (pushed){  
            f[v][to] += pushed;  
            f[to][v] -= pushed;  
            return pushed;  
        }  
    }  
    return 0;  
}  
int dinic() {  
    int flow = 0;  
    // flow between any two vertices is initially zero  
    memset(f, 0, sizeof f);  
    while(true){  
        if (!bfs())  break;  
        memset(ptr, 0, sizeof ptr);  
        // overflow?  
        while (int pushed = dfs (s, INF32))  
            flow += pushed;  
    }  
    return flow;  
}  
int main()  
{  
    // set s (source) , t (sink) , n (nodes)  
    memset(c, 0, sizeof c);  
    // add edges in capacity (c) matrix  
    // call dinic function to get Maxflow  
}  