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

#include <iostream>
#include <vector>
using namespace std;

int n,m;
vt<int> a;
vt<int> val;
vt<vt<int>> cfg;
void solve(){
    cfg.assign(n,vt<int>());
    FOR(i,n){
        FOR(j,i,n,i+1){
            val[i] += a[j];
            cfg[j].pb(i);
        }
    }
    int ans=0;
    FOR(i,m){
        int p,s; cin>>p>>s;
        p--;
        EACH(ind, cfg[p]){
           val[ind] += s; 
        }
        int tmp= *max_element(val.begin(), val.end());
        EACH(ind, cfg[p]){
           val[ind] -= s; 
        }
        dbg(tmp);
    }
    cout<<ans<<endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    #ifdef ON_PC
        freopen("../shared/input.txt", "r", stdin);
        freopen("../shared/ans.txt", "w", stdout);
        //freopen("../shared/error.txt", "w", stderr);
        clock_t start, end;
        start = clock();
    #endif // ON_PC

    int t; 
    // cin >> t;
    t =1;
    while(t--){
        cin>>n;
        a.resize(n);
        val.assign(n,0);
        EACH(x, a) cin >> x;
        cin>>m;
        solve();
    }


    #ifdef ON_PC
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cerr << "Finished in " << time_taken*1000<< " ms " << endl;
    #endif // ON_PC   

    return 0;
}