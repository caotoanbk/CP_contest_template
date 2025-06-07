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


int n,k;
vt<pii> v;
vt<int> vis; 

void countJumps(int cur_pos, int jump_to, int &total_jumps) {
    int rightPos = v[cur_pos].se;
    FOR(i, cur_pos+1, jump_to+1) {
        if(v[i].fi > rightPos){
            total_jumps += v[i].fi - rightPos;
            rightPos = v[i].se;
        }else{
            rightPos = max(rightPos, v[i].se);
        }
    }
}

void solve(){
    int total_jumps = 0;

    int cur_pos = 0;
    FOR(i, k){
        //Jump to the next position vis[i]
        int jump_to = vis[i];
        if(jump_to < cur_pos) swap(cur_pos, jump_to);
        countJumps(cur_pos, jump_to, total_jumps);
        cur_pos = vis[i];
    }
    cout << total_jumps << endl;
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
        cin>>n>>k;
        FOR(i,n){
            int x,y;
            cin>>x>>y;
            v.pb({x,y});
        }
        FOR(i, k){
            int x; cin>>x;
            vis.pb(x-1);
        }
        solve();
    }


    #ifdef ON_PC
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cerr << "Finished in " << time_taken*1000<< " ms " << endl;
    #endif // ON_PC   

    return 0;
}