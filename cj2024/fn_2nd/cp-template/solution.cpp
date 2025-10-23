#include <bits/stdc++.h>
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "../../../Share/lib/debug2.h"
#else
  #define dbg(...)
  #define dbgArr(...)
#endif

// ========== Fast IO initializer ==========
struct FastIO {
    FastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    }
} fastio; // khởi tạo trước main

// ========== Aliases & Macros ==========
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
template<typename T> using vt = vector<T>;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define nl '\n'

// Loop macros
#define FOR(i,a,b) for(ll i=(a); i<(b); ++i)
#define REP(i,n) FOR(i,0,n)
#define PER(i,n) for(ll i=(n)-1; i>=0; --i)

// ========== Helpers (optional) ==========
template<class T> inline bool chmin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<class T> inline bool chmax(T& a,const T& b){if(b>a){a=b;return true;}return false;}

ll n,m;
const int MAX_N = (int)2*1e5+1;
ll D[MAX_N+1], S[MAX_N+1];
vt<vt<ll>> group_by_val;
vt<vt<ll>> group_by_sum;

struct MergeSortTree{
  vt<vt<ll>> tree;
  int n;
  MergeSortTree(){n=0;}
  MergeSortTree(const vt<ll>& arr){
    n = sz(arr);
    if(n == 0) return;
    tree.resize(4*n+5);
    build(arr);
  }
  void build(const vt<ll>& arr){
    n = sz(arr);
    if(n == 0) return;
    tree.resize(4*n+5);
    build_rec(1,0,n-1,arr);
  }
  void build_rec(int node, int l, int r, const vt<ll>& arr){
    if(l == r){
      tree[node].pb(arr[l]);
      return;
    }
    int mid = (l+r)/2;
    build_rec(2*node, l, mid, arr);
    build_rec(2*node+1, mid+1, r, arr);
    merge(all(tree[2*node]), all(tree[2*node+1]), back_inserter(tree[node]));
  }

  int query_count(int ql, int qr, ll low, ll high){
    if (n == 0 || ql > qr) return 0;
    return query_rec(1,0,n-1,ql,qr,low,high);
  }

  int query_rec(int node, int l, int r, int ql, int qr, ll low, ll high){
    if(r < ql || l > qr) return 0;
    if(ql <= l && r <= qr){
      int left_idx = lower_bound(all(tree[node]), low) - tree[node].begin();
      int right_idx = upper_bound(all(tree[node]), high) - tree[node].begin();
      return right_idx - left_idx;
    }
    int mid = (l+r)/2;
    return query_rec(2*node, l, mid, ql, qr, low, high) +
           query_rec(2*node+1, mid+1, r, ql, qr, low, high);
  }
  
};
vt<MergeSortTree> mgs_tree;

void precompute(){
  memset(D, 0, sizeof(D));
  memset(S, 0, sizeof(S));
  FOR(i, 1, MAX_N+1){
    for(int j = i; j <= MAX_N; j += i){
      D[j]++;
      S[j] += i;
    }
  }

  ll maxD= 0;
  FOR(i,1,MAX_N+1){
    chmax(maxD, D[i]);
  }
  group_by_val.resize(maxD+1);
  group_by_sum.resize(maxD+1);
  mgs_tree.resize(maxD+1);
  FOR(i,1,MAX_N+1){
    group_by_val[D[i]].pb(i);
    group_by_sum[D[i]].pb(S[i]);
  }
  FOR(d, 1, maxD+1){
    if(sz(group_by_val[d]) > 0){
      mgs_tree[d] = MergeSortTree(group_by_sum[d]);
    }
  }
  
}
ll x, a, b, c;

// ========== Solve function ==========
void solve(){
  
  // precompute();
  // dbg(MAX_N);
  cin>>n>>m;
  dbg(n,m);
  FOR(i,0,m){
    // try{
    // dbg("query ", i);
      // cout<<"hello there"<<nl;
      x, a,b,c;
      cin>>x>>a>>b>>c;
      // dbg(x,a,b,c);
      ll L = max(1ll, x-a);
      ll R = min(n, x+a);
      ll ans(0);
      FOR(d,max(1ll,D[x]-b), min(D[x]+b+1, (ll)group_by_val.size()+1)){
        if(sz(group_by_val[d]) == 0) continue;
        // assert(d>0);
        dbg(d);
        ll left_idx = lower_bound(all(group_by_val[d]), L) - group_by_val[d].begin();
        ll right_idx = upper_bound(all(group_by_val[d]), R) - group_by_val[d].begin() - 1;
        if(left_idx> right_idx) continue;
        ll cnt = 0;
        cnt = mgs_tree[d].query_count(left_idx, right_idx, S[x]-c, S[x]+c);
        ans += cnt;
      }
      cout<<ans<<" ";
    // }catch(...){
    //   dbg(i);
    // }
  }
  cout<<nl;
}
void signalHandler(int signum) {
    cerr << "\nCaught signal: " << signum << endl;
    dbg(n,m);
    dbg(x,a,b,c);
    if (signum == SIGSEGV) cerr << "Segmentation fault detected!\n";
    else if (signum == SIGABRT) cerr << "Aborted!\n";
    exit(signum);
}

// ========== Main ==========
int main() {
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    #ifdef ON_PC
      freopen("../../../Share/input.txt","r",stdin);
      freopen("../../../Share/output.txt","w",stdout);
      clock_t start = clock();
    #endif

    int T = 1;
    precompute();
    // dbg(group_by_val[0]); 
    cin >> T;
    while(T--){
      try{
        solve();
      }catch(...){
        dbg("Exception caught in test case", T);
      }
    }

    #ifdef ON_PC
      clock_t end = clock();
      double ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
      cerr << "Finished in " << ms << " ms" << nl;
    #endif
    return 0;
}
