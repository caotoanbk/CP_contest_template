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
struct State {
  int l, r;
  int sL, sR; // in {-1, 0, +1}
};
struct ParentInfo{
  int prevId;
  char action; // 'L' or 'R'
};
int encodeState(const State& st, int n){
  int id = st.l;
  id = id *n + st.r;
  int a = st.sL + 1; // map {-1,0,1} to {0,1,2}
  int b = st.sR + 1;
  id = id * 3 + a;
  id = id * 3 + b;
  return id;
}
State decodeState(int id , int n){
  State st{};
  int b = id % 3; id /= 3;
  int a = id % 3; id /= 3;
  st.r = id % n; id /= n;
  st.l = id;
  st.sL = a - 1; // map back to {-1,0,1}
  st.sR = b - 1;
  return st;
}

int sign(int x, int y){
  if(x == y) return 0;
  return x < y ? 1 : -1;
}

int n;
vt<int> H, R;
void solve(){
  cin >> n;
  H.resize(n); R.resize(n);
  REP(i,n) cin >> H[i];
  REP(i,n) cin >> R[i];
  vt<int> ord(n);
  iota(all(ord), 0);
  sort(all(ord), [](int i, int j){
    return H[i] >= H[j];
  });

  if(n < 3) {cout << -1 << nl; return;}
  if(H[ord[0]] == H[ord[1]]) {cout << -1 << nl; return;}
  int top = ord[0];

  vt<int> cur, nxt;
  unordered_set<int> inNxt;
  cur.push_back(encodeState({top, top, 0, 0}, n));
  vt<unordered_map<int, ParentInfo>> parent(n + 1); // parent[layer][stateId] = {prevStateId, actionUsedToReachState}
  for(int layer = 1; layer < n; layer++){
    int x = ord[layer];
    nxt.clear(); inNxt.clear();
    auto addToNext = [&](const State& ns, int prevId, char action){
      int nsId = encodeState(ns, n);
      if(inNxt.insert(nsId).second){
        nxt.push_back(nsId);
        parent[layer][nsId] = {prevId, action};
      }
    };

    for(int id : cur){
      State st = decodeState(id, n);
      // Try LEFT transition
      if(H[x] < H[st.l]){
        int g = sign(R[x], R[st.l]);
        if(g != 0 && (st.sL == 0 || g != st.sL)){
          State ns{.l = x, .r = st.r, .sL = g, .sR = (st.l == st.r ? g : st.sR)};
          addToNext(ns, id, 'L');
        }
      }

      // Try RIGHT transition
      if(H[x] < H[st.r]){
        int g = sign(R[st.r], R[x]);
        if(g != 0 && (st.sR == 0 || g != st.sR)){
          State ns{.l = st.l, .r = x, .sL =(st.l == st.r ? g : st.sL), .sR = g};
          addToNext(ns, id, 'R');
        }
      }
    }
    swap(cur, nxt);
    if(cur.empty()) break;
  }
  int endId = -1;
  for(int id : cur){
    State st = decodeState(id, n);
    if(st.l != top && st.r != top){
      endId = id;
      break;
    }
  }
  if(endId == -1){
    cout << -1 << nl;
    return;
  }
  vt<char> actionForOrd(n, '?');
  int curId = endId;
  bool okTrace = true;
  for(int layer = n-1; layer >= 1; layer--){
    auto it = parent[layer].find(curId);
    if(it == parent[layer].end()){
      okTrace = false;
      break;
    }
    actionForOrd[layer] = it->second.action;
    curId = it->second.prevId;
  }
  if(!okTrace || curId != encodeState({top, top, 0, 0}, n)){
    cout << -1 << nl;
    return;
  }
  deque<int> ans;
  ans.push_back(top);
  for(int i = 1; i <= n-1; i++){
    int x = ord[i];
    if(actionForOrd[i] == 'L') ans.push_front(x);
    else if(actionForOrd[i] == 'R') ans.push_back(x);
    else{
      cout << -1 << nl;
      return;
    }
  }
  for(int i : ans){
    cout << i+1 << ' ';
  }
  cout << nl;

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
    // dbg(T);
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
