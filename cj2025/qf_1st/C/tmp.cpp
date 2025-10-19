#include <bits/stdc++.h>
#include "../../../Share/lib/testlib.h"
using namespace std;

// ========== Debug ==========
#ifdef ON_PC
  #include "../../../Share/lib/debug2.h"
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
pair<ll,ll> findHole(int k, array<ll, 4> cnt){
  ll ox=0, oy=0;
  int curK = k;
  while(curK > 1){
    bool found = false;
    int chosen_h = -1;
    array<ll,4> contributed = {0,0,0,0};
    for(int hole =0; hole < 4 && !found; hole++){
      array<ll,4> curCnt = {0,0,0,0};
      curCnt[trominoHoleMap[hole]]++;
      REP(child,4){
        int childHole = (child == hole) ? hole : trominoHoleMap[child];
        REP(q,4){
          curCnt[q] += G[curK-1][childHole][q];
        }
      }

      bool ok = true;
      REP(q,4){
        if(curCnt[q] > cnt[q]) ok = false;
      }
      if(ok){
        chosen_h = hole;
        found = true;
        REP(q,4){
          contributed[q] = curCnt[q];
        }
      }
    }

    if(found == false) {
      return {-1,-1};
    }

    REP(q,4){
      cnt[q] -= contributed[q];
    }
    int mid = 1 << (curK - 1);
    if(chosen_h == 0){
    }
    else if(chosen_h == 1){
      oy += mid;
    }
    else if(chosen_h == 2){
      ox += mid;
    }
    else if(chosen_h == 3){
      ox += mid;
      oy += mid;
    }
    curK--;
  }
  int finalHole = -1;
  REP(t,4){
    if(cnt[t] == 1){
      if(finalHole != -1){
        return {-1,-1};
      }else{
        finalHole = trominoHoleMap[t];
      }
    }else if(cnt[t] != 0){
      return {-1,-1};
    }
  }
  if(finalHole == -1) return {-1,-1};
  if(finalHole == 0){
  }
  else if(finalHole == 1){
    oy += 1;
  }
  else if(finalHole == 2){
    ox += 1;
  }
  else if(finalHole == 3){
    ox += 1;
    oy += 1;
  }

  return {ox, oy};
}
bool dfs(int k, ll ox, ll oy, array<ll,4>& cnt, pair<ll,ll>& res){
  if(k == 1){
    int finalHole = -1;
    REP(t,4){
      if(cnt[t] == 1){
        if(finalHole != -1){
          return false;
        }else{
          finalHole = trominoHoleMap[t];
        }
      }else if(cnt[t] != 0){
        return false;
      }
    }
    if(finalHole == -1) return false;
    if(finalHole == 0){
    }
    else if(finalHole == 1){
      res = {ox, oy+1};
    }
    else if(finalHole == 2){
      res = {ox+1, oy};
    }
    else if(finalHole == 3){
      res = {ox+1, oy+1};
    }
    return true;
  }
  int mid = 1 << (k - 1);
  for(int hole =0; hole < 4; hole++){
    array<ll, 4> curCnt = {0,0,0,0};
    curCnt[trominoHoleMap[hole]]++;
    for(int child =0; child <4; child++){
      if(child == hole) continue;
      int childHole = (child == hole) ? hole : trominoHoleMap[child];
      REP(q,4){
        curCnt[q] += G[k-1][childHole][q];
      }
    }
    bool ok = true;
    REP(q,4){
      if(curCnt[q] > cnt[q]) ok = false;
    }
    if(!ok) continue;

    array<ll,4> newCnt = cnt;
    REP(q,4){
      newCnt[q] -= curCnt[q];
    }
    ll nOx = ox, nOy = oy;
    if(hole == 0){
    }
    else if(hole == 1){
      nOy += mid;
    }
    else if(hole == 2){
      nOx += mid;
    }
    else if(hole == 3){
      nOx += mid;
      nOy += mid;
    }
    if(dfs(k-1, nOx, nOy, newCnt, res)){
      return true;
    }
  }
  return false;
}
void solve2(){
  array<ll,4> cnt;
  cin >> k >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3];
  // cin >> k >> x >> y;
  G.resize(k+1);
  G[1][0] = {0, 0, 0,1};
  G[1][1] = {0, 0, 1,0};
  G[1][2] = {0, 1, 0,0};
  G[1][3] = {1, 0, 0,0};


  FOR(i,2,k+1){
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

  //bai toan dem so luong tromino
  // array<ll, 4> ans = countTromnios(k, x, y);
  // cout<< ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << nl;

  //bai toan tim hole
  pair<ll,ll> res;
  if(dfs(k,0,0,cnt,res)) {
    cout << res.first << " " << res.second << nl;
  }else {
    cout << -1 << " " << -1 << nl;
  }
}

