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
int n;
vt<ll> B;
void solve(){
  cin >> n;
  B.resize(n+1);
  REP(i,n){
    cin >> B[i+1];
  } 

  //next greater to right (strictly >)
  vt<int> nextGeater(n+2, n+1);
  {
    vt<int> st;
    for(int i= n; i>=1; --i){
      while(!st.empty() && B[st.back()] <= B[i]) st.pop_back();
      nextGeater[i] = st.empty() ? n+1 : st.back();;
      st.push_back(i);
    }
  }
  //previous greater to left (strictly >)
  vt<int> prevGreater(n+2, 0);
  {
    vt<int> st;
    for(int i= 1; i<=n; ++i){
      while(!st.empty() && B[st.back()] <= B[i]) st.pop_back();
      prevGreater[i] = st.empty() ? 0 : st.back();
      st.push_back(i);
    }
  }
  unordered_map<int, vt<int>> pos;
  pos.reserve(2 * n); // để đạt LF ~0.5
  FOR(i,1,n+1){
    pos[B[i]].pb(i);
  }
  unordered_map<int, vt<ll>> prefixSum;
  prefixSum.reserve(2 * n); // để đạt LF ~0.5
  for(auto& [val, indices] : pos){
    vt<ll> ps(sz(indices)+1, 0);
    REP(i, sz(indices)){
      ps[i+1] = ps[i] + indices[i];
    }
    prefixSum[val] = move(ps);
  }

  ll ans = 0;
  FOR(i,1,n+1){
    ll val = B[i];
    int gR = nextGeater[i];
    if(gR <= n){
      if(gR-i+1 > 2) ans += gR-i+1;
    }
    //right equal endpoints in (i+1, gR-1)
    int L = i+2;
    int R = gR-1;
    if(L <= R){
      auto &vec = pos[val];
      auto &ps = prefixSum[val];
      int l = lower_bound(all(vec), L) - vec.begin();;
      int r = upper_bound(all(vec), R) - vec.begin() - 1;
      if(l <= r){
        ll count = r - l + 1;
        ll sumIndices = ps[r + 1] - ps[l];
        ans += sumIndices - count * (i - 1);
      }
    }

    int gL = prevGreater[i];
    if(gL >= 1){
      if(i - gL + 1 > 2) ans += i - gL + 1;
    }
  }

  cout << ans << nl;


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
