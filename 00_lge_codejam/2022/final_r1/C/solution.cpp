#include <bits/stdc++.h>
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "lib\debug2.h"
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

int bestLen = 1;
int bestCnt =0;

inline void updateAns(int len1, int len2){
  if(len1 + len2 -1 > bestLen){
    bestLen = len1 + len2 -1;
    bestCnt = 1;
  }else if(len1 + len2 -1 == bestLen){
    bestCnt++;
  }
}

struct State{
  int mask;
  int len;
};
const int MAXN = (int)1e5;
vt<State> dp[MAXN+1];
int label[MAXN+1];
vt<vt<int>> adj(MAXN+1);

// ========== Solve function ==========
void dfs(int u, int p){
  dp[u].clear();
  int mu = (1 << label[u]);
  dp[u].pb({mu, 1});
  for(auto v: adj[u]){
    if(v == p) continue;
    dfs(v, u);
    for(auto st: dp[v]){
      if(st.mask & mu){
        continue;
      }
      bool exist = false;
      for(auto st2: dp[u]){
        if(st2.mask == (st.mask | mu)){
          exist = true;
          break;
        }
      }
      if(!exist) dp[u].pb({st.mask | mu, st.len + 1});
    }
  }

  int k = dp[u].size();
  FOR(i, 0, k){
    FOR(j, i+1, k){
      if(dp[u][i].mask & dp[u][j].mask) continue;
      updateAns(dp[u][i].len, dp[u][j].len);
    }
  }
  FOR(i, 0, k){
    if(dp[u][i].len == bestLen){
      bestCnt++;
    }else if(dp[u][i].len > bestLen){
      bestLen = dp[u][i].len;
      bestCnt = 1;
    }
  }
}
int n,root;
void solve(){
  bestLen = 1;
  bestCnt = 0;
  cin >> n;
   string s; cin >> s;
   FOR(i, 0, n){
      label[i+1] = s[i] - 'A';
   }
   FOR(i, 1, n+1){
      adj[i].clear();
      int p; cin >> p;
      if(p){
        adj[p].pb(i);
        adj[i].pb(p);
      }else{
        root = i;
      }
   }

   dfs(root, 0);

   cout << bestLen << " " << bestCnt << nl;

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
    cin >> T;
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
