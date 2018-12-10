int n, low_link[MAXN], index[MAXN], ind, group, gr[MAXN];
stack<int> st;
vector<int> adj[MAXN];
bool instack[MAXN];
void tarjan(int c)
{
	index[c]=low_link[c]=ind++;
	instack[c]=1;
	st.push(c);
	int k;
	Rep(i, (int)adj[c].size())
	{
		k=adj[c][i];
		if(index[k]==-1) 
		{
			tarjan(k);
			low_link[c]=min(low_link[c], low_link[k]);
		}
		else if(instack[k]) low_link[c]=min(low_link[c], index[k]);
	}
	if(low_link[c]==index[c])
	{
		group++;
		do
		{
			k=st.top(), st.pop();
			gr[k]=group;
			instack[k]=0;
		}while (k!=c);
	}
}
int main(){
	Set(index, -1), Set(instack, 0);
	ind=group=0;
	Rep(i, n) if(index[i]==-1) tarjan(i);
	cout<<group<<endl;
	return 0;
}