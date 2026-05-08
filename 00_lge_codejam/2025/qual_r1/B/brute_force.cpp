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
#define FOR(i,a,b) for(int i=(a); i<(b); ++i)
#define REP(i,n) FOR(i,0,n)
#define PER(i,n) for(int i=(n)-1; i>=0; --i)

// ========== Helpers (optional) ==========
template<class T> inline bool chmin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<class T> inline bool chmax(T& a,const T& b){if(b>a){a=b;return true;}return false;}

struct Event{
  ll s,e,p,d;
};
// ========== Solve function ==========
int n,k;
vt<Event> events;
map<int, vt<Event>> events_by_start;
map<int, vt<Event>> events_by_end;
vt<int> timeline;
void solve(){
  cin >> n >> k;
  events.resize(n);
  ll tmp = 0;
  FOR(i,0,n){
    cin >> events[i].s >> events[i].e >> events[i].p >> events[i].d;
    tmp = max(tmp, events[i].e);
  }
  const int MAX_TIME = 10;
  int ans = (int)1e9;
  FOR(i,1,MAX_TIME+1){
    int S = 0;
    int cnt = 0;
    FOR(j,0, n){
      if(events[j].s <= i && events[j].e >= i){
        cnt++;
        S += events[j].p - events[j].d * (i - events[j].s);
      }
    }
    if(cnt >= k){
      chmin(ans, S);
    }
  }
  cout << (ans == (int)1e9 ? -1 : ans) << nl;
  if(ans < -1){
    cout << "inf" << nl;
  }

}

// ========== Main ==========
int main() {
    #ifdef ON_PC
      freopen("../../../Share/input.txt","r",stdin);
      freopen("../../../Share/ans.txt","w",stdout);
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
