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

//======= SIGNAL HANDLER FOR DEBUGGING ======== 
void signalHandler(int signum) {
    cerr << "\nCaught signal: " << signum << endl;
    // dbg(...); // add relevant variables to debug
    if (signum == SIGSEGV) cerr << "Segmentation fault detected!\n";
    else if (signum == SIGABRT) cerr << "Aborted!\n";
    exit(signum);
}

// ========== Solve function ==========
int n,m,k;
void solve(){
  cin >> n >> m>> k; 
  //do thi adj[u] = {(v,time)}
  vt<vt<pii>> adj(n+1, vt<pii>());
  FOR(i,0,m){
    int u,v,t;
    cin >> u >> v >> t;
    adj[u].pb({v,t});
    adj[v].pb({u,t});
  }
  //dist[u][j] = min time to reach u using j "free roads"
  vt<vt<ll>> dist(n+1, vt<ll>(k+1, LLONG_MAX));

  dist[1][0] = 0;
  //min-heap: (time, (node, used_free_roads))
  priority_queue<tuple<ll, int, int>, vt<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
  pq.push({0, 1, 0});

  while(!pq.empty()){
    auto [d, u, used] = pq.top(); pq.pop();
    if(d > dist[u][used]) continue; //da co cach di tot hon
    for(auto [v,time] : adj[u]){
      //di chuyen binh thuowng
      if(d + time < dist[v][used]){
        dist[v][used] = d + time;
        pq.push({dist[v][used], v, used});
      }
      //di chuyen mien phi neu con du "free roads"
      if(used < k){
        if(d < dist[v][used+1]){
          dist[v][used+1] = d;
          pq.push({dist[v][used+1], v, used+1});
        }
      }
    }
  }

  ll ans = LLONG_MAX; 
  FOR(j,0,k+1){
    chmin(ans, dist[n][j]);
  }
  cout << ans << nl;
}

// ========== Main ==========
int main() {
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    
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
