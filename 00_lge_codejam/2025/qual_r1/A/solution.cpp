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
using i64 = long long;
using pii = pair<int,int>;
using pll = pair<i64,i64>;
template<typename T> using vt = vector<T>;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((i64)(x).size())
#define nl '\n'

// Loop macros
#define FOR(i,a,b) for(i64 i=(a); i<(b); ++i)
#define REP(i,n) FOR(i,0,n)
#define PER(i,n) for(i64 i=(n)-1; i>=0; --i)

// ========== Helpers (optional) ==========
template<class T> inline bool chmin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<class T> inline bool chmax(T& a,const T& b){if(b>a){a=b;return true;}return false;}

double dx[] = {-1,1,-1,1};
double dy[] = {1, 1, -1, -1};

struct Point{
  double x, y;
};
struct Triangle{
  Point a, b, c;
};
const double EPS = 1e-9;

void intersectX(Point A, Point B, Point C, Point D, vt<double>& res, bool getY = false){
  //toa do giao nhau giua AB va CD
  double a1 = B.y - A.y;
  double b1 = A.x - B.x;
  double c1 = a1 * A.x + b1 * A.y;

  double a2 = D.y - C.y;
  double b2 = C.x - D.x;
  double c2 = a2 * C.x + b2 * C.y;

  double det = a1 * b2 - a2 * b1;
  if (fabs(det) < EPS) return; //song song

  double x = (b2 * c1 - b1 * c2) / det;
  double y = (a1 * c2 - a2 * c1) / det;

  //kiem tra xem diem giao co nam tren doan thang AB va CD khong
  auto between = [&](double l, double r, double v) {
      return v >= min(l, r) - EPS && v <= max(l, r) + EPS;
  };

  if (between(A.x, B.x, x) && between(A.y, B.y, y) &&
      between(C.x, D.x, x) && between(C.y, D.y, y)) {
      if (getY) res.pb(y);
      else      res.pb(x);
  }
}

//tim toa do x cua cac diem giao nhau giua 2 tam giac va toa do X cua cac dinh tam giac
void getX(Triangle T1, Triangle T2, vt<double> &x_pos){
  intersectX(T1.a, T1.b, T2.b, T2.c, x_pos);
  intersectX(T1.a, T1.b, T2.a, T2.c, x_pos);
  intersectX(T1.b, T1.c, T2.b, T2.c, x_pos);
  intersectX(T1.b, T1.c, T2.a, T2.b, x_pos);
  intersectX(T1.a, T1.c, T2.b, T2.c, x_pos);
}

// ========== Solve function ==========
int n;
vt<Triangle> TRI;
void solve(){
    cin >> n;
    TRI.resize(n);
    int o;
    double d, x, y;
    FOR(i,0,n){
        cin >> o >> d >> x >> y;
        TRI[i] = {
          {x, y},
          {x + dx[o-1]*d, y},
          {x, y + dy[o-1]*d},
        };
    }
    // dbg(TRI[0].a.x, TRI[0].a.y, TRI[0].b.x, TRI[0].b.y, TRI[0].c.x, TRI[0].c.y);

    vt<double> x_pos; //tap hop cac toa do x can duyet
    FOR(i, 0, n){
      x_pos.pb(TRI[i].a.x);
      x_pos.pb(TRI[i].b.x);
      FOR(j, i+1, n){
        getX(TRI[i], TRI[j], x_pos);
      }
    }

    sort(all(x_pos));
    x_pos.erase(unique(all(x_pos)), x_pos.end());
    dbg(x_pos);
    double ans = 0.0;
    FOR(i, 0, sz(x_pos)-1){
      double xm = (x_pos[i] + x_pos[i+1]) / 2.0; //toa do x giua 2 diem lien tiep
      vt<vt<double>> ys; //tap hop cac doan y tai xm
      FOR(j, 0, n){
        //kiem tra xem xm co nam trong pham vi cua tam giac j khong
        double x1 = TRI[j].a.x;
        double x2 = TRI[j].b.x;
        double x3 = TRI[j].c.x;
        if(xm < min({x1, x2, x3}) - EPS || xm > max({x1, x2, x3}) + EPS){
          continue;
        }
        //tinh toa do y tai xm
        vt<double> ys_tam;
        intersectX(TRI[j].a, TRI[j].b, {xm, -1e3}, {xm, 1e3}, ys_tam, true);
        intersectX(TRI[j].b, TRI[j].c, {xm, -1e3}, {xm, 1e3}, ys_tam, true);
        sort(all(ys_tam));
        ys.pb({ys_tam[0], ys_tam[1]});
      }
      //tinh toan do dai phan chong nhau tren truc y
      sort(all(ys));
      double cur_y = -1e9;;
      double total_y = 0.0;
      for(auto seg : ys){
        if(seg[0] > cur_y + EPS){
          total_y += seg[1] - seg[0];
          cur_y = seg[1];
        } else if(seg[1] > cur_y + EPS){
          total_y += seg[1] - cur_y;
          cur_y = seg[1];
        }
      }

      ans += total_y * (x_pos[i+1] - x_pos[i]);
    }
    cout << fixed << setprecision(2) << ans << nl;

}

// ========== Main ==========
int main() {
    #ifdef ON_PC
      freopen("../../../Share/input.txt","r",stdin);
      freopen("../../../Share/output.txt","w",stdout);
      clock_t start = clock();
    #endif

    int T;
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
