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

struct State {
  int l, r;
  int sL, sR; // in {-1, 0, +1}
};

struct ParentInfo {
  int prevId;
  char action; // 'L' or 'R'
};

int encodeState(const State& st, int n) {
  int a = st.sL + 1; // 0..2
  int b = st.sR + 1; // 0..2
  int id = st.l;
  id = id * n + st.r;
  id = id * 3 + a;
  id = id * 3 + b;
  return id;
}

State decodeState(int id, int n) {
  State st{};
  int b = id % 3; id /= 3;
  int a = id % 3; id /= 3;
  st.r = id % n; id /= n;
  st.l = id;
  st.sL = a - 1;
  st.sR = b - 1;
  return st;
}

int sign(ll a, ll b){
  if(a < b) return 1;
  if(a > b) return -1;
  return 0;
}
int n;
ll H[401], R[401];
// vt<pll> S;
void solve(){
  cin >> n;
  REP(i, n) cin >> H[i];
  REP(i, n) cin >> R[i];
  vt<int> ord(n);
  iota(all(ord), 0);
  sort(all(ord), [](int i, int j){
    return H[i] >= H[j];
  });

  // S.resize(n);
  // REP(i,n) cin >> S[i].fi;
  // REP(i,n) cin >> S[i].se;
  // sort(all(S), [](const pll& a, const pll& b){
  //   if(a.fi != b.fi) return a.fi > b.fi;
  //   return a.se > b.se;
  // });

  if(n < 3) {cout << -1 << nl; return;}
  if(H[ord[1]] == H[ord[0]]) {cout << -1 << nl; return;}

  int top = ord[0];

  // parent[layer][stateId] = {prevStateId, actionUsedToReachState}
  vt<unordered_map<int, ParentInfo>> parent(n + 1);

  vt<int> cur, nxt;
  unordered_set<int> inCur, inNxt;

  State start{top, top, 0, 0};
  int startId = encodeState(start, n);
  cur.pb(startId);
  inCur.insert(startId);

  for (int t = 1; t <= n - 1; ++t) {
    int x = ord[t];
    nxt.clear();
    inNxt.clear();

    auto addToNext = [&](const State& ns, int prevId, char action) {
      int nid = encodeState(ns, n);
      if (inNxt.insert(nid).second) {
        nxt.pb(nid);
        parent[t + 1][nid] = {prevId, action};
      }
    };

    for (int id : cur) {
      State st = decodeState(id, n);

      // TODO: LEFT transition
      // 1) check H[x] < H[st.l]
      // 2) g = sign(R[x], R[st.l]), require g != 0
      // 3) if st.sL != 0, require g != st.sL
      // 4) build ns:
      //    ns.l = x, ns.r = st.r, ns.sL = g,
      //    ns.sR = (st.l == st.r ? g : st.sR)
      // 5) addToNext(ns, id, 'L')

      // TODO: RIGHT transition
      // 1) check H[x] < H[st.r]
      // 2) g = sign(R[st.r], R[x]), require g != 0
      // 3) if st.sR != 0, require g != st.sR
      // 4) build ns:
      //    ns.l = st.l, ns.r = x, ns.sR = g,
      //    ns.sL = (st.l == st.r ? g : st.sL)
      // 5) addToNext(ns, id, 'R')
    }

    cur.swap(nxt);
    inCur.swap(inNxt);
    if (cur.empty()) break;
  }

  int endId = -1;
  for (int id : cur) {
    State st = decodeState(id, n);
    if (st.l != top && st.r != top) {
      endId = id;
      break;
    }
  }

  if (endId == -1) {
    cout << -1 << nl;
    return;
  }

  vt<char> actionForOrd(n, '?');
  int curId = endId;
  bool okTrace = true;
  for (int layer = n; layer >= 2; --layer) {
    auto it = parent[layer].find(curId);
    if (it == parent[layer].end()) {
      okTrace = false;
      break;
    }
    actionForOrd[layer - 1] = it->second.action;
    curId = it->second.prevId;
  }

  if (!okTrace || curId != startId) {
    // TODO: debug / validate parent storage if this happens.
    cout << -1 << nl;
    return;
  }

  deque<int> ans;
  ans.push_back(top);
  for (int i = 1; i <= n - 1; ++i) {
    int x = ord[i];
    if (actionForOrd[i] == 'L') ans.push_front(x);
    else if (actionForOrd[i] == 'R') ans.push_back(x);
    else {
      // TODO: this should not happen if transitions + trace are complete.
      cout << -1 << nl;
      return;
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << ans[i] + 1 << (i + 1 == n ? '\n' : ' ');
  }

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
