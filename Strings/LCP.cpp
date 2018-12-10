//O(n^2)
void LCP(string a, string b)
{
	Set(lcp, 0);
    for(int i=a.size()-1; i>=0; i--) 
    for(int j=b.size()-1; j>=0; j--) {
		if(a[i]==b[j]) lcp[i][j]=1+lcp[i+1][j+1];
		else lcp[i][j]=0;
    }
}