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

struct NodeDP{
  int len;
  ll cnt;
};
const int MAXN = (int)1e5;
vt<NodeDP> dp[MAXN+1];
int label[MAXN+1];
vt<vt<int>> adj(MAXN+1);

NodeDP dfs(int u, int p){
  int best1 =1;
  ll cnt1 = 1;
  int A=0, B=0;
  ll cA=0, cB=0, sumA =0, sumB=0, sumSqA=0, sumSqB=0;

  for(auto v: adj[u]){
    dbg(u,v);
    if(v == p) continue;
    NodeDP child = dfs(v, u);
    if(label[u] != label[v]){
      int cand = child.len +1;
      if(cand > best1){
        best1 = cand;
        cnt1 = child.cnt;
      }else if(cand == best1){
        cnt1 += child.cnt;
      }
      dbg(cand);

      if(cand > A){
        B = A; cB = cA, sumB = sumA; sumSqB = sumSqA;
        A = cand; cA = child.cnt; sumA = child.cnt; sumSqA = child.cnt * child.cnt;
      }else if (cand == A){
        dbg("equal A");
        sumA += child.cnt;
        sumSqA += child.cnt * child.cnt;
        cA += child.cnt;
      }else if(cand > B){
        B = cand; cB = child.cnt;
        sumB = child.cnt; sumSqB = child.cnt * child.cnt;
      }else if(cand == B){
        cB += child.cnt;  
        sumB += child.cnt;
        sumSqB += child.cnt * child.cnt;
      }

    }
  }

  if(A > 0){
    ll ways = (sumA * sumA - sumSqA) / 2;
    if(ways > 0){
      if(A + A -1 > bestLen){
        bestLen = A + A -1;
        bestCnt = ways;
      }else if(A + A -1 == bestLen){
        bestCnt += ways;
      }
    }else{
      if(B){
        if (A+ B -1 > bestLen){
          bestLen = A + B -1;
          bestCnt = sumA * sumB;
        }else if(A + B -1 == bestLen){
          bestCnt += sumA * sumB;
        }
      }
    }
  }


  if(best1 == bestLen){
    bestCnt += cnt1;
  }else if(best1 > bestLen){
    bestLen = best1;
    bestCnt = cnt1;
  }


  return {best1, cnt1};
}

// ========== Solve function ==========
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
   }
   FOR(i, 1, n+1){
      
      int p; cin >> p;
      if(p){
        adj[p].pb(i);
        adj[i].pb(p);
      }else{
        root = i;
      }
   }
  //  dbg(root);
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
