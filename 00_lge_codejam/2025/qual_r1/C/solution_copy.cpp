#include <bits/stdc++.h>
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "lib/debug2.h"
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
const array<ll,4> trominoHoleMap = {3, 2, 1, 0 };
vector<array<array<ll,4>,4>> G;
int k;
ll x,y;

int quadrant_once(int k, int x, int y) {
    int mid = 1 << (k - 1);
    if(x < mid && y < mid) return 0;
    if(x < mid && y >= mid) return 1;
    if(x >= mid && y < mid) return 2;
    return 3;
}

array<ll, 4> countTromnios(int k, ll x, ll y){
  array<ll, 4> res = {0, 0, 0, 0};
  ll curK= k,curX = x, curY = y;
  while(curK > 1){
    ll mid = 1 << (curK - 1);
    int q;
    if(curX <mid){
      if(curY < mid) q=0; else q=1;
    }
    else{
      if(curY < mid) q=2; else q=3;
    }
    res[trominoHoleMap[q]]++;
    REP(child,4){
      if(child == q) continue;
      int childHole = trominoHoleMap[child];
      REP(qq,4){
        res[qq] += G[curK-1][childHole][qq];
      }
    }
    if(q == 1) curY -= mid;
    else if(q == 2) curX -= mid;
    else if(q == 3) curX -= mid, curY -= mid;
    curK--;
  }

  int finalHole = quadrant_once(1, curX, curY);
  res[trominoHoleMap[finalHole]]++;
  return res;
}

void precompute() {
    G.resize(31);
    G[1][0] = {0, 0, 0,1};
    G[1][1] = {0, 0, 1,0};
    G[1][2] = {0, 1, 0,0};
    G[1][3] = {1, 0, 0,0};


    FOR(i,2,31){
      REP(hole,4){
        array<ll,4> cnt = {0, 0, 0, 0};
        cnt[trominoHoleMap[hole]]++;
        REP(child,4) {
          int childHole = (child == hole) ? hole : trominoHoleMap[child];
          REP(q,4) {
            cnt[q] += G[i-1][childHole][q];
          }
        }
        G[i][hole] = cnt;
      }
    }
}
void solve() {
  const int MAX_T = (int)3*1e5;
  cout << MAX_T << nl;
  ll x=10123123,y=160032132,k=30;
  // cout << k << " " << x << " " << y << nl;
  array<ll,4> res = countTromnios(30, x, y);
  REP(t,MAX_T){
    cout << k<<" "<< res[0] << " " << res[1] << " " << res[2] << " " << res[3] << nl;
  }
}

// ========== Main ==========
int main() {
    #ifdef ON_PC
      // freopen("../../../Share/input.txt","r",stdin);
      freopen("../../../Share/input.txt","w",stdout);
      clock_t start = clock();
    #endif

    int T = 1;
    // cin >> T;
    precompute();
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
