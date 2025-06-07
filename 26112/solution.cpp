#include <bits/stdc++.h>
using namespace std;
#ifdef ON_PC
    #include "../shared/lib/debug2.h"
#else
    #define dbg(...) 
    #define dbgArr(...)
#endif

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

#define int int64_t
int n,p,q;
const map<char,int> suit_to_value = {
    {'C', 0}, // Clubs
    {'D', 1}, // Diamonds
    {'H', 2}, // Hearts
    {'S', 3}  // Spades
};

const map<string,int> kind_to_value = {
    {"2", 0}, {"3", 1}, {"4", 2}, {"5", 3}, {"6", 4},
    {"7", 5}, {"8", 6}, {"9", 7}, {"10", 8}, {"J", 9},
    {"Q", 10}, {"K", 11}, {"A", 12}
};

vt<int> X;
vt<int> P1,P2;

// int dp[501][501][501];// dp[i][j][k] = max LCS with i caards from P1, j cards from P2 and k cards from X
vt<vt<vt<int>>> dp;

void solve(){
    cin>>n>>p>>q;
    dp.resize(n+1, vt<vt<int>>(p+1, vt<int>(q+1, 0)));
    dp[0][0][0] = 0;
    FOR(i,n){
        string card; cin>> card;
        char suit = card[0];
        string kind = card.substr(1);
        X.pb(kind_to_value.at(kind) + 13 * suit_to_value.at(suit));
    }
    FOR(i,p){
        string card; cin>>card;
        char suit = card[0];
        string kind = card.substr(1);
        P1.pb(kind_to_value.at(kind) + 13 * suit_to_value.at(suit));
    }
    FOR(i,q){
        string card; cin>>card;
        char suit = card[0];
        string kind = card.substr(1);
        P2.pb(kind_to_value.at(kind) + 13 * suit_to_value.at(suit));
    }

   FOR(i, n+1){
    FOR(j, p+1){
        FOR(k, q+1){
            if(i < n && j < p && X[i] == P1[j]) {
                dp[i+1][j+1][k] = max(dp[i+1][j+1][k], dp[i][j][k] + 1);
            }
            if(i< n && j < p) {
                dp[i+1][j+1][k] = max(dp[i+1][j+1][k], dp[i][j][k]);
            }
            if(i <n) {
                dp[i+1][j][k] = max(dp[i+1][j][k], dp[i][j][k]);
            }
            if(j < p){
                dp[i][j+1][k] = max(dp[i][j+1][k], dp[i][j][k]);
            }

            if(i< n && k < q && X[i] == P2[k]) {
                dp[i+1][j][k+1] = max(dp[i+1][j][k+1], dp[i][j][k] + 1);
            }
            if(i<n && k<q){
                dp[i+1][j][k+1] = max(dp[i+1][j][k+1], dp[i][j][k]);
            }
            if(i < n) {
                dp[i+1][j][k] = max(dp[i+1][j][k], dp[i][j][k]);
            }
            if(k < q) {
                dp[i][j][k+1] = max(dp[i][j][k+1], dp[i][j][k]);
            }
        }
    }
}



    dbg(dp[3][1][1]);
    cout << dp[n][p][q] << endl;

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