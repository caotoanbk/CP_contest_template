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

// ========== Solve function ==========
int n1,m1,n2,m2;
vt<vt<int>> adj1,adj2;
vt<bool> special1,special2;
vt<int> ans1,ans2;
const ll mod = (ll)(1e9)+7;
//======= SIGNAL HANDLER FOR DEBUGGING ======== 
void signalHandler(int signum) {
    cerr << "\nCaught signal: " << signum << endl;
    // dbg(...); // add relevant variables to debug
    dbg(n1,m1,n2,m2);
    if (signum == SIGSEGV) cerr << "Segmentation fault detected!\n";
    else if (signum == SIGABRT) cerr << "Aborted!\n";
    exit(signum);
}


void dfs(int node, int parent, int cnt, int& res, vt<vt<int>>& adj, vt<bool>& special){
  if(cnt == 1){
    res++;
  }
  for(auto&x : adj[node]){
    if(x != parent){
      if(special[x]){
        if(cnt+1 > 1) continue;
        
        dfs(x, node, cnt+1, res, adj, special);
        
      }else{
        dfs(x, node, cnt, res, adj, special);
      }
    }
  }
}

void solve(){
  cin >> n1>>m1; 
  adj1.assign(n1+1, {});
  special1.assign(n1+1, false);
  ans1.assign(n1+1, 0);
  REP(i, m1){
    int u; cin >> u;
    special1[u] = true;
  }
  REP(i,n1-1){
    int u,v; cin >> u >> v;
    // if (i < 10) cerr << u << " " << v << nl;
    adj1[u].pb(v);
    adj1[v].pb(u);
  }
  cin >> n2>>m2; 
  adj2.assign(n2+1, {});
  special2.assign(n2+1, false);
  ans2.assign(n2+1, 0);
  REP(i, m2){
    int u; cin >> u;
    special2[u] = true;
  }
  REP(i,n2-1){
    int u,v;
    // if (i < 10) cerr << u << " " << v << nl;
     if (!(cin >> u >> v)) {
        cerr << "Input ended early at i = " << i << "\n";
        break;
    }
    adj2[u].pb(v);
    adj2[v].pb(u);
  }
 
  FOR(i,1,n1+1){
    int res = 0;
    dfs(i,0, special1[i]?1:0, res, adj1, special1);
    ans1[i] = res;
  }
  FOR(i,1,n2+1){
    int res = 0;
    dfs(i,0, special2[i]?1:0, res, adj2, special2);
    ans2[i] = res;
  }

  long long sumA1 = 0, sumA2 = 0;
  long long sumA1i = 0, sumA2j = 0;

  for (int i = 1; i <= n1; ++i) {
      sumA1 += ans1[i];
      sumA1 %= mod;
      sumA1i += ans1[i] * i;
      sumA1i %= mod;
  }

  for (int j = 1; j <= n2; ++j) {
      sumA2 += ans2[j];
      sumA2 %=mod;
      sumA2j += ans2[j] * j;
      sumA2j %= mod;
  }

  long long S = sumA2 * sumA1i % mod + sumA1 * sumA2j %mod;
  S %= mod;
  cout << S <<endl;
  cout.flush();
}

// ========== Main ==========
int main() {
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    
    #ifdef ON_PC
      FILE* f1 = freopen("d:\\C++\\CP\\Share\\input.txt","r",stdin);
      FILE* f2 = freopen("d:\\C++\\CP\\Share\\output.txt","w",stdout);
      if (!f1 ) {
        cerr << "Failed to open input/output file!\n";
        return 1;
     }
      clock_t start = clock();
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    FOR(i,0,T){
        solve();
        cerr<<"finish"<<endl;
        // cout.flush();
      }

    #ifdef ON_PC
      clock_t end = clock();
      double ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
      cerr << "Finished in " << ms << " ms" << nl;
    #endif
    return 0;
}
