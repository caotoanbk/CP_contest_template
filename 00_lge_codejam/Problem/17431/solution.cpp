#include <bits/stdc++.h>
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "lib\debug2.h"
  #define VEC(v, i) (v.at(i))
  #define MAT(mat, i, j) (mat.at(i).at(j))
#else
  #define VEC(v, i) (v[i])
  #define MAT(mat, i, j) (mat[i][j])
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

// ==========DEFINE OTHER STRUCT/CLASS/VARIABLE ==========
const int MAXN = 5e6+5;
int n, x;
long long H[MAXN], W[MAXN];
long long hs, ha, hb, hc, 
          my_ws, wa, wb, wc;
// Take input from stdin.
void gen(int i){
  if(i == 0){
    H[0] = hs % hc + 1;
    W[0] = my_ws % wc + 1;
  }else{
    H[i] = H[i-1] + 1 
       + (H[i-1] * ha + hb) % hc;
    W[i] = (W[i-1] * wa + wb) % wc + 1;
  }
}
deque<pll> dq;
void solve(){
// ========== Solve function ==========
  cin >> n >> x;
  cin >> hs >> ha >> hb >> hc;
  cin >> my_ws >> wa >> wb >> wc;
  FOR(j, 0, n){
    gen(j);
    if(!empty(dq)){
      dq.push_back({j, H[j]*W[j]});
    }else{
      while(!empty(dq) && H[j] - dq[0].fi > x){
        dq.pop_front();
      }
    }
  }

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
