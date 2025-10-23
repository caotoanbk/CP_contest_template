#include <bits/stdc++.h>
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "../../Share/lib/debug2.h"
#else
  #define dbg(...)
  #define dbgArr(...)
#endif

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

//======= SIGNAL HANDLER FOR DEBUGGING ======== 
void signalHandler(int signum) {
    cerr << "\nCaught signal: " << signum << endl;
    // dbg(...); // add relevant variables to debug
    if (signum == SIGSEGV) cerr << "Segmentation fault detected!\n";
    else if (signum == SIGABRT) cerr << "Aborted!\n";
    exit(signum);
}

// ========== Solve function ==========
int n,m;
vt<vt<int>> adj;
vt<bool> special;
vt<int> ans;

void dfs(int node, int parent, int cnt, int& res){
  if(cnt == 1){
    res++;
  }
  for(auto&x : adj[node]){
    if(x != parent){
      if(special[x]){
        if(cnt+1 > 1) continue;
        
        dfs(x, node, cnt+1, res);
        
      }else{
        dfs(x, node, cnt, res);
      }
    }
  }
}

void solve(){
  cin >> n >> m; 
  adj.assign(n+1, {});
  special.assign(n+1, false);
  ans.assign(n+1, 0);
  REP(i,n-1){
    int u,v; cin >> u >> v;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  REP(i,m){
    int u; cin >> u;
    special[u] = true;
  }
 
  FOR(i,1,n+1){
    int res = 0;
    dfs(i,0, special[i]?1:0, res);
    ans[i] = res;
  }
  FOR(i,1,n+1){
    cout << ans[i]<< " ";
  }
  cout << '\n';
}

// ========== Main ==========
int main() {
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    
    #ifdef ON_PC
      FILE* f1 = freopen("d:\\C++\\CP\\Share\\input.txt","r",stdin);
      FILE* f2 = freopen("d:\\C++\\CP\\Share\\output.txt","w",stdout);
      if (!f1 || !f2) {
        cerr << "Failed to open input/output file!\n";
        return 1;
     }
      clock_t start = clock();
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    dbg(T);
    FOR(i,0,T){
        cout << "case " << i<<"\n";
        solve();
        cout.flush();
      }

    #ifdef ON_PC
      clock_t end = clock();
      double ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
      cerr << "Finished in " << ms << " ms" << nl;
    #endif
    return 0;
}
