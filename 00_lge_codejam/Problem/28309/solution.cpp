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

// ========== Helpers ==========
template<class T> inline bool chmin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<class T> inline bool chmax(T& a,const T& b){if(b>a){a=b;return true;}return false;}

//======= SIGNAL HANDLER FOR DEBUGGING ========
void signalHandler(int signum) {
    cerr << "\nCaught signal: " << signum << endl;
    if (signum == SIGSEGV) cerr << "Segmentation fault detected!\n";
    else if (signum == SIGABRT) cerr << "Aborted!\n";
    exit(signum);
}

// ==========================================================
// TỔNG QUAN BÀI TOÁN
// ----------------------------------------------------------
// Lưới R x C, đi từ (1,1) đến (R,C) chỉ sang phải/xuống.
// Có N ô kẹo (N <= 100). Tìm số đường đi nhặt nhiều kẹo
// nhất, mod P = 1000003.
//
// KEY INSIGHT: R,C <= 10^6 nên DP từng ô O(R*C) quá chậm.
// Chỉ có N+2 điểm "quan trọng": S, N kẹo, E.
// => DP trên N+2 điểm này, mỗi cạnh cần biết số cách đi
//    "không chạm kẹo trung gian" giữa 2 điểm.
// ==========================================================

const ll P = 1000003; // modulo đặc biệt của bài, là số nguyên tố

// ----------------------------------------------------------
// LUCAS THEOREM: tính C(n,k) mod P khi n có thể rất lớn
// ----------------------------------------------------------
// Precompute fact[0..P-1] và invFact[0..P-1]
// Dùng Lucas: C(n,k) mod p = C(n%p, k%p) * C(n/p, k/p) mod p
// ----------------------------------------------------------
ll fact[1000003], invFact[1000003];

