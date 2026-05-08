#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ============================================================
// BÀI: Đi từ (1,1) đến (R,C) chỉ sang phải/xuống
//      N ô kẹo (N<=100), R,C<=10^6
//      Đếm số đường nhặt nhiều kẹo nhất, mod P=1000003
// IDEA: DP trên N+2 điểm {S, kẹo1..N, E} thay vì R*C ô
//       Mỗi cạnh u->v cần biết số đường từ u đến v
//       mà KHÔNG chạm kẹo nào ở giữa (dùng bao hàm-loại trừ)
// ============================================================

const ll P = 1000003;

// ---- Precompute factorial mod P để tính C(n,k) mod P -------
ll fact[1000003], inv_fact[1000003];

ll pw(ll a, ll b) { // a^b mod P
    ll r = 1; a %= P;
    for (; b; b >>= 1, a = a*a%P) if (b&1) r = r*a%P;
    return r;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < P; i++) fact[i] = fact[i-1] * i % P;
    inv_fact[P-1] = pw(fact[P-1], P-2);
    for (int i = P-2; i >= 0; i--) inv_fact[i] = inv_fact[i+1] * (i+1) % P;
}

ll C(ll n, ll k) { // C(n,k) mod P, yêu cầu 0 <= n,k < P
    if (k < 0 || k > n) return 0;
    return fact[n] % P * inv_fact[k] % P * inv_fact[n-k] % P;
}

ll lucas(ll n, ll k) { // C(n,k) mod P khi n có thể >= P
    if (k == 0) return 1;
    if (k > n)  return 0;
    return C(n%P, k%P) * lucas(n/P, k/P) % P;
}

// ---- Số đường đơn điệu từ (r1,c1) đến (r2,c2) ------------
// = C(dr+dc, dr), bằng 0 nếu không reachable
ll ways(ll r1, ll c1, ll r2, ll c2) {
    ll dr = r2-r1, dc = c2-c1;
    if (dr < 0 || dc < 0) return 0;
    return lucas(dr+dc, dr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();

    int T; cin >> T;
    while (T--) {
        ll R, C, N; cin >> R >> C >> N;

        // pts[0]=S, pts[1..N]=kẹo, pts[N+1]=E
        // isCandy[i]=true nếu i là kẹo
        vector<pair<ll,ll>> pts(N+2);
        vector<bool> isCandy(N+2, false);
        pts[0]   = {1, 1};
        pts[N+1] = {R, C};
        for (int i = 1; i <= N; i++) {
            cin >> pts[i].first >> pts[i].second;
            isCandy[i] = true;
        }

        // Sort theo topo order (x tăng, y tăng) để DP đúng
        // Ghi nhớ: sau sort cần tìm lại index của S và E
        sort(pts.begin(), pts.end());
        int idxS = -1, idxE = -1;
        for (int i = 0; i <= N+1; i++) {
            if (pts[i] == make_pair(1LL,1LL)) idxS = i;
            if (pts[i] == make_pair(R, C))    idxE = i;
        }
        // isCandy cũng cần reorder theo sort
        // Đơn giản hơn: dùng một vt chứa {x,y,candy}
        // Ở đây rebuild isCandy từ đầu dựa trên pts
        // (S và E không phải kẹo, còn lại là kẹo)
        for (int i = 0; i <= N+1; i++)
            isCandy[i] = (i != idxS && i != idxE);

        int M = N+2;
        auto reach = [&](int u, int v) { // u có thể đi tới v?
            return pts[v].first  >= pts[u].first &&
                   pts[v].second >= pts[u].second;
        };

        // --------------------------------------------------------
        // F[u][w] = số đường từ u đến kẹo w
        //           mà w là kẹo ĐẦU TIÊN sau u (không chạm kẹo khác)
        //
        // F[u][w] = ways(u,w) - sum_{z kẹo, u<z<w} F[u][z] * ways(z,w)
        //
        // Giải thích: lấy tổng tất cả đường u->w (=ways(u,w)),
        // trừ đi những đường đã chạm kẹo z nào đó trước w.
        // --------------------------------------------------------
        vector<vector<ll>> F(M, vector<ll>(M, 0));
        for (int u = 0; u < M; u++) {
            for (int w = u+1; w < M; w++) {
                if (!isCandy[w] || !reach(u,w)) continue;
                F[u][w] = ways(pts[u].first, pts[u].second,
                               pts[w].first, pts[w].second);
                for (int z = u+1; z < w; z++) {
                    if (!isCandy[z] || !reach(u,z) || !reach(z,w)) continue;
                    F[u][w] = (F[u][w] - F[u][z] * ways(pts[z].first, pts[z].second,
                                                         pts[w].first, pts[w].second) % P + P) % P;
                }
            }
        }

        // --------------------------------------------------------
        // trans[u][v] = số cách "chuyển cạnh" từ u sang v trong DAG
        //
        // - Nếu v là kẹo:  trans[u][v] = F[u][v]
        // - Nếu v = E:     trans[u][E] = ways(u,E) không chạm kẹo
        //                 = ways(u,E) - sum_{z kẹo} F[u][z] * ways(z,E)
        // --------------------------------------------------------
        vector<vector<ll>> trans(M, vector<ll>(M, 0));
        for (int u = 0; u < M; u++) {
            // -> kẹo
            for (int v = u+1; v < M; v++) {
                if (isCandy[v]) trans[u][v] = F[u][v];
            }
            // -> E
            if (!reach(u, idxE)) continue;
            trans[u][idxE] = ways(pts[u].first, pts[u].second, R, C);
            for (int z = u+1; z < idxE; z++) {
                if (!isCandy[z] || !reach(u,z) || !reach(z,idxE)) continue;
                trans[u][idxE] = (trans[u][idxE]
                    - F[u][z] * ways(pts[z].first, pts[z].second, R, C) % P + P) % P;
            }
        }

        // --------------------------------------------------------
        // DP: best[v] = số kẹo tối đa tới v
        //     ways_dp[v] = số cách đạt best[v], mod P
        //
        // Relax u -> v:
        //   cand = best[u] + (1 nếu v kẹo, 0 nếu v=E)
        //   add  = ways_dp[u] * trans[u][v]
        // --------------------------------------------------------
        vector<ll> best(M, -1), ways_dp(M, 0);
        best[idxS]   = 0;
        ways_dp[idxS] = 1;

        for (int u = 0; u < M; u++) {
            if (best[u] < 0) continue;
            for (int v = u+1; v < M; v++) {
                if (trans[u][v] == 0) continue;
                ll cand = best[u] + (isCandy[v] ? 1 : 0);
                ll add  = ways_dp[u] * trans[u][v] % P;
                if (cand > best[v]) {
                    best[v]   = cand;
                    ways_dp[v] = add;
                } else if (cand == best[v]) {
                    ways_dp[v] = (ways_dp[v] + add) % P;
                }
            }
        }

        cout << ways_dp[idxE] << "\n";
    }
}
