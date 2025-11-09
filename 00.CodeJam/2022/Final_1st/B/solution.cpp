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

// ========== Solve function ==========
int n,m,k;
vt<int> v1,v2;
void solve(){
  cin >> n >> m >> k;
  v1.resize(n);
  v2.resize(m);
  FOR(i,0,n){
    cin>>v1[i];
  }
  FOR(i,0,m){
    cin>>v2[i];
  }

  vt<int> sumA, sumB;
  REP(i,1<<n){
    if(__builtin_popcount(i) == k){
      int sum = 0;
      REP(j,n){
        if(i & (1<<j)){
          sum += v1[j];
        }
      }
      sumA.pb(sum);
    }
  }

  REP(i,1<<m){
    if(__builtin_popcount(i) == k){
      int sum = 0;
      REP(j,m){
        if(i & (1<<j)){
          sum += v2[j];
        }
      }
      sumB.pb(sum);
    }
  }
  ll mxA = *max_element(all(sumA));
  ll mxB = *max_element(all(sumB));
  ll minA = *min_element(all(sumA));
  ll minB = *min_element(all(sumB));
  ll maxDiff = max(abs(mxA - minB), abs(mxB - minA));

  sort(all(sumB));
  ll minDiff = LLONG_MAX;
  for(auto x: sumA){
    auto it = lower_bound(all(sumB), x);
    if(it != sumB.end()){
      chmin(minDiff, 0ll+abs(x - *it));
    }
    if(it != sumB.begin()){
      --it;
      chmin(minDiff, 0ll+ abs(x - *it));
    }
  }


  cout <<minDiff << " " << maxDiff << nl;



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
