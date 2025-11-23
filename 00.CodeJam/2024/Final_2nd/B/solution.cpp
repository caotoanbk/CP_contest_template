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

// ==========DEFINE OTHER STRUCT/CLASS/VARIABLE ==========
struct Seg{
  int n;
  static const ll MOD = 1e9+7;
  vt<ll> st, lazy;
  inline ll norm_mod(ll x){ return ((x % MOD) + MOD) % MOD; }
  Seg(int N=0){init(N);}
  void init(int N){
    n = N;
    st.assign(4*n+10, 0);
    lazy.assign(4*n+10, 0);
  }

  void build(const vt<ll>& a, int p, int l, int r){
    if(l == r){
      st[p] = a[l];
      return;
    }
    int m = (l + r) / 2;
    build(a, p*2, l, m);
    build(a, p*2+1, m+1, r);
    st[p] = st[p*2] + st[p*2+1];
  }

  void push(int p, int l, int r){
    if(lazy[p] != 0 && l != r){
      int m = (l + r) / 2;
      st[p*2] = (st[p*2] + lazy[p] * (m - l + 1)) % MOD;
      st[p*2+1] =  (st[p*2+1] + lazy[p] * (r - m)) % MOD;
      lazy[p*2] = (lazy[p*2] + lazy[p]) % MOD;
      lazy[p*2+1] = (lazy[p*2+1] + lazy[p]) % MOD;
      lazy[p] = 0;
    }else if(l == r){
      lazy[p] = 0;
    }
  }

  void rangeAdd(int p, int l, int r, int ql, int qr, ll v){
    if(ql > r || qr < l) return;
    if(ql <= l && r <= qr){
      v = norm_mod(v);
      st[p] = (st[p] + v * (r - l + 1)) % MOD;
      lazy[p] = (lazy[p]+v)%MOD;
      return;
    }
    push(p, l, r);
    int m = (l + r) / 2;
    rangeAdd(p*2, l, m, ql, qr, v);
    rangeAdd(p*2+1, m+1, r, ql, qr, v);
    st[p] = (st[p*2] + st[p*2+1]) % MOD;
  }

  ll rangeSum(int p, int l, int r, int ql, int qr){
    if(ql > r || qr < l) return 0;
    if(ql <= l && r <= qr){
      return st[p];
    }
    push(p, l, r);
    int m = (l + r) / 2;
    return (rangeSum(p*2, l, m, ql, qr) + rangeSum(p*2+1, m+1, r, ql, qr)) % MOD;
  }

  void rangeAdd(int l, int r, ll v){
    rangeAdd(1, 0, n-1, l, r, v);
  }

  ll rangeSum(int l, int r){
    return rangeSum(1, 0, n-1, l, r);
  }
};

// int norm(int x, int N){
//   return (x % N + N) % N;
int norm(int x,int N){
    x%=N;
    if(x<0) x+=N;
    return x;
}

// ========== Solve function ==========
void solve(){
  int n,m;
  cin >> n >> m;
  vt<ll> V(n);
  REP(i,n) cin >> V[i]; 
  
  Seg seg(n);
  seg.build(V,1,0,n-1);

  int offset = 0; //origin maps to physical index offset
  int dir =1; //+1 normal, -1 reversed
  
  vt<ll> answers;
  vt<int> S(m); vt<ll> X(m), Y(m);
  REP(i,m){
    cin >> S[i];
  }
  REP(i,m){
    cin >> X[i];
  }
  REP(i,m){
    cin >> Y[i];
  }
  dbg(V,S, X, Y);
  for(int k=0; k<m; k++){
    int s; ll x,y;
    s = S[k]; x = X[k]; y = Y[k];
    if(s == 1){          // rotate CCW x
      offset = norm(offset + dir*(int)x, n);
    } else if(s == 2){   // rotate CW x
      offset = norm(offset - dir*(int)x, n);
    } else if(s == 3){
      dir = -dir;
    } else if(s == 4){
      int len = (int)x;
      // len ∈ [1,n] theo đề
      if(dir == 1){
        int l = offset;
        int r = offset + len - 1;
        if(r < n){
          seg.rangeAdd(l,r,y);
        }else{
          r %= n;
          seg.rangeAdd(l,n-1,y);
          seg.rangeAdd(0,r,y);
        }
      }else{
        int start = norm(offset - (len-1), n);
        int end = offset;
        if(start <= end){
          seg.rangeAdd(start,end,y);
        }else{
          seg.rangeAdd(start,n-1,y);
          seg.rangeAdd(0,end,y);
        }
      }
    } else if(s == 5){
      int len = (int)x;
      ll res=0;
      if(dir == 1){
        int l = offset;
        int r = offset + len - 1;
        if(r < n){
          res = seg.rangeSum(l,r);
        }else{
          r %= n;
          res = (seg.rangeSum(l,n-1) + seg.rangeSum(0,r)) % Seg::MOD;
        }
      }else{
        int start = norm(offset - (len-1), n);
        int end = offset;
        if(start <= end){
          res = seg.rangeSum(start,end);
        }else{
          res = (seg.rangeSum(start,n-1) + seg.rangeSum(0,end)) % Seg::MOD;
        }
      }
      answers.push_back(res);
    }
  }

  for(ll ans : answers){
    cout << ans % Seg::MOD << " ";
  }
  cout << nl;
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
