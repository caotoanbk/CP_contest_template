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
int n;
vt<int> T;
vt<int> D;

auto parseTime(const string& s){
  int h = stoi(s.substr(0, 2));
  int m = stoi(s.substr(3,2));
  int sec = stoi(s.substr(6,2));
  return h * 3600 + m * 60 + sec;
};

ll extendedGCD(ll a, ll b, ll& x, ll& y){
  if(b == 0){
    x = 1; y = 0;
    return a;
  }
  ll x1, y1;
  ll gcd = extendedGCD(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a /b)*y1;
  return gcd;
}


void solve(){
  cin >> n;
  T.resize(n);
  D.resize(n);
  REP(i, n){
    string s; cin >> s;
    T[i] = parseTime(s);
  }
  REP(i, n) cin >> D[i];

  ll r = 0, p = 1; // tap nghiem: t ≡ r (mod p), ban dau moi t deu hop le

  FOR(i, 1, n){
    // Dieu kien dong bo: (D[i]-D[0])*t ≡ (T[0]-T[i]) (mod 86400)
    ll M = 86400;
    ll a = ((ll)(D[i] - D[0]) % M + M) % M;
    ll b = ((ll)(T[0] - T[i]) % M + M) % M;

    // Phase 2: giai a*t ≡ b (mod M)
    ll x, y;
    ll g = extendedGCD(a, M, x, y);
    if (b % g != 0) { cout << 0 << nl; return; }

    ll mg = M / g;
    x = ((x % mg) + mg) % mg;           // normalize x
    ll t0 = (b / g % mg) * x % mg;      // t ≡ t0 (mod mg)

    // Phase 3: merge t ≡ t0 (mod mg) vao t ≡ r (mod p)
    // => p*k ≡ (t0 - r) (mod mg)
    ll diff = ((t0 - r) % mg + mg) % mg;
    ll g2 = extendedGCD(p, mg, x, y);
    if (diff % g2 != 0) { cout << 0 << nl; return; }

    ll mg2 = mg / g2;
    x = ((x % mg2) + mg2) % mg2;        // x = inv(p/g2) mod mg2
    ll k = (diff / g2 % mg2) * x % mg2;
    r = r + p * k;
    p = p / g2 * mg;                     // = lcm(p, mg)
    r = r % p;
  }

  cout << 86400 / p << nl;
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
