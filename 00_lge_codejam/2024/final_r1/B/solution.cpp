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

void solve(){
  int n,m;
  cin >> n >> m;
  vt<int> X(n);
  REP(i,n){
    cin >> X[i];
  }  
  //build complement set B
  vt<int> usedPos(n+1, 0), usedNeg(n+1, 0);
  for(int x : X){
    if(x > 0) usedPos[x] = 1;
    else usedNeg[-x] = 1;
  }

  vt<int> B;
  FOR(v,1,n+1){
    if(usedPos[v] == 0) B.pb(v);
    if(usedNeg[v] == 0) B.pb(-v);
  }

  int maxScore = n;
  int S = 1 << n;
  vt<vt<ll>> dp(S, vt<ll>(maxScore+1, 0));
  dp[0][0] = 1;
  for(int mask = 0; mask < S; ++mask){
    int pos = __builtin_popcount(mask);
    for(int score = 0; score <= maxScore; ++score){
      ll cur = dp[mask][score];
      for(int j=0; j< n; j++){
        if(mask & (1 << j)) continue;
        int gain =1;
        if((B[j] > 0) ==(X[pos] > 0) && (abs(B[j]) > abs(X[pos]))){
          gain = 0;
        }
        dp[mask | (1 << j)][score + gain] += cur;
      }
    }
    
  }
  cout << dp[S-1][m] << nl;
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
      freopen(SHARE_PATH "output.txt","w",stdout);
      if(!f1){
        cerr<< "Error when open input"<<"\n";
        return 0;
      }
      clock_t start = clock();
    #endif

    int T = 1;
    cin >> T;
    dbg(T);
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
