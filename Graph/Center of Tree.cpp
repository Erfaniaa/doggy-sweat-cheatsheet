struct node
{
    char ch;
    int col, big, sz;
    vector<int> adj;
}nd[MAXN];
int n, col;
vector<int> vec;
void DFS(int pos, int col)
{
    nd[pos].sz=1;
    nd[pos].col=col;
    int k;
    nd[pos].big=0;
    Rep(i, nd[pos].adj.size())
    {
        k=nd[pos].adj[i];
        if(nd[k].col==col || nd[k].col==-1) continue;
        DFS(k, col);
        nd[pos].sz+=nd[k].sz;
        nd[pos].big=max(nd[pos].big, nd[k].sz);
    }
    vec.push_back(pos);
}
void div(int r, char ch,int col)
{
    vec.clear();
    DFS(r, col);
    r=vec[0];
    int sz=vec.size();
    Rep(i, vec.size())
    {
        nd[vec[i]].big=max(nd[vec[i]].big, sz-nd[vec[i]].sz);
        if(nd[vec[i]].big<nd[r].big) r=vec[i];
    }
    nd[r].col=-1;
    nd[r].ch=ch;
    Rep(i, nd[r].adj.size()) if(nd[nd[r].adj[i]].col==col) div(nd[r].adj[i], ch+1, col+1);
}