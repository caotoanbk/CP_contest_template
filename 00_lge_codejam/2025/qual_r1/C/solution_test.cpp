#include <bits/stdc++.h>
using namespace std;

// ==================== Debug ====================
#ifdef ON_PC
  #include "lib/debug2.h"
#else
  #define dbg(...)
  #define dbgArr(...)
#endif

// ==================== FastIO initializer ====================
struct FastIO {
    FastIO() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    }
} fastio; // khởi tạo trước main

// ==================== Aliases & Macros ====================
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

struct TrominoCount  {
    ll a, b, c, d;
    inline void set0() { a = b = c = d = 0; }
    inline ll sum() const { return a + b + c + d; }
};

vector<array<TrominoCount,4>> G;

void precompute() {
    G.resize(31);

    G[1][0] = {0, 0, 0, 1};
    G[1][1] = {0, 0, 1, 0};
    G[1][2] = {0, 1, 0, 0};
    G[1][3] = {1, 0, 0, 0};

    FOR(i,2,31) {
        REP(hole,4) {
            TrominoCount cnt = {0,0,0,0};
            int centerIdx = 3-hole;
            if (centerIdx == 0) cnt.a++;
            else if (centerIdx == 1) cnt.b++;
            else if (centerIdx == 2) cnt.c++;
            else cnt.d++;

            REP(child,4) {
                int childHole = (child == hole) ? child : 3-child;
                const TrominoCount &ref = G[i-1][childHole];
                cnt.a += ref.a; cnt.b += ref.b; cnt.c += ref.c; cnt.d += ref.d;
            }
            G[i][hole] = cnt;
        }
    }
}

bool solveGreedy(int k, ll ox, ll oy, TrominoCount cnt, pair<ll,ll>& res) {
    TrominoCount cur, remainCnt, bestNewCnt;
    ll mid;
    int bestHole;
    ll newOx=0, newOy=0;

    while (true) {
        if (k == 1) {
            // base case: 2x2
            int finalHole = -1;
            if (cnt.a==1 && cnt.b==0 && cnt.c==0 && cnt.d==0) finalHole = 3;
            else if (cnt.b==1 && cnt.a==0 && cnt.c==0 && cnt.d==0) finalHole = 2;
            else if (cnt.c==1 && cnt.a==0 && cnt.b==0 && cnt.d==0) finalHole = 1;
            else if (cnt.d==1 && cnt.a==0 && cnt.b==0 && cnt.c==0) finalHole = 0;
            else return false;

            if(finalHole == 0){
                res = {ox, oy};
            }else if(finalHole == 1){
                res = {ox+1, oy};
            }else if(finalHole == 2){
                res = {ox, oy+1};
            }else{
                res = {ox+1, oy+1};
            }
            return true;
        }

        mid = 1LL << (k - 1);
        bestHole = -1;
        long long bestDist = LLONG_MAX;

        REP(hole,4) {
            cur.set0();
            int centerIdx = 3-hole;
            if (centerIdx == 0) cur.a++;
            else if (centerIdx == 1) cur.b++;
            else if (centerIdx == 2) cur.c++;
            else cur.d++;

            REP(child,4) {
                if (child == hole) continue;
                const TrominoCount &ref = G[k-1][3-child];
                cur.a += ref.a; cur.b += ref.b; cur.c += ref.c; cur.d += ref.d;
            }

            if (cur.a > cnt.a || cur.b > cnt.b || cur.c > cnt.c || cur.d > cnt.d) continue;

            remainCnt.a = cnt.a - cur.a;
            remainCnt.b = cnt.b - cur.b;
            remainCnt.c = cnt.c - cur.c;
            remainCnt.d = cnt.d - cur.d;

            ll totalNew = remainCnt.sum();
            ll expectedForSubtree = ((1LL << (2 * (k - 1))) - 1) / 3;
            if (totalNew != expectedForSubtree) continue;

            const TrominoCount &pattern = G[k-1][hole];
            ll dist = 0;
            ll x0 = remainCnt.a - pattern.a; dist += llabs(x0);
            ll x1 = remainCnt.b - pattern.b; dist += llabs(x1);
            ll x2 = remainCnt.c - pattern.c; dist += llabs(x2);
            ll x3 = remainCnt.d - pattern.d; dist += llabs(x3);

            if (bestHole == -1 || dist < bestDist) {
                bestHole = hole;
                bestDist = dist;
                bestNewCnt = remainCnt;
                newOx = ox; newOy = oy;
                if (hole == 1) newOx += mid;
                else if (hole == 2) newOy += mid;
                else if (hole == 3) { newOx += mid; newOy += mid; }
            }
        }

        if (bestHole == -1) return false;

        k--;
        ox = newOx;
        oy = newOy;
        cnt = bestNewCnt;
    }
    return false;
}

// ==================== Solve ====================
void solve() {
    int k;
    cin>>k;

    TrominoCount cnt;
    cin >> cnt.a >> cnt.b >> cnt.c >> cnt.d;

    // ll gridSize = 1LL << k;
    // ll totalCells = gridSize * gridSize;
    // ll expectedTrominos = (totalCells - 1) / 3;
    // ll actualTotal = cnt.sum();

    // if (actualTotal != expectedTrominos) {
    //     cout << "-1 -1" << nl;
    //     return;
    // }

    pair<ll,ll> result;
    if (solveGreedy(k, 0, 0, cnt, result))
        cout << result.second << " " << result.first << nl;
    else
        cout << "-1 -1" << nl;
}

// ==================== Main ====================
int main() {
#ifdef ON_PC
    freopen("../../../Share/input.txt","r",stdin);
    freopen("../../../Share/output.txt","w",stdout);
    clock_t start = clock();
#endif

    precompute();
    int T; cin>>T;
    while (T--) solve();

#ifdef ON_PC
    clock_t end = clock();
    double ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
    cerr << "Finished in " << ms << " ms\n";
#endif
    return 0;
}
