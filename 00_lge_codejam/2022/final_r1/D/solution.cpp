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

const ll mod = (ll)(1e9)+7;


ll powmod(ll a, ll b){
  ll ans = 1;
  a %= mod;
  while(b){
    if(b&1) ans =ans*a % mod;
    a =a * a % mod;
    b >>= 1;
  }
  return ans;
}

ll modinv(ll a){
  return powmod(a, mod-2);
}

ll geo_sum(ll x, ll len){
  if(len < 2) return 0;
  if(x == 1) return (len-1)%mod;
  ll first = (x%mod) * (x%mod) % mod;
  ll num = (powmod(x, len-1)-1 + mod)%mod;
  ll den = modinv(x-1);
  return (first * num % mod) * den % mod;
}


// ========== Solve function ==========
int n;
vt<int> A;
vt<int> r,l;
unordered_map<int, int> freq, last;

void solve(){
  cin>>n; 
  A.assign(n+1,0);
  r.assign(n+1,0);
  l.assign(n+1,0);
  freq.clear();
  last.clear();
  FOR(i, 1,n+1) cin >> A[i];
  int x = 0;
  FOR(i,1,n+1){
   while(x+1 <= n && freq[A[x+1]] == 0){
    freq[A[++x]]++;
   } 
   r[i] = x;
   freq[A[i]]--;
  }
  // dbg(A);
  // dbg(r);

  int curL = 1;
  FOR(i, 1, n+1){
    if(last.count(A[i])){
      curL =max(curL, last[A[i]] + 1);
    }
    l[i] = curL;
    last[A[i]] = i;
  }  



  ll ans = 0;
  FOR(i,1,n+1){
    int len = r[i]-i+1;
    ans = (ans+ geo_sum(i, len))%mod;

    int y = l[i];
    len = i-y+1;
    ans = (ans+geo_sum(i, len))%mod;

  }

  // ----- i-side -----
    // for(int i=1;i<=n;i++){
    //     int len = r[i] - i + 1;
    //     ans = (ans + geo_sum(i, len)) % mod;
    // }

    // // ----- j-side -----
    // for(int j=1;j<=n;j++){
    //     int len = j - l[j] + 1;
    //     ans = (ans + geo_sum(j, len)) % mod;
    // }
  cout << ans%mod << nl;
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
