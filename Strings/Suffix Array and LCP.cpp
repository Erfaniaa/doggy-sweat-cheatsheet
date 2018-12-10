//From "You Know Izad?" team cheat sheet
const int MAXLG = 15;  
const int MAXN = 3000;  
int P[MAXLG][MAXN], stp;  
string s;  
struct entry {  
    int nr[2], p;  
} L[MAXN];  
int cmp(entry a, entry b) {  
    return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1] ? 1 : 0) : (a.nr[0] < b.nr[0] ? 1 : 0);  
}  
void init() {  
    memset(P, 0, sizeof P);  
    stp = 1;  
    fore(i, 0, MAXN) {  
        L[i].nr[0] = 0;  
        L[i].nr[1] = 0;  
        L[i].p = 0;  
    }  
}  
int rangeComp(int idx, const string &t, int len){  
    fore(i, 0, len) {  
        if(i >= L(t) && i + idx >= L(s)) return 0;  
        else if(i + idx >= L(s)) return 1;  
        else if(i >= L(t)) return -1;  
        if(s[i + idx] == t[i]) continue;  
        if(s[i + idx] > t[i]) return 1;  
        return -1;  
    }  
    return 0;  
}  
void construct() {  
    init();  
    for (int i = 0; i < L(s); i++)  
        P[0][i] = s[i] - 'a';  
    for (int cnt = 1; (cnt >> 1) < L(s); stp++, cnt <<= 1){  
        for (int i = 0; i < L(s); i++){  
            L[i].nr[0] = P[stp - 1][i];  
            L[i].nr[1] = i + cnt < L(s) ? P[stp-1][i+cnt] : -1;  
            L[i].p = i;  
        }  
        sort(L, L + L(s), cmp);  
        for (int i = 0; i < L(s); i ++)  
            P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;  
    }  
}  
ii stringMatching(const string &t){  
    int low = 0, high = L(s) - 1, mid = low;  
    while (low < high){  
        mid = (low + high) / 2;  
        int res = rangeComp(L[mid].p , t, L(t));  
        if (res >= 0) high = mid;  
        else low = mid + 1;  
    }  
    if (rangeComp(L[low].p , t, L(t)) != 0) return ii(-1, -1);  
    ii ans;  
    ans.first = low;  
    low = 0; high = L(s) - 1; mid = low;  
    while (low < high) {  
        mid = (low + high) / 2;  
        int res = rangeComp(L[mid].p, t, L(t));  
        if (res > 0) high = mid;  
        else low = mid + 1;  
    }  
    if (rangeComp(L[high].p, t, L(t)) != 0) high--;  
    ans.second = high;  
    return ans;  
}  
int lcp(int x, int y)  {  
    int ret = 0;  
    if (x == y) return L(s) - x;  
    for (int k = stp - 1; k >= 0 && x < L(s) && y < L(s); k--)  {  
        if (P[k][x] == P[k][y])  
            x += (1 << k), y += (1 << k), ret += (1 << k);  
    }  
    return ret;  
}  
int main()  {  
    cin >> s;  
    construct();  
    string t;  
// rangeComp and stringMatching are optional  
    while(cin >> t)  {  
        ii ans = stringMatching(t);  
        cout << ans.first << " " << ans.second << endl;  
    }  
}  
