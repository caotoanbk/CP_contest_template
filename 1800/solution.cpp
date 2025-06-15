#include <bits/stdc++.h>
using namespace std;
#ifdef ON_PC
    #include "../shared/lib/debug2.h"
#else
    #define dbg(...) 
    #define dbgArr(...)
#endif

#define int int64_t
typedef pair<int,int> pii;
#define ll long long
#define ld long double
#define ar array
#define vt vector
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define endl '\n'

#define F_OR(i, a, b, s) for (int i=(a); (s)>0?i<(b):i>(b); i+=(s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)
#define EACH(x, a) for (auto& x: a)

const int INF = 1e9 + 7;

int n,p,k;
vt<vt<pii>> adj;

vector<int> dijkstra(int n, int start, const vector<vector<pair<int, int>>> &adj) {
    vector<int> dist(n, INF);
    dist[start] = 0;

    // Min-heap: (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

bool can_reach(int n, int val, int start, const vector<vector<pair<int, int>>> &adj) {
    vector<int> dist(n, INF);
    dist[start] = 0;

    // Min-heap: (distance, node)
   deque<int> dq;
    dq.pb(start);

    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            int cost = w > val ? 1 : 0; // Count only edges with weight >= val
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                if (cost == 0) {
                    dq.push_front(v); // If the edge weight is less than or equal to val, prioritize it
                } else {
                    dq.push_back(v); // Otherwise, add it to the back
                }
            }
        }
    }

    return dist[n-1] <= k; // Check if we can reach node n-1 within k weight
}

void solve(){
    cin>>n>>p>>k;
    adj.resize(n);

    FOR(i, p){
        int u,v,w;
        cin >> u >> v>>w;
        u--; v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w}); // Assuming undirected graph
    }


    int lo = 0, hi = 1'000'000;
    int ans = -1;
    while( lo <= hi){
        int mid = (lo+hi)/2;
        if(can_reach(n, mid, 0, adj)){
            ans = mid;
            hi = mid - 1; // Try to find a smaller maximum weight
        } else {
            lo = mid + 1; // Increase the maximum weight
        }
    }

   cout << ans <<endl;



}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    #ifdef ON_PC
        freopen("../shared/input.txt", "r", stdin);
        freopen("../shared/output.txt", "w", stdout);
        //freopen("../shared/error.txt", "w", stderr);
        clock_t start, end;
        start = clock();
    #endif // ON_PC

    int t=1; 
    // cin >> t;
    while(t--){
        solve();
    }


    #ifdef ON_PC
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cerr << "Finished in " << time_taken*1000<< " ms " << endl;
    #endif // ON_PC   

    return 0;
}