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

// ========== Solve function ==========
void solve(){
  int n,m;
  cin >> n >> m;
  vt<vt<int>> a(n, vt<int>(m,0));
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      cin >> a[i][j];
    }
  }


  ll ans = 0;
  if(n<=m){
    for(int x1 = 0; x1 <n ; x1++){
      for(int x2= x1+1; x2<n ; x2++){
        int cnt[21] = {0};
        for(int y=0; y<m; y++){
          int s = a[x1][y] + a[x2][y];
          cnt[s]++;
        }
        for(int t=2; t<=9; t++){
          ans += 1ll * cnt[t]*cnt[20-t];
        }
        ll c10 = cnt[10];
        ans += c10 * (c10 - 1) / 2;
      }
    }
  }else{
    for(int y1 = 0; y1 <m ; y1++){
      for(int y2= y1+1; y2<m ; y2++){
        int cnt[21] = {0};
        for(int x=0; x<n; x++){
          int s = a[x][y1] + a[x][y2];
          cnt[s]++;
        }
        for(int t=2; t<=9; t++){
          ans += 1ll * cnt[t]*cnt[20-t];
        }
        ll c10 = cnt[10];
        ans += c10 * (c10 - 1) / 2;
      }
    }
  }
  cout << ans << nl;
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
    // cin >> T;
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
