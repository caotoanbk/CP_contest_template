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
const ll MOD = 1000003;
struct Point {int r,c; bool snack;};

ll modPow(ll a, ll e){
  ll r = 1;
  while(e){
    if(e&1) r = (r*a) % MOD;
    a = (a*a) % MOD;
    e >>= 1;
  }
  return r;
}

// ========== Solve function ==========
void solve(){
  int R, C, N;
  if(!(cin >> R >> C >> N)) return;
  vt<Point> pts;
  pts.pb({1,1,false});
  REP(i,N){
    int r,c; cin >> r >> c;
    pts.pb({r,c,true});
  }
  pts.pb({R,C,false});
  sort(all(pts), [](const Point& a, const Point& b){
    if(a.r != b.r) return a.r < b.r;
    return a.c < b.c;
  });
  int M = sz(pts);
  // int MAX = R + C + 2;
  vt<ll> fact(MOD),invFact(MOD);
  fact[0] = 1;
  FOR(i,1,MOD) fact[i] = (fact[i-1]*i) % MOD;
  invFact[MOD-1] = modPow(fact[MOD-1], MOD-2);
  for(int i = MOD-2; i >= 0; --i){
    invFact[i] = (invFact[i+1]*(i+1)) % MOD;
  }

  auto nCrSmal = [&](int n, int r) -> ll {
    if(r > n || r < 0) return 0;
    return (fact[n] * ((invFact[r] * invFact[n - r]) % MOD)) % MOD;
  };

  auto lucas = [&](ll n, ll r) -> ll {
    if(r > n || r < 0) return 0;
    ll res = 1;
    while(n > 0 || r > 0){
      int ni = n % MOD;
      int ri = r % MOD;
      res = (res * nCrSmal(ni, ri)) % MOD;
      n /= MOD;
      r /= MOD;
    }
    return res;
  };

  auto raw = [&](int a, int b){
    int dr = pts[b].r - pts[a].r;
    int dc = pts[b].c - pts[a].c;
    if(dr < 0 || dc < 0) return 0ll;
    return lucas(dr + dc, dr);
  };

  //advoid[j][i]: so duong di tu j den i ma khong an snack
  vt<vt<ll>> avoid(M, vt<ll>(M, 0));
  REP(i, M){
    REP(j,i){
      ll total = raw(j,i);
      if(!total) continue;
      FOR(k, j+1, i){
        if(pts[k].r >= pts[j].r && pts[k].c >= pts[j].c && 
          pts[k].r <= pts[i].r && pts[k].c <= pts[i].c && pts[k].snack){
          total = (total - avoid[j][k] * raw(k,i) % MOD + MOD) % MOD;
        }
      }
      avoid[j][i] = total;
    }
  }

  vt<int> bestSnack(M, -1);
  vt<ll> ways(M, 0);
  bestSnack[0] = 0;
  ways[0] = 1;
  FOR(i,1,M){
    int best = -1;
    ll cnt = 0;
    FOR(j, 0, i){
      ll paths = avoid[j][i];
      if(paths == 0) continue;
      int gain = bestSnack[j] + (pts[i].snack ? 1 : 0);
      if(gain > best){
        best = gain;
        cnt = ways[j] * paths % MOD;
      } else if(gain == best){
        cnt = (cnt + ways[j] * paths) % MOD;
      }
    }
    bestSnack[i] = best;
    ways[i] = cnt;
  }


  cout << ways[M-1] << nl;
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
