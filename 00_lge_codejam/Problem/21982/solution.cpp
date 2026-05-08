#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll,ll>;

// ==========DEFINE OTHER STRUCT/CLASS/VARIABLE ==========
int n, x;
long long hs, ha, hb, hc,
          my_ws, wa, wb, wc;

void solve(){
  cin >> n >> x;
  cin >> hs >> ha >> hb >> hc;
  cin >> my_ws >> wa >> wb >> wc;

  deque<pll> dq;
  ll best = -1;
  ll h_cur = 0, w_cur = 0;

  for (int j = 0; j < n; ++j) {
    if(j == 0){
      h_cur = hs % hc + 1;
      w_cur = my_ws % wc + 1;
    }else{
      h_cur = h_cur + 1 + (h_cur * ha + hb) % hc;
      w_cur = (w_cur * wa + wb) % wc + 1;
    }

    ll v_cur = h_cur * w_cur;

    while(!dq.empty() && h_cur - dq.front().first > x) dq.pop_front();
    if(!dq.empty()){
      best = max(best, dq.front().second + v_cur);
    }
    while(!dq.empty() && dq.back().second <= v_cur) dq.pop_back();
    dq.push_back({h_cur, v_cur});
  }

  cout << best << '\n';
}

int main() {
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

    int T;
    cin >> T;
    while (T--) {
      solve();
    }

    #ifdef ON_PC
      clock_t end = clock();
      double ms = double(end - start) / CLOCKS_PER_SEC * 1000.0;
      cerr << "Finished in " << ms << " ms\n";
    #endif
    return 0;
}
