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

int t,a,s,b;
vt<int> v;
void solve(){
    cin>>t>>a>>s>>b;
    v.resize(a,0);
    vt<int> counts(t, 0);
    EACH(x, v) {
        cin >> x;
        counts[x-1]++;
    }
    int dp[t+1][b+1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    FOR(i, t){
        int k = counts[i];
        vt<int> pref(b+1, 0);
        FOR(j, b+1){
            if(j > 0) pref[j] = (pref[j-1] + dp[i][j]) % 1000000; // To avoid overflow
            else pref[j] = dp[i][j];
        }
        FOR(j, b+1){
           int l = max((int)0, j-k);
           int r = j;
           dp[i+1][j] = pref[r];
           if(l > 0) {
               dp[i+1][j] = (dp[i+1][j] - pref[l-1] + 1000000) % 1000000; // To avoid overflow
           }
        }
    }

    int total = 0;
    FOR(i, s, b+1){
        total = (total + dp[t][i]); // To avoid overflow
    }
    cout << (total%1000000) << endl;
    
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