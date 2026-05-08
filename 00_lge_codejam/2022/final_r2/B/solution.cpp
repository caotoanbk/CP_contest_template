#include <bits/stdc++.h>
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "../../../../99.Share/lib/debug2.h"
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
  int n, root;
  cin >> n;
  vt<int> p(n+1, 0);
  vt<int> v(n+1, 0);
  vt<vt<int>> child(n+1, vt<int>());
  FOR(i,1,n+1) cin >> v[i];
  FOR(i,1,n+1) {
    cin >> p[i];
    if(p[i] == 0) root = i;
    else child[p[i]].pb(i);
  }
  // VEC(v, 1) = 2;

  stack<int> st;
  vt<int> order;
  st.push(root);
  while(!st.empty()){
    int u = st.top(); st.pop();
    order.pb(u);
    for(int c : child[u]){
      st.push(c);
    }
  }
  vt<ll> dp0(n+1, 0); // ko chon u
  vt<ll> dp1(n+1, 0); // chon u
  for(int i = sz(order)-1; i >= 0; --i){
    int u = order[i];
    if(child[u].empty()){
      dp1[u] = v[u];
      dp0[u] = 0;
      continue;
    }

    //u chon
    ll sumIfChooseU = v[u];
    for(int c : child[u]){
      sumIfChooseU += dp0[c];
    }
    dp1[u] = sumIfChooseU;

    //u ko chon, phai co >=1 con dc chon
  bool hasChosenChild = false;
  ll best = 0;
  // bestDiff keeps the MAXIMUM (dp1[c] - dp0[c]) among children where we initially took dp0[c].
  // If no child was chosen (hasChosenChild == false), we must upgrade one child from dp0 to dp1,
  // so we add bestDiff (which may be negative) to minimize loss. Original code took the minimum difference (worst choice).
  ll bestDiff = LLONG_MIN;
    for(int c : child[u]){
     ll take0 = dp0[c];
     ll take1 = dp1[c]; 
     if(take1 > take0){
       hasChosenChild = true;
       best += take1;
     }
     else{
       best += take0;
       bestDiff = max(bestDiff, take1 - take0); // choose child with largest (least negative) diff if forced later
     }
    }
    if(!hasChosenChild){
      best += bestDiff; // enforce picking one child
    }
     dp0[u] = best;
   }
    
  cout << max(dp0[root], dp1[root]) << nl;


  
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
