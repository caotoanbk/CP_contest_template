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
void solve(){
  ll n, k, a, b;
  cin >> n >> k >> a >> b;
  
  vt<ll> s(n);
  ll total = 0;
  ll count_ones = 0;
  
  REP(i, n){
    cin >> s[i];
    total += s[i];
    if(s[i] == 1) count_ones++;
  }
  
  // Check if possible
  if(total < k){
    cout << -1 << nl;
    return;
  }
  
  // Already have enough unit sticks
  if(count_ones >= k){
    cout << 0 << nl;
    return;
  }
  
  // Need to cut: k - count_ones more unit sticks
  ll needed = k - count_ones;
  
  // DP: dp[j] = minimum cost to get at least j unit sticks from cutting
  vt<ll> dp(needed + 1, LLONG_MAX);
  dp[0] = 0;
  
  REP(i, n){
    if(s[i] >= 2){
      ll L = s[i];
      ll cost = a * (L - 1) * (L - 1) + b;
      
      // Update DP in reverse order (0/1 knapsack)
      for(ll j = needed; j >= 0; --j){
        if(dp[j] != LLONG_MAX){
          ll next = min(needed, j + L);
          chmin(dp[next], dp[j] + cost);
        }
      }
    }
  }
  
  if(dp[needed] == LLONG_MAX){
    cout << -1 << nl;
  } else {
    cout << dp[needed] << nl;
  }
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
