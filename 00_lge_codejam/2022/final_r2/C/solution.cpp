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

struct DegreeSide{
  vt<int> nodeDeg;
  vt<ll> counts;
  vt<ll> prefixLess;
  vt<ll> contribute;
  int maxDeg;
  ll total = 0;
  void init(vt<int>& deg){
    nodeDeg = deg;
    maxDeg = *max_element(all(deg));
    counts.resize(maxDeg+1,0);
    prefixLess.resize(maxDeg+1,0);
    contribute.resize(maxDeg+1,0);
    for(auto d: deg){
      counts[d]++;
    }
    ll running = 0;
    for(int d= 0; d<=maxDeg; d++){
      prefixLess[d] = running;
      running += counts[d];
    }
    for(int d=0; d<=maxDeg; d++){
      contribute[d] = 1ll * d * counts[d]*(2*prefixLess[d] + counts[d] +1)/2;
      total += contribute[d];
    }
  }

  void dec(int idx){
    int d = nodeDeg[idx];
    nodeDeg[idx]--;
    int d1 = d, d0 = d-1;
    total -= contribute[d1];
    total -= contribute[d0];
    counts[d1]--;
    counts[d0]++;
    prefixLess[d1]++;
    contribute[d1] = 1ll * d1 * counts[d1]*(2*prefixLess[d1] + counts[d1] +1)/2;
    contribute[d0] = 1ll * d0 * counts[d0]*(2*prefixLess[d0] + counts[d0] +1)/2;
    total += contribute[d1];
    total += contribute[d0];
  }

  void inc(int idx){
    int d = nodeDeg[idx];
    nodeDeg[idx]++;
    dbg(d,maxDeg);
    int d0 = d, d1 = d+1;
    total -= contribute[d0];
    total -= contribute[d1];
    counts[d0]--;
    counts[d1]++;
    prefixLess[d1]--;
    contribute[d0] = 1ll * d0 * counts[d0]*(2*prefixLess[d0] + counts[d0] +1)/2;
    contribute[d1] = 1ll * d1 * counts[d1]*(2*prefixLess[d1] + counts[d1] +1)/2;
    total += contribute[d0];
    total += contribute[d1];
  }

};

// ========== Solve function ==========
int n,m,k;
void solve(){
  cin >> n >> m >> k; 
  vt<int> degX, degY;
  vt<pii> edges;
  degX.resize(n,0);
  degY.resize(m,0);
  REP(i,k){
    int x,y; cin >> x >> y;
    degX[--x]++;
    degY[--y]++;
    edges.pb({x,y});
  }
  dbg(degX);
  DegreeSide sideX, sideY;
  sideX.init(degX);
  sideY.init(degY);
  ll base = sideX.total + sideY.total;
  // cout << base << nl;
  vt<ll> ans(k,0);
  REP(i,k){
    dbg(edges[i]);
    int x = edges[i].fi;
    int y = edges[i].se;
    sideX.dec(x);
    sideY.dec(y);
    ll curr = sideX.total + sideY.total;
    ans[i] = curr;
    sideX.inc(x);
    sideY.inc(y);
  }
  cout << base << " "<< *max_element(all(ans))<< nl;
  // cout.flush();
  
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
