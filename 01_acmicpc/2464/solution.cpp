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
ll N;
void solve(){
  cin >> N; 
  bool found_lower = false;
  bool found_higher = false;
  ll temp = N, A=0, B=0;
  // Tìm A (số nhỏ hơn N gần nhất với số bit 1 bằng N)
  {
    int pos = -1;
    REP(i,63){
      bool bit_i =  (temp >> i) & 1;
      bool bit_i1 = (temp >> (i+1)) & 1;
      if(bit_i1 == 1 && bit_i  == 0){
        pos = i;
        break;
      }
    }

    if(pos != -1){
      found_lower = true;
      A = N;
      A &= ~(1ULL << (pos+1));
      A |=  (1ULL << pos);

      int ones = 0, zeros = 0;
      REP(i,pos){
        bool bit_i = (N >> i) & 1;
        if(bit_i) ones++;
        else zeros++;
      }
      A &= ~((1ULL << pos) - 1); // clear all bits lower than pos
      PER(i, pos){
        if(ones > 0){
          A |= (1ULL << i);
          ones--;
        }
      }
    }
  }

  // Tim B (số lớn hơn N gần nhất với số bit 1 bằng N)
  {
    int pos = -1;
    REP(i, 63){
      bool bit_i = (N >> i) & 1;
      bool bit_i1 = (N >> (i+1)) & 1;
      if(bit_i1 == 0 && bit_i == 1){
        pos = i;
        break;
      }
    }
    if(pos != -1){
      found_higher = true;
      B = N;
      B &= ~(1ULL << pos);
      B |=  (1ULL << (pos+1));
      int ones = 0, zeros =0;
      REP(i, pos){
        bool bit_i = (N >> i) & 1;
        if(bit_i) ones++;
        else zeros++;
      }
      B &= ~((1ULL << pos) - 1); // clear all bits lower than pos
      REP(i, pos){
        if(ones > 0){
          B |= (1ULL << i);
          ones--;
        }
      }
    }
  }

  cout << A << " " << B << nl;
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
