#include <bits/stdc++.h>
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "lib/debug2.h"
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

// ========== Solve function ==========
int parseTime(const string& s){
  int h = stoi(s.substr(0, 2));
  int m = stoi(s.substr(3,2));
  int sec = stoi(s.substr(6,2));
  return h * 3600 + m * 60 + sec;
}

ll extendedGcd(ll a, ll b, ll &x, ll &y){
  if(b==0){
    x=1; y= 0;
    return a;
  }
  ll x1, y1;
  ll gcd = extendedGcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a /b)*y1;
  return gcd;
}

int n;
vt<int> T;
vt<int> D;
void solve(){
  cin >> n;
  T.resize(n);
  D.resize(n);
  REP(i, n){
    string s; cin >> s;
    T[i] = parseTime(s);
  }
  REP(i, n) cin >> D[i];
  ll r=0, p=1; //tap nghiem: t =r(mod p), ban dau moi t deu hop le, t o day la thoi gian bat dau cua chu trinh, nen t = 0 (mod 1) la hop le voi moi chu trin
  FOR(i, 1, n){
    ll b = T[i] - T[0];
    ll a = D[0] - D[i];
    ll M = 86400;
    a = (a%M + M) % M;
    b = (b%M + M) % M;
    //giai a*t = b(mod M)
    ll x, y;
    ll g = extendedGcd(a, M, x, y);
    if(b % g != 0){
      cout << 0 << nl;
      return;
    }
    ll mg = M / g;
    x = (x % mg + mg) %mg; //normalize x
    ll t0 = (b/g % mg) * x %mg; //t = t0 (mod mg) la tap nghiem cua a*t = b(mod M)
    //merge t = t0 (mod mg) vao t = r (mod p) => t=r + k*p = t0 (mod mg) => p*k = t0 - r (mod mg)
    //=> p*k = t0 - r (mod mg)
    ll diff = ((t0 - r) % mg + mg) % mg;
    ll g2 = extendedGcd(p, mg, x, y);
    if(diff % g2 != 0){
      cout << 0 << nl;
      return;
    }
    ll mg2 = mg /g2;
    x = (x % mg2 + mg2) % mg2; //normalize x
    ll k0 = (diff/g2 %mg2)*x%mg2; //k = k0 (mod mg2) la tap nghiem cua p*k = t0 - r (mod mg)
    r = r + k0 * p; //cap nhat tap nghiem: t = r + k0*p (mod lcm(p, mg)) la tap nghiem moi sau khi gop
    p = p / g2*mg; //cap nhat mo du: lcm(p, mg) = p/g2*mg
    r = (r % p + p) % p; //normalize r
  }
  cout << 86400 / p << nl; //so chu trinh la 86400/p, vi moi chu trinh co do dai p, va thoi gian lap lai la 86400
}

// ========== Main ==========
int main() {
    #ifdef ON_PC
      #define SHARE_PATH "D:/C++/CP/99.Share/"
      FILE* f1 = freopen(SHARE_PATH "input.txt","r",stdin);
      FILE* f2 = freopen(SHARE_PATH "ans.txt","w",stdout);
      if(!f1){
        cerr<< "Error when open input file!"<<"\n";
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
