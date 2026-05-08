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

struct Quad4 {
    ll a, b, c, d;
    inline void set0() { a = b = c = d = 0; }
    inline ll sum() const { return a + b + c + d; }
};
// ========== Solve function ==========
vector<array<Quad4,4>> G;
const array<ll,4> trominoHoleMap = {3, 2, 1, 0 };
int k;

// Thuật toán greedy O(k) - chọn quadrant duy nhất có thể
bool solveGreedy(int k, ll ox, ll oy, Quad4 cnt, pair<ll,ll>& res) {
    // Local buffers
    array<ll,4> curCnt, newCnt, validNewCnt;
    ll mid;
    int validHole;
    ll validNOx = 0, validNOy = 0;

    while (true) {
        if (k == 1) {
            int finalHole = -1;
            for (int t = 0; t < 4; t++) {
                if (cnt[t] == 1) {
                    if (finalHole != -1) return false;
                    finalHole = trominoHoleMap[t];
                } else if (cnt[t] != 0) return false;
            }
            if (finalHole == -1) return false;
            if (finalHole == 0) res = {ox, oy};
            else if (finalHole == 1) res = {ox + 1, oy};
            else if (finalHole == 2) res = {ox, oy + 1};
            else res = {ox + 1, oy + 1};
            return true;
        }

        mid = 1LL << (k - 1);
        validHole = -1;

        for (int hole = 0; hole < 4; hole++) {
            // compute curCnt
            curCnt = {0,0,0,0};
            curCnt[trominoHoleMap[hole]]++;
            for (int child = 0; child < 4; child++) {
                if (child == hole) continue;
                int childHole = trominoHoleMap[child];
                for (int q = 0; q < 4; q++)
                    curCnt[q] += G[k-1][childHole][q];
            }

            bool ok = true;
            for (int q = 0; q < 4; q++) {
                if (curCnt[q] > cnt[q]) { ok = false; break; }
                newCnt[q] = cnt[q] - curCnt[q];
            }
            if (!ok) continue;

            ll totalNew = 0;
            for (int q = 0; q < 4; q++) {
                if (newCnt[q] < 0) { ok = false; break; }
                totalNew += newCnt[q];
            }
            if (!ok) continue;

            ll expectedForSubtree = 0;
            if (k > 1) {
                ll subSize = 1LL << (2 * (k - 1));
                expectedForSubtree = (subSize - 1) / 3;
            }
            if (totalNew != expectedForSubtree) continue;

            // Quadrant này khả thi
            if (validHole != -1) {
                // Có nhiều hơn 1 quadrant khả thi - dùng heuristic tiebreak như ban đầu
                ll dist1 = 0, dist2 = 0;
                for (int q = 0; q < 4; q++) {
                    ll a = validNewCnt[q] - G[k-1][validHole][q];
                    ll b = newCnt[q] - G[k-1][hole][q];
                    dist1 += (a >= 0) ? a : -a;
                    dist2 += (b >= 0) ? b : -b;
                }

                if (dist2 < dist1) {
                    validHole = hole;
                    validNewCnt = newCnt;
                    validNOx = ox;
                    validNOy = oy;
                    if (hole == 1) validNOx += mid;
                    else if (hole == 2) validNOy += mid;
                    else if (hole == 3) { validNOx += mid; validNOy += mid; }
                }
            } else {
                validHole = hole;
                validNewCnt = newCnt;
                validNOx = ox;
                validNOy = oy;
                if (hole == 1) validNOx += mid;
                else if (hole == 2) validNOy += mid;
                else if (hole == 3) { validNOx += mid; validNOy += mid; }
            }
        }

        if (validHole == -1) return false;

        // descend into chosen quadrant
        k--;
        ox = validNOx;
        oy = validNOy;
        cnt = validNewCnt;
    }
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
    array<ll,4> cnt;
    cin >> k >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3];
    
    // precompute();
    
    ll gridSize = 1LL << k;
    ll totalCells = gridSize * gridSize;
    ll expectedTrominos = (totalCells - 1) / 3;
    ll actualTotal = cnt[0] + cnt[1] + cnt[2] + cnt[3];
    
    if (actualTotal != expectedTrominos) {
        cout << -1 << " " << -1 << endl;
        return;
    }
    
    pair<ll,ll> result;
    if (solveGreedy(k, 0, 0, cnt, result)) {
        cout << result.se << " " << result.fi << endl;
    } else {
        cout << -1 << " " << -1 << endl;
    }
}

// ========== Main ==========
int main() {
    #ifdef ON_PC
      freopen("../../../Share/input.txt","r",stdin);
      freopen("../../../Share/output.txt","w",stdout);
      clock_t start = clock();
    #endif

    int T = 1;
    cin >> T;
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
