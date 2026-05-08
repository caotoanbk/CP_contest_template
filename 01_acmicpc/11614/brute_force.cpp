#include <bits/stdc++.h>
using namespace std;
#ifdef ON_PC
    #include "../shared/lib/debug2.h"
#else
    #define dbg(...) 
    #define dbgArr(...)
#endif

#define int int64_t
typedef pair<int,int> pii;
#define ll long long
#define ld long double
#define ar array
#define vt vector
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define endl '\n'

#define F_OR(i, a, b, s) for (int i=(a); (s)>0?i<(b):i>(b); i+=(s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)
#define EACH(x, a) for (auto& x: a)

int a,b;
string s;
struct Word{
    int start;
    int end;
};
vt<Word> words;
void extractWords(const string& s, vt<Word>& result){
    int start = 0;
    while (start < s.size()) {
        if (s[start] == ' ') {
            result[start].start = -1;
            result[start].end = -1;
            start++;
            continue;
        }

        // Find the end of the current word
        int end = start;
        while (end < s.size() && s[end] != ' ') {
            end++;
        }

        // Extract the word from start to end-1
        string word = s.substr(start, end - start);

        // Fill the vector for all characters in this word
        for (int i = start; i < end; ++i) {
            result[i].start = start;
            result[i].end = end - 1; // end is inclusive
        }

        // Move to the next part of the string
        start = end;
    }
}
void solve(){
    // cin >> s;
    // int n;
    // cin >> n;
    // cin.ignore(); // discard the '\n' left in the buffer
    getline(cin, s); // now safe

    int n = sz(s);
    dbg(s,n);
    words.resize(n);
    extractWords(s, words);
    // dbg(words);

    cin >>a>>b;
    FOR(i, a, b+1){
        int ans = 0;
        int ind = 0;
        while(ind < n){
            if (words[ind].start == -1) {
                ++ind;
                continue;
            }
            ans += words[ind].end - words[ind].start + 1; // length of the word
            ans++;
            if(ind + i -1 == n-1 || (ind+i-1 <n-1 && words[ind+i-1].start != -1 && words[ind+i].start ==-1) ){
                ind += i+1; // move to the next word
            } else {
                if(ind+i-1 < n && words[ind+i-1].start != -1){
                    ind = words[ind+i-1].start;
                }else{
                    ind += i; 
                }
            }
        }
        ans--; // remove the last space
        cout << ans <<endl;
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    #ifdef ON_PC
        freopen("../shared/input.txt", "r", stdin);
        freopen("../shared/output.txt", "w", stdout);
        //freopen("../shared/error.txt", "w", stderr);
        clock_t start, end;
        start = clock();
    #endif // ON_PC

    int t=1; 
    // cin >> t;
    while(t--){
        solve();
    }


    #ifdef ON_PC
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cerr << "Finished in " << time_taken*1000<< " ms " << endl;
    #endif // ON_PC   

    return 0;
}