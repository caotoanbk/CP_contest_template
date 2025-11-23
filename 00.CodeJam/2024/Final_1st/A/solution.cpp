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

struct Prefix2D {
  int n;
  vt<vt<ll>> ps;
  //ps[i][j] = tổng các phần tử a[r][c] với 0 ≤ r < i và 0 ≤ c < j.
  Prefix2D(const vt<string>& a){
    n = sz(a);
    ps.assign(n+1, vt<ll>(n+1, 0));
    REP(i, n){
      REP(j, n){
        ps[i+1][j+1] = ps[i+1][j] + ps[i][j+1] - ps[i][j] + (a[i][j] - '0');
      }
    }
  }

  ll sum(int r1, int c1, int r2, int c2) const{
    //tổng các phần tử a[r][c] với r1 ≤ r < r2 và c1 ≤ c < c2.
    return ps[r2][c2] - ps[r1][c2] - ps[r2][c1] + ps[r1][c1];
  }
};

ll eaten(const Prefix2D& P, int r0, int c0, int size){
  if(size == 1) return 0;
  ll S = P.sum(r0, c0, r0 + size, c0 + size);
  int idx = (int)(S%4);
  int h = size/2;
  struct Quad{int r,c;};
  Quad q[4] ={
    {r0, c0},         //0
    {r0, c0 + h},     //1
    {r0 + h, c0},     //2
    {r0 + h, c0 + h}  //3
  };
  ll eaten_here = P.sum(q[idx].r, q[idx].c, q[idx].r + h, q[idx].c + h);
  ll total = eaten_here;
  REP(i,4){
    if(i != idx){
      total += eaten(P, q[i].r, q[i].c, h);
    }
  }
  return total;
}

// ========== Solve function ==========
void solve(){
  int n;
  cin >> n;
  vt<string> a(n);
  REP(i,n) cin >> a[i];
  Prefix2D P(a);
  ll total = P.sum(0,0,n,n);
  ll eaten_cells = eaten(P, 0, 0, n);
  cout << total - eaten_cells << nl;

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
