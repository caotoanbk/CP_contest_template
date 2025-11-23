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
struct Edge {
  int to; ll cap; int rev;
};

struct Dinic{
  int N;
  vt<vt<Edge>> G;
  vt<int> lvl, it;
  Dinic(int n): N(n), G(n), lvl(n), it(n) {}
  void add_edge(int u, int v, ll cap){
    Edge a{v, cap, (int)G[v].size()};
    Edge b{u, 0, (int)G[u].size()};
    G[u].pb(a);
    G[v].pb(b);
  }

  bool bfs(int s, int t){
    fill(all(lvl), -1);
    queue<int> q;
    lvl[s] = 0;
    q.push(s);
    while(!q.empty()){
      int u = q.front(); q.pop();
      for(auto &e : G[u]){
        if(e.cap > 0 && lvl[e.to] < 0){
          lvl[e.to] = lvl[u] + 1;
          q.push(e.to);
        }
      }
    }
    return lvl[t] >= 0;
  }

  bool dfs(int u, int t, ll f){
    if(!f || u == t)  return f;
    for(int &i = it[u]; i< sz(G[u]); ++i){
      Edge &e = G[u][i];
      if(e.cap > 0 && lvl[e.to] == lvl[u] + 1){
        ll d = dfs(e.to, t, min(f, e.cap));
        if(d > 0){
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  ll max_flow(int s, int t){
    ll flow = 0;
    while(bfs(s,t)){
      fill(all(it), 0);
      while(ll f = dfs(s,t, LLONG_MAX)){
        flow += f;
      }
    }
    return flow;
  }
};

// ========== Solve function ==========
void solve(){
  int n,m,s,t;
  cin >> n >> m;
  vt<int> U(m), V(m), W(m);
  REP(i,m){
    cin >> U[i] >> V[i] >> W[i];
    --U[i];
    --V[i];
  }
  cin >> s >> t;
  --s; --t;
  Dinic D(n);
  ll mult = (ll)m+1;
  for(int i=0; i<m; ++i){
    ll cap = W[i]*mult + 1;
    D.add_edge(U[i], V[i], cap);
    D.add_edge(V[i], U[i], cap);
  }

  ll F = D.max_flow(s,t);
  ll cost = F / mult;
  ll edges = F % mult;

  cout << cost << nl;
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
