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

bool disjoint(int l1, int r1, int l2, int r2){
  return r1 < l2 || r2 < l1;
}

// ========== Solve function ==========
int n,a,b,c;
vt<int> v;
void solve(){
  cin >> n >> a >> b >> c;
  v.resize(n);
  REP(i,n) cin >> v[i]; 
  ll best = LLONG_MIN;

  vt<ll> P(n+1, 0);
  REP(i,n) P[i+1] = P[i] + v[i];
  auto sumRange = [&](int l, int r){
    return P[r+1] - P[l];
  };

  for(int s1 = 0; s1 +a <=n; s1++){
    int e1 = s1 + a -1;
    ll Sa = sumRange(s1, e1);
    for(int s2=0; s2 + b <= n; s2++){
      int e2 = s2+b-1;
      ll Sb = sumRange(s2, e2);
      if(!disjoint(s1, e1, s2, e2)) continue;
      for(int s3=0; s3 + c <= n; s3++){
        int e3 = s3 + c -1;
        ll Sc = sumRange(s3, e3);
        if(!disjoint(s1, e1, s3, e3)) continue;
        if(!disjoint(s2, e2, s3, e3)) continue;
        ll product = Sa * Sb * Sc;
        chmax(best, product);
      }
    }
  }

  cout << best << nl;
}

// ========== Main ==========
int main() {
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    
    #ifdef ON_PC
      #define SHARE_PATH "D:/C++/CP/99.Share/"
      FILE* f1 = freopen(SHARE_PATH "input.txt","r",stdin);
      FILE* f2 = freopen(SHARE_PATH "ans.txt","w",stdout);
      if(!f1){
        cerr<< "Error when open input"<<"\n";
        return 0;
      }
      clock_t start = clock();
    #endif

    int T = 1;
    cin >> T;
    while(T--){
      // dbg(T);
        solve();
    }

    #ifdef ON_PC
      clock_t end = clock();
      double ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
      cerr << "Finished in " << ms << " ms" << nl;
    #endif
    return 0;
}
