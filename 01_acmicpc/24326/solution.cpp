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

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);  // enough space for segment tree
        build(a, 1, 0, n - 1);
    }

    void build(const vector<int>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = a[l];
        } else {
            int mid = (l + r) / 2;
            build(a, 2 * node, l, mid);
            build(a, 2 * node + 1, mid + 1, r);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return INT_MIN;     // no overlap
        if (ql <= l && r <= qr) return tree[node]; // total overlap
        int mid = (l + r) / 2;
        return max(
            query(2 * node, l, mid, ql, qr),
            query(2 * node + 1, mid + 1, r, ql, qr)
        );
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
        } else {
            int mid = (l + r) / 2;
            if (idx <= mid)
                update(2 * node, l, mid, idx, val);
            else
                update(2 * node + 1, mid + 1, r, idx, val);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    // public interfaces
    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }
};


struct SegmentTreeIter {
    int n;
    vector<int> tree;
    SegmentTreeIter(const vector<int>& a) {
        n = (int)a.size();
        tree.resize(2*n);
        for (int i=0; i<n; i++) tree[n+i] = a[i];
        for (int i=n-1; i>0; i--) tree[i] = max(tree[i<<1], tree[i<<1|1]);
    }
    void update(int pos, int val) {
        pos += n;
        tree[pos] = val;
        for (pos /= 2; pos > 0; pos /= 2)
            tree[pos] = max(tree[pos<<1], tree[pos<<1|1]);
    }
    int query() {
        return tree[1];
    }
};


int n,m;
vt<int> a;
vt<int> val,v1;
vt<vt<int>> cfg;
void solve(){
    cfg.assign(n,vt<int>());
    FOR(i,n){
        FOR(j,i,n,i+1){
            val[i] += a[j];
            v1[i] += a[j];
            cfg[j].pb(i);
        }
    }
    int max_org = *max_element(all(val));
    FOR(i,n){
        sort(cfg[i].begin(), cfg[i].end(), [](int x, int y) {
            return val[x] > val[y];
        });
    }
    int mx_cnt = 0;
    FOR(i,n){
        if(val[i] == max_org) {
            mx_cnt++;
        }
    }

    
    sort(v1.begin(), v1.end(), greater<int>());
    // dbg(v1);

    int ans =0;
    vt<int> cnt(n,0);
    // FOR(i,n){
    //     EACH(ind, cfg[i]){
    //         if(val[ind] == max_org) {
    //             cnt[i]++;
    //         }
    //     }
    // }

    unordered_set<int> max_val_indices;
    FOR(i, n) {
        if (val[i] == max_org) max_val_indices.insert(i);
    }

    FOR(i, n) {
        for (int ind : cfg[i]) {
            if (max_val_indices.count(ind)) {
                cnt[i]++;
            }
        }
    }
    FOR(i,m){
        int p,s; cin>>p>>s;
        p--;


        if(s >=0){
            if(cnt[p] == mx_cnt){
                ans += s + val[cfg[p][0]];
            }else{
                ans += max(max_org, val[cfg[p][0]] + s);
            }
        }else{
            if(cnt[p] == mx_cnt){
                int tmp_ind=0;
                // dbg(cfg[p]);
                FOR(j, sz(cfg[p])){
                    // dbg(val[cfg[p][j]]);
                    // if(v1[j] == max_org) continue;
                    if(val[cfg[p][j]] != v1[j]){
                        tmp_ind = j;
                        break;
                    }else{
                        tmp_ind++;
                    }
                }
                // dbg(tmp_ind);
                ans += max(max_org+s, v1[tmp_ind]);
            }else{
                ans += max_org;
            }
        }

    }
    cout<<ans<<endl;
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

    int t; 
    // cin >> t;
    t =1;
    while(t--){
        cin>>n;
        a.resize(n);
        val.assign(n,0);
        v1.assign(n,0);
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