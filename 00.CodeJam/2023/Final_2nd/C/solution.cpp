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

struct Cell {int r,c;};
const int INF = 1e9;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// ========== Solve function ==========
void solve(){
  int R, C, N;
  int rt, ct;
  if(!(cin >> R >> C >> N >> rt >> ct)) return;
  --rt; --ct;
  vt<Cell> pawns(N);
  REP(i,N){
    int r,c;
    cin >> r >> c;
    --r; --c;
    pawns[i] = {r,c};
  }
  vt<string> g(R);
  REP(i, R) cin >> g[i];

  auto bfs = [&](int sr, int sc) -> vt<vt<int>>{
    vt<vt<int>> dist(R, vt<int>(C, INF));
    dist[sr][sc] = 0;
    queue<Cell> q;
    q.push({sr, sc});
    while(!q.empty()){
      auto [r,c] = q.front(); q.pop();
      int d = dist[r][c];
      REP(dir,4){
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
        if(g[nr][nc] == 'W') continue;
        if(dist[nr][nc] > d + 1){
          dist[nr][nc] = d + 1;
          q.push({nr, nc});
        }
      }
    }
    return dist;
  };


  //dist0: tu dich
  auto dist0 = bfs(rt, ct);

  //kiem tra reach
  for(auto& p : pawns){
    if(dist0[p.r][p.c] == INF){
      cout << -1 << nl;
      return;
    }
  }

  //dist from each pawn to all cells
  vt<vt<vt<int>>> distPawns(N);
  REP(i,N){
    distPawns[i] = bfs(pawns[i].r, pawns[i].c);
  }

  ll D = 0;
  vt<int> baseDist(N);
  REP(i,N){
    baseDist[i] = dist0[pawns[i].r][pawns[i].c];
    D += baseDist[i];
  }


  ll net = 0;
  REP(r, R){
    REP(c, C){
      if(g[r][c] != 'W') continue;

      //lay cac neighbor trong
      vt<Cell> neigh;
      REP(dir,4){
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
        if(g[nr][nc] == '.'){
          neigh.pb({nr, nc});
        } 
      }


      int m = sz(neigh);
      if(m < 2) continue; //can >= 2 duong de cai tao qua wall
      ll deltaWall = 0;
      REP(i,N){
        ll best = baseDist[i];
        REP(a,m){
          int ra = neigh[a].r;
          int ca = neigh[a].c;
          ll da = dist0[ra][ca];
          if(da >= INF) continue;
          REP(b,m){
            if(a == b) continue;
            int rb = neigh[b].r;
            int cb = neigh[b].c;
            ll db = distPawns[i][rb][cb];;
            if(db >= INF) continue;
            //di qua wall tu neigh[a] den neigh[b]
            ll cand = da + 2+ db; 
            chmin(best, cand);
          }
        }
        deltaWall += ( baseDist[i]-best);
      }
      net += deltaWall;
    }
  }

  cout << D << " " << net << nl;

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
