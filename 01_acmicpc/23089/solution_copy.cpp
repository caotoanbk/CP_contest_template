#include <bits/stdc++.h>
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "lib\debug2.h"
  #define VEC(v, i) (v.at(i))
  #define MAT(mat, i, j) (mat.at(i).at(j))
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
int n,k;
vt<vt<int>> adj;
vt<vt<int>> down, up;
vt<int> parent;

void dfsDown(int u, int p){
  parent[u] = p;
  down[u][0] = 1;
  for(int v : adj[u]){
    if(v == p) continue;
    dfsDown(v, u);
    for(int dist = 1; dist <= k; dist++){
      down[u][dist] += down[v][dist-1];
    }
  }
}

void dfsUp(int u){
  for(int v: adj[u]){
    if(v == parent[u]) continue;
    up[v][1] +=1; // u is at distance 1 from v
    for(int d = 2; d <= k; d++){
      up[v][d] = up[u][d-1] + down[u][d-1] - down[v][d-2];
    }
    dfsUp(v);
  }
}

void solve(){
 cin >> n >> k;
 adj.assign(n, vt<int>());
 REP(i,n-1){
   int u,v;
   cin >> u >> v;
   u--; v--;
   adj[u].pb(v);
   adj[v].pb(u);
 }
 down.assign(n, vt<int>(k+1, 0));
 up.assign(n, vt<int>(k+1, 0));
 parent.assign(n, -1);
 dfsDown(0, -1);
 dfsUp(0);

 int best = 1;
 for(int u=0; u<n; u++){
  int total =0;
  for(int d=0; d<=k; d++){
    total += down[u][d] + up[u][d];
  }
  chmax(best, total);
 }
  cout << best << nl;
}


// ========== Main ==========
int main() {
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    #ifdef ON_PC
      #define SHARE_PATH "D:/C++/CP/99.Share/"
      FILE* f1 = freopen(SHARE_PATH "input.txt","r",stdin);
      FILE* f2 = freopen(SHARE_PATH "output.txt","w",stdout);
      if(!f1){
        cerr<< "Error when open input"<<"\n";
        return 0;
      }
      clock_t start = clock();
    #endif

    int T = 1;
    // cin >> T;
    while(T--){
        solve();
    }

    #ifdef ON_PC
      clock_t end = clock();
      double ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
      cerr << "Finished in " << ms << " ms" << nl;
    #endif
    return 0;
}
