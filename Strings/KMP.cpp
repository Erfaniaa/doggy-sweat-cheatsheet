//From "You Know Izad?" team cheat sheet
int fail[100005];  
void build(const string &key){  
    fail[0] = 0;  
    fail[1] = 0;  
    fore(i, 2, L(key)) {  
        int j = fail[i - 1];  
        while (true) {  
            if (key[j] == key[i - 1]) {  
                fail[i] = j + 1;  
                break;  
            }  
            else if (j == 0) break;  
            j = fail[j];  
        }  
    }  
}  
int KMP(const string &text, const string &key) {  
    build(key);  
    int i = 0, j = 0;  
    while (true) {  
        if (j == L(text)) return -1;  
        if (text[j] == key[i]) {  
            i++;  
            j++;  
            if (i == L(key)) return j - i;  
        }  
        else if (i > 0) i = fail[i];  
        else j++;  
    }  
}