ll power(ll a, ll b, ll mod) {
    // Tính a^b mod p bằng fast exponentiation
    ll res = 1; a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void precompute() {
    // Precompute factorial và inverse factorial trong [0, P)
    fact[0] = 1;
    FOR(i, 1, P) fact[i] = fact[i-1] * i % P;
    invFact[P-1] = power(fact[P-1], P-2, P); // Fermat's little theorem
    PER(i, P-1) invFact[i] = invFact[i+1] * (i+1) % P;
}

ll comb(ll n, ll k) {
    // C(n, k) mod P với 0 <= n, k < P
    if (k < 0 || k > n) return 0;
    return fact[n] % P * invFact[k] % P * invFact[n-k] % P;
}

ll lucas(ll n, ll k) {
    // Lucas theorem: C(n,k) mod P khi n có thể >= P
    // C(n,k) = C(n%P, k%P) * C(n/P, k/P) mod P
    if (k == 0) return 1;
    if (k > n) return 0;
    return comb(n % P, k % P) * lucas(n / P, k / P) % P;
}

// ----------------------------------------------------------
// G(u, v): số đường đơn điệu từ u đến v (không quan tâm kẹo)
// = C(dx+dy, dx) với dx = x_v - x_u, dy = y_v - y_u
// = 0 nếu không reachable (dx < 0 hoặc dy < 0)
// ----------------------------------------------------------
ll G(ll x1, ll y1, ll x2, ll y2) {
    ll dx = x2 - x1, dy = y2 - y1;
    if (dx < 0 || dy < 0) return 0;
    return lucas(dx + dy, dx);
}

// ----------------------------------------------------------
// SOLVE FUNCTION
// ----------------------------------------------------------
void solve() {
    ll R, C, N;
    cin >> R >> C >> N;

    // Danh sách điểm: index 0 = S, 1..N = kẹo, N+1 = E
    vt<pll> pts(N + 2);
    pts[0] = {1, 1};       // S
    pts[N+1] = {R, C};     // E
    FOR(i, 1, N+1) cin >> pts[i].fi >> pts[i].se;

    // Sắp xếp theo topo order (x tăng, y tăng)
    // Chú ý: giữ S ở đầu và E ở cuối sau khi sort
    // Cách đơn giản: sort tất cả N+2 điểm, sau đó DP theo
    // thứ tự đã sort
    sort(pts.begin(), pts.end());
    // Tìm lại index của S và E sau khi sort
    int idxS = -1, idxE = -1;
    REP(i, N+2) {
        if (pts[i] == mp(1LL, 1LL)) idxS = i;
        if (pts[i] == mp(R, C))     idxE = i;
    }

    int M = N + 2; // tổng số điểm

    // isCandy[i] = true nếu điểm i là kẹo (không phải S hay E)
    vt<bool> isCandy(M, true);
    isCandy[idxS] = false;
    isCandy[idxE] = false;

    // ----------------------------------------------------------
    // Bước 1: Tính F[u][w] cho từng cặp (u, w)
    // F[u][w] = số đường từ u đến w mà w là kẹo đầu tiên sau u
    //
    // Công thức (bao hàm - loại trừ):
    // F[u][w] = G(u,w) - sum_{z: u <= z < w, z là kẹo} F[u][z] * G(z,w)
    //
    // Duyệt u từ 0..M-1, với mỗi u duyệt w theo thứ tự topo
    // (đã sort rồi nên duyệt index tăng dần là đúng)
    // ----------------------------------------------------------
    // F[u][v] = số cách đi từ u đến v, v là kẹo đầu tiên
    vt<vt<ll>> F(M, vt<ll>(M, 0));

    REP(u, M) {
        // Duyệt w theo thứ tự topo (index tăng, và reachable từ u)
        FOR(w, u+1, M) {
            if (!isCandy[w]) continue; // chỉ tính F đến kẹo
            if (pts[w].fi < pts[u].fi || pts[w].se < pts[u].se) continue; // không reachable

            // Bắt đầu từ G(u, w): tất cả đường từ u đến w
            F[u][w] = G(pts[u].fi, pts[u].se, pts[w].fi, pts[w].se);

            // Trừ đi các đường đi qua kẹo z nằm giữa u và w
            FOR(z, u+1, w) {
                if (!isCandy[z]) continue;
                if (pts[z].fi < pts[u].fi || pts[z].se < pts[u].se) continue; // z không reachable từ u
                if (pts[w].fi < pts[z].fi || pts[w].se < pts[z].se) continue; // w không reachable từ z
                // F[u][z] * G(z, w): đường qua kẹo z đầu tiên rồi mới đến w
                F[u][w] = (F[u][w] - F[u][z] % P * G(pts[z].fi, pts[z].se, pts[w].fi, pts[w].se) % P + P) % P;
            }
        }
    }

    // ----------------------------------------------------------
    // Bước 2: Tính T[u][v]: số cách chuyển cạnh trong DP
    // - Nếu v là kẹo: T[u][v] = F[u][v]
    // - Nếu v = E:    T[u][E] = số đường u->E không chạm thêm kẹo
    //                         = G(u,E) - sum_{z kẹo, u<=z<=E} F[u][z] * G(z,E)
    // ----------------------------------------------------------
    vt<vt<ll>> T(M, vt<ll>(M, 0));

    REP(u, M) {
        // Transition đến các kẹo w
        FOR(w, u+1, M) {
            if (!isCandy[w]) continue;
            T[u][w] = F[u][w]; // bằng F[u][w] vì w là kẹo
        }

        // Transition đến E (nếu E reachable từ u)
        if (pts[idxE].fi >= pts[u].fi && pts[idxE].se >= pts[u].se) {
            T[u][idxE] = G(pts[u].fi, pts[u].se, R, C);
            // Trừ đi các đường đi qua kẹo z trước E
            FOR(z, u+1, idxE) {
                if (!isCandy[z]) continue;
                if (pts[z].fi < pts[u].fi || pts[z].se < pts[u].se) continue;
                if (R < pts[z].fi || C < pts[z].se) continue;
                T[u][idxE] = (T[u][idxE] - F[u][z] % P * G(pts[z].fi, pts[z].se, R, C) % P + P) % P;
            }
        }
    }

    // ----------------------------------------------------------
    // Bước 3: DP tối ưu số kẹo + đếm số cách
    //
    // best[v] = số kẹo tối đa khi tới v
    // ways[v] = số cách đạt best[v], mod P
    //
    // Relax cạnh u -> v:
    //   cand = best[u] + (1 nếu v là kẹo, 0 nếu v là E)
    //   add  = ways[u] * T[u][v]
    //   nếu cand > best[v]: gán mới
    //   nếu cand == best[v]: cộng dồn ways
    // ----------------------------------------------------------
    vt<ll> best(M, -1), ways(M, 0);
    best[idxS] = 0;
    ways[idxS] = 1;

    // Duyệt theo thứ tự topo (đã sort)
    REP(u, M) {
        if (best[u] < 0) continue; // chưa reachable

        FOR(v, u+1, M) {
            if (T[u][v] == 0) continue; // không có đường

            ll cand = best[u] + (isCandy[v] ? 1 : 0);
            ll add  = ways[u] * T[u][v] % P;

            if (cand > best[v]) {
                best[v] = cand;
                ways[v] = add;
            } else if (cand == best[v]) {
                ways[v] = (ways[v] + add) % P;
            }
        }
    }

    cout << ways[idxE] << nl;
}

// ========== Main ==========
int main() {
    signal(SIGSEGV, signalHandler);
    signal(SIGABRT, signalHandler);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute(); // precompute factorial mod P một lần trước tất cả test

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

    int TC = 1;
    cin >> TC;
    while(TC--){
        solve();
    }

    #ifdef ON_PC
      clock_t end = clock();
      double ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
      cerr << "Finished in " << ms << " ms" << nl;
    #endif
    return 0;
}
