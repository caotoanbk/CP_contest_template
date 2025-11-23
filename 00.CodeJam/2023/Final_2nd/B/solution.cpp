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
int n,m;
vt<int> d;
void solve(){
  cin >> n >> m;
  d.resize(n);
  FOR(i,1, n){
    cin >> d[i];
  } 
  //build coordinate x X[i] = khoang cach tu room 1 dem room i
  vt<ll> X(n+1, 0);
  FOR(i,1, n+1){
    X[i+1] = X[i] + d[i];
  }

  // prefix sum
  vt<ll> P1(n+1, 0), P2(n+1, 0);
  FOR(i, 1, n+1){
    P1[i] = P1[i-1] + X[i];
    P2[i] = P2[i-1] + 1ll* X[i]*i;
  }

  auto S = [&](int i, int j){
    return 2*(P2[j] - P2[i-1]) - 1ll*(i+j)*(P1[j] - P1[i-1]);
  };

  ll lo = 0;
  ll hi = S(1,n);

  auto feasible = [&](ll T) -> bool{
    int l =1;
    int cnt = 0;
    while(l <=n){
      int r = l;
      while(r<=n && S(l,r) <= T) r++;
      cnt++;
      l = r;
    }

    return cnt <= m;
  };

  ll ans;
  while(lo <= hi){
    ll mid = lo + (hi-lo)/2;
    if(feasible(mid)){
      ans = mid;
      hi = mid-1;
    }else{
      lo = mid+1;
    }
  }
  cout << ans << "\n";

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