// Thuật toán greedy O(k) - chọn quadrant duy nhất có thể
bool solveGreedy(int k, ll ox, ll oy, array<ll,4> cnt, pair<ll,ll>& res) {
    if (k == 1) {
        int finalHole = -1;
        for (int t = 0; t < 4; t++) {
            if (cnt[t] == 1) {
                if (finalHole != -1) return false;
                finalHole = trominoHoleMap[t];
            } else if (cnt[t] != 0) {
                return false;
            }
        }
        
        if (finalHole == -1) return false;
        
        if (finalHole == 0) res = {ox, oy};
        else if (finalHole == 1) res = {ox + 1, oy};
        else if (finalHole == 2) res = {ox, oy + 1};
        else res = {ox + 1, oy + 1};
        
        return true;
    }
    
    ll mid = 1LL << (k - 1);
    
    // Tìm quadrant duy nhất khả thi
    int validHole = -1;
    array<ll,4> validNewCnt;
    ll validNOx, validNOy;
    
    for (int hole = 0; hole < 4; hole++) {
        // Tính curCnt cho 3 subtree không chứa hole thật
        array<ll, 4> curCnt = {0, 0, 0, 0};
        curCnt[trominoHoleMap[hole]]++;
        
        for (int child = 0; child < 4; child++) {
            if (child == hole) continue;
            int childHole = trominoHoleMap[child];
            for (int q = 0; q < 4; q++) {
                curCnt[q] += G[k-1][childHole][q];
            }
        }
        
        // Kiểm tra đủ không
        bool ok = true;
        array<ll,4> newCnt;
        for (int q = 0; q < 4; q++) {
            if (curCnt[q] > cnt[q]) {
                ok = false;
                break;
            }
            newCnt[q] = cnt[q] - curCnt[q];
        }
        
        if (!ok) continue;
        
        // Kiểm tra thêm: newCnt phải tương ứng với MỘT cấu hình hole nào đó ở level k-1
        // Tức là phải tồn tại hole' sao cho newCnt giống hoặc có thể dẫn đến G[k-1][hole']
        
        // Ý tưởng: nếu tổng newCnt đúng thì ok
        ll totalNew = 0;
        for (int q = 0; q < 4; q++) {
            if (newCnt[q] < 0) {
                ok = false;
                break;
            }
            totalNew += newCnt[q];
        }
        
        ll expectedForSubtree = 0;
        if (k > 1) {
            ll subSize = 1LL << (2 * (k - 1));
            expectedForSubtree = (subSize - 1) / 3;
        }
        
        if (totalNew != expectedForSubtree) continue;
        
        // Quadrant này khả thi
        if (validHole != -1) {
            // Có nhiều hơn 1 quadrant khả thi - cần thử cả
            // Nhưng để tối ưu, ta ưu tiên quadrant có pattern phù hợp nhất
            // Heuristic: chọn quadrant có newCnt gần với G[k-1][hole] nhất
            
            // So sánh với validHole hiện tại
            ll dist1 = 0, dist2 = 0;
            for (int q = 0; q < 4; q++) {
                dist1 += abs(validNewCnt[q] - G[k-1][validHole][q]);
                dist2 += abs(newCnt[q] - G[k-1][hole][q]);
            }
            
            if (dist2 < dist1) {
                validHole = hole;
                validNewCnt = newCnt;
                
                validNOx = ox;
                validNOy = oy;
                if (hole == 1) validNOx += mid;
                else if (hole == 2) validNOy += mid;
                else if (hole == 3) {
                    validNOx += mid;
                    validNOy += mid;
                }
            }
        } else {
            validHole = hole;
            validNewCnt = newCnt;
            
            validNOx = ox;
            validNOy = oy;
            if (hole == 1) validNOx += mid;
            else if (hole == 2) validNOy += mid;
            else if (hole == 3) {
                validNOx += mid;
                validNOy += mid;
            }
        }
    }
    
    if (validHole == -1) return false;
    
    // Đệ quy với quadrant tìm được
    return solveGreedy(k - 1, validNOx, validNOy, validNewCnt, res);
}
void precompute() {
    G.resize(k+1);
    G[1][0] = {0, 0, 0,1};
    G[1][1] = {0, 0, 1,0};
    G[1][2] = {0, 1, 0,0};
    G[1][3] = {1, 0, 0,0};


    FOR(i,2,k+1){
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
// sinh cnt hợp lệ đệ quy
array<ll,4> genCnt(int k) {
    if(k==1){
        array<ll,4> base = {0,0,0,1};
        for(int i=3;i>0;i--){
          int j = rnd.next(0,i); // dùng random_t
          swap(base[i], base[j]);
      }
        return base;
    }
    int midHole = rnd.next(0,3); // quadrant chứa hole
    array<ll,4> cnt = {0,0,0,0};
    cnt[trominoHoleMap[midHole]]++; // miếng trung tâm
    for(int child=0; child<4; child++){
        int childHole = (child==midHole)? rnd.next(0,3) : trominoHoleMap[child];
        array<ll,4> sub = genCnt(k-1);
        for(int q=0;q<4;q++) cnt[q]+=sub[q];
    }
    return cnt;
}
void solve() {
    // array<ll,4> cnt;
    // cin >> k >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3];
    
    precompute();
    const int TESTCOUNT = 100;
    REP(i, TESTCOUNT){
        // Sinh k và cnt hợp lệ
        k = rnd.wnext(1, 10, 2);
        array<ll,4> trominoCnt = genCnt(k);

        // Tìm hole từ cnt
        pair<ll,ll> hole;
        solveGreedy(k, 0, 0, trominoCnt, hole);

        if(hole == make_pair(-1LL,-1LL)){
            cout << "TEST #" << i+1 << " FAIL: no hole found!\n";
            cout << "k=" << k << ", trominoCnt: ";
            for(auto v:trominoCnt) cout << v << " ";
            cout << "\n";
            break;
        }

        // Tính lại cnt từ hole
        array<ll,4> computedCnt = countTromnios(k, hole.second, hole.first);

        cout << "TEST #" << i+1 << ", k=" << k << "\n";
        cout << "Expected cnt: ";
        for(auto v:trominoCnt) cout << v << " ";
        cout << "\nComputed cnt: ";
        for(auto v:computedCnt) cout << v << " ";
        cout << "\nHole: (" << hole.first << "," << hole.second << ")\n";

        if(computedCnt != trominoCnt){
            cout << "==> FAIL\n";
            break;
        } else {
            cout << "==> CORRECT\n";
        }
        cout << "------------------------\n";
    }

    return;
    
    // ll gridSize = 1LL << k;
    // ll totalCells = gridSize * gridSize;
    // ll expectedTrominos = (totalCells - 1) / 3;
    // ll actualTotal = cnt[0] + cnt[1] + cnt[2] + cnt[3];
    
    // if (actualTotal != expectedTrominos) {
    //     cout << -1 << " " << -1 << endl;
    //     return;
    // }
    
    // pair<ll,ll> result;
    // if (solveGreedy(k, 0, 0, cnt, result)) {
    //     cout << result.se << " " << result.fi << endl;
    // } else {
    //     cout << -1 << " " << -1 << endl;
    // }
}

// ========== Main ==========
int main(int argc, char *argv[]) {
  #ifdef ON_PC
      registerGen(argc, argv, 1);
      freopen("../../../Share/input.txt","r",stdin);
      freopen("../../../Share/output.txt","w",stdout);
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
