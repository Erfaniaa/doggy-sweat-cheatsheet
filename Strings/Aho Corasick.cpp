const int MAXN = 404, MOD = 1e9 + 7, sigma = 26;

int term[MAXN], len[MAXN], to[MAXN][sigma], link[MAXN], sz = 1;
void add_str(string s)
{
    int cur = 0;
    for(auto c: s)
    {
        if(!to[cur][c - 'a'])
        {
            to[cur][c - 'a'] = sz++;
            len[to[cur][c - 'a']] = len[cur] + 1;
        }
        cur = to[cur][c - 'a'];
    }
    term[cur] = cur; 
}

void push_links()
{
    int que[sz];
    int st = 0, fi = 1;
    que[0] = 0;
    while(st < fi)
    {
        int V = que[st++];
        int U = link[V];
        if(!term[V]) term[V] = term[U];
        for(int c = 0; c < sigma; c++)
            if(to[V][c])
            {
                link[to[V][c]] = V ? to[U][c] : 0;
                que[fi++] = to[V][c];
            }
            else
            {
                to[V][c] = to[U][c];
            }
    }
}