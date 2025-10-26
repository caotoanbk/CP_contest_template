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

int n;
vt<ar<int,3>> v;
vt<int> end_times;
void solve(){
    cin>>n;
    v.resize(n);
    end_times.resize(n);
    FOR(i, n) {
        cin >> v[i][0] >> v[i][1];
        v[i][2] = i;
        end_times[i] = v[i][0] + v[i][1];
    }
    sort(all(v), [](ar<int,3> a, ar<int,3> b) {
        if (a[0] == b[0]) return a[1] > b[1];
        return a[0] < b[0];
    });
    sort(all(end_times)); // sort end times in descending order
    // data compression
    end_times.erase(unique(all(end_times)), end_times.end());
    auto get_idx = [&](int x) {
        return lower_bound(all(end_times), x) - end_times.begin();
    };

    //building fenweik tree
    int m = sz(end_times);
    vt<int> bit(m+1, 0);
    auto update = [&](int i, int val) {
        for (++i; i < bit.size(); i += i & -i)
            bit[i] = max(bit[i], val);
    };

    auto query = [&](int i) {
        int res = 0;
        for (++i; i > 0; i -= i & -i)
            res = max(res, bit[i]);
        return res;
    };
    set<int> se;
    vt<int> ans(n, 0);
    FOR(i, n){
        auto [a2, t2, idx2] = v[i];
        int e = a2 + t2;
        if(se.lower_bound(e) == se.end()) {
            ans[v[i][2]] = 0; // no valid end time found
            se.insert(e);
            continue;
        }
        int idx = get_idx(e);
        int rev_indx = m - idx-1; // reverse index in the compressed array
        int val = query(rev_indx);
        ans[v[i][2]] = val + 1;
        update(rev_indx, ans[v[i][2]]);
        dbg(idx,rev_indx,e,bit);
    }


    FOR(i, n){
        cout << ans[i] << " ";
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