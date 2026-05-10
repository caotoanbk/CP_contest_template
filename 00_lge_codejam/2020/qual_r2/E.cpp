#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vt vector
#define pb push_back

struct Dinic{
    // O(V^2 * E) worst case, O(sqrt(V)*E) for unit networks
    struct Edge{
        int to, rev;
        ll cap, flow;
    };
    vt<vt<Edge>> adj;
    vt<int> level;
    vt<int> ptr;
    int n;

    Dinic(int n){
        this->n = n;
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int u, int v, ll cap){
        adj[u].pb({v, (int)adj[v].size(), cap, 0});
        adj[v].pb({u, (int)adj[u].size() - 1, 0, 0});
    }

    bool bfs(int s, int t){
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &e : adj[u]){
                if(level[e.to] == -1 && e.flow < e.cap){
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int v, int t, ll pushed){
        if(pushed == 0 || v == t) return pushed;
        for(int& cid = ptr[v]; cid < (int)adj[v].size(); cid++){
            auto &e = adj[v][cid];
            int tr = e.to;
            if(level[v] + 1 != level[tr] || e.flow >= e.cap) continue;
            ll tr_push = dfs(tr, t, min(pushed, e.cap - e.flow));
            if(tr_push == 0) continue;
            e.flow += tr_push;
            adj[tr][e.rev].flow -= tr_push;
            return tr_push;
        }
        return 0;
    }

    ll max_flow(int s, int t){
        ll flow = 0;
        while(bfs(s,t)){
            fill(ptr.begin(), ptr.end(), 0);
            while(ll pushed = dfs(s,t,LLONG_MAX)){
                flow += pushed;
            }
        }
        return flow;
    }

    vt<int> get_s_group(){
        vt<int> s_group;
        for(int i=0; i< n; i++){
            if(level[i] != -1) s_group.pb(i);
        }
        return s_group;
    }

    bool is_in_s(int u){
        return level[u] != -1;
    }
};


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while(t--){
        int n,m;
        cin >> n >> m;
        ll base = 0;

        Dinic dinic(n+2);
        for(int i = 0 ; i < n ; i++){
            ll a,b;
            cin >> a >> b;
            if(a > b) dinic.add_edge(0, i+1, a-b);
            else if(a < b) dinic.add_edge(i+1, n+1, b-a);
            base += max(a,b);
        }
        for(int i = 0; i < m; i++){
            int k,s; cin >> k >> s;
            vt<int> nodes(k);
            for(int j = 0; j < k; j++){
              cin >> nodes[j];
            }
            for(int j=0; j<k; j++){
                for(int l=j+1; l<k; l++){
                    dinic.add_edge(nodes[j], nodes[l], s);
                    dinic.add_edge(nodes[l], nodes[j], s);
                }
            }
        }

        cout << base - dinic.max_flow(0, n+1) << "\n";
        vt<int> groupA;
        for(int u : dinic.get_s_group())
            if(u != 0 && u != n+1) groupA.pb(u);
        cout << groupA.size();
        for(int x : groupA) cout << " " << x;
        cout << "\n";
    }

    return 0;
}