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
int n,x,y,z;
vt<int> v;
void solve(){
  ll result = LLONG_MIN;
  cin >> n >> x >> y >> z;
  v.resize(n);
  REP(i,n) cin >> v[i]; 

  auto getMax = [&](int a, int b, int c){
    vt<ll> leftMax(n, LLONG_MIN), rightMax(n, LLONG_MIN);
    vt<ll> leftMin(n, LLONG_MAX), rightMin(n, LLONG_MAX);
    ll windowSum = 0;
    REP(i, a) windowSum += v[i];
    leftMax[a-1] = windowSum;
    leftMin[a-1] = windowSum;
    FOR(i, a, n){
      windowSum += v[i] - v[i - a];
      leftMax[i] = max(leftMax[i-1], windowSum);
      leftMin[i] = min(leftMin[i-1], windowSum);
    }
  
    windowSum = 0;
    
    for(int i= n-1; i>=n-c; --i) windowSum += v[i];
    rightMax[n - c] = windowSum;
    rightMin[n - c] = windowSum;
    for(int i= n - c -1; i>=0; --i){
      windowSum += v[i] - v[i + c];
      rightMax[i] = max(rightMax[i+1], windowSum);
      rightMin[i] = min(rightMin[i+1], windowSum);
    }
    windowSum = 0;
    for(int i= a; i< a+b; ++i) windowSum += v[i];
    for(int i= a; i<= n - b - c; ++i){
      if(i > a){
        windowSum += v[i + b-1] - v[i-1];
      }
      ll Sb = windowSum;
      ll Sa_max = leftMax[i -1];
      ll Sa_min = leftMin[i -1];
      ll Sc_max = rightMax[i + b];
      ll Sc_min = rightMin[i + b];
  
      chmax(result, Sa_max*Sb*Sc_max);
      chmax(result, Sa_min*Sb*Sc_min);
      chmax(result, Sa_max*Sb*Sc_min);
      chmax(result, Sa_min*Sb*Sc_max);
    }
  };
  // getMax(x, y, z);
  // getMax(x, z, y);
  // getMax(y, x, z);
  // getMax(y, z, x);
  // getMax(z, x, y);
  // getMax(z, y, x);
  vt<int> lengths = {x, y, z};
  sort(all(lengths));
  do{
    getMax(lengths[0], lengths[1], lengths[2]);
  }while(next_permutation(all(lengths)));

  cout << result << nl;
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
