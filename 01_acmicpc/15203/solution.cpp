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

struct Tarjan{
   int n;
   vector<vector<int>> adj;
   vector<int> low, num, comp, st;
   vt<bool> inStack;
   int dfsTime=0, compCnt = 0;
   Tarjan(int n): n(n), adj(n), low(n, -1), num(n, -1), comp(n, -1), inStack(n, false) {}
    void addEdge(int u, int v){
      adj[u].pb(v);
    }
    void dfs(int u){
      low [u] = num[u] = dfsTime++;
      st.pb(u);
      inStack[u] = true;
      for(int v: adj[u]){
        if(num[v] == -1){
          dfs(v);
          chmin(low[u], low[v]);
        }else{
          if(inStack[v]){
            chmin(low[u], num[v]);
          }
        }
      }
      if(low[u] == num[u]){
        while(true){
          int v = st.back(); st.pop_back();
          inStack[v] = false;
          comp[v] = compCnt;
          if(u == v) break;
        }
        compCnt++;
    }
  }
    void run(){
      FOR(i,0,n){
        if(num[i] == -1){
          dfs(i);
        }
      }
    }
};

// ========== Solve function ==========
int n,m;
void solve(){
  cin >> n >> m;
  Tarjan tj(n);
  REP(i,m){
    int u,v;
    cin >> u >> v;
    u--; v--;
    tj.addEdge(u,v);
  }
  tj.run();
  int C = tj.compCnt;
  vt<int> indeg(C,0);
  for(int u=0; u<n; ++u){
    for(int v: tj.adj[u]){
      if(tj.comp[u] != tj.comp[v]){
        indeg[tj.comp[v]]++;
      }
    }
  }
  int sourceSCC = -1;
  REP(c,C){
    if(indeg[c] == 0){
      if(sourceSCC != -1){ // more than 1 source SCC
        cout << "0\n";
        return;
      }
      sourceSCC = c;
    }
  }
  if(sourceSCC == -1){
    cout << "0\n";
    return;
  }
  vt<int> nodes;
  FOR(i,0,n){
    if(tj.comp[i] == sourceSCC){
      nodes.pb(i);
    }
  }

  //verify 
  {
    vt<char> visited(n, 0);
    queue<int> q;
    q.push(nodes[0]); visited[nodes[0]] = 1;
    while(!q.empty()){
      int u = q.front(); q.pop();
      for(int v: tj.adj[u]){
        if(!visited[v]){
          visited[v] = 1;
          q.push(v);
        }
      }
    }

    FOR(i, 0, n){
      if(!visited[i]){
        cout << "0\n";
        return;
      }
    }
  }

  cout<< sz(nodes) << nl;
  for(int u: nodes){
    cout << (u+1) << " ";
  }
  cout << nl;

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
