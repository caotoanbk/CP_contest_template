#include <bits/stdc++.h>
using namespace std;

int LOGN;
int n, m;
vector<vector<int>> g;
vector<int> depth;
vector<int> tin, tout;
int timerv = 0;
vector<vector<int>> up;
vector<int> parent1;

void dfs_lca(int u, int p){
    tin[u] = ++timerv;
    up[u][0] = p;
    for (int k=1;k<LOGN;k++) up[u][k] = up[ up[u][k-1] ][k-1];
    for (int v: g[u]){
        if (v==p) continue;
        depth[v] = depth[u] + 1;
        parent1[v] = u;
        dfs_lca(v, u);
    }
    tout[u] = ++timerv;
}

bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v){
    if (is_ancestor(u,v)) return u;
    if (is_ancestor(v,u)) return v;
    for (int k=LOGN-1;k>=0;k--){
        int w = up[u][k];
        if (w && !is_ancestor(w, v)) u = w;
    }
    return up[u][0];
}

// We'll need subtree sizes on original tree for segments between virtual-tree nodes.
// We will compute sizes by doing one DFS and storing parent (parent1).
vector<int> subsize_all; // size of subtree in original rooted tree (root = 1)

int compute_subsizes(int root = 1){
    // iterative stack to avoid recursion depth
    vector<int> order;
    order.reserve(n);
    stack<pair<int,int>> st;
    st.push({root, 0});
    while(!st.empty()){
        auto [u,p] = st.top(); st.pop();
        order.push_back(u);
        for (int v: g[u]){
            if (v==p) continue;
            parent1[v] = u;
            depth[v] = depth[u] + 1;
            st.push({v,u});
        }
    }
    // process in reverse to compute subtree sizes
    for (int u : order) subsize_all[u] = 1;
    for (int i = (int)order.size()-1; i>=0; --i){
        int u = order[i];
        for (int v: g[u]){
            if (v == parent1[u]) continue;
            subsize_all[u] += subsize_all[v];
        }
    }
    return 0;
}

// Build virtual tree from vector<int> nodes (must be unique), returns adjacency list of virtual tree
vector<vector<int>> build_virtual_tree(vector<int>& nodes){
    sort(nodes.begin(), nodes.end(), [](int a, int b){ return tin[a] < tin[b]; });
    // add LCAs
    vector<int> st;
    vector<vector<int>> vt(n+1);
    st.push_back(nodes[0]);
    for (int i=1;i<(int)nodes.size();++i){
        int u = nodes[i];
        int w = lca(u, st.back());
        if (w == st.back()){
            st.push_back(u);
            continue;
        }
        while (st.size() >= 2 && depth[ st[st.size()-2] ] >= depth[w]){
            int v = st.back(); st.pop_back();
            int par = st.back();
            vt[par].push_back(v);
            vt[v].push_back(par);
        }
        if (st.back() != w){
            int v = st.back(); st.pop_back();
            // attach v to w
            vt[w].push_back(v);
            vt[v].push_back(w);
            st.push_back(w);
        }
        st.push_back(u);
    }
    while (st.size() >= 2){
        int v = st.back(); st.pop_back();
        int par = st.back();
        vt[par].push_back(v);
        vt[v].push_back(par);
    }
    return vt;
}

// Helper: count number of original-tree nodes that lie within the virtual-tree subtree
// We'll need to compute for an edge (a-b) in virtual tree, the number of original nodes in the side towards b (when parent is a)
// If we root virtual tree at some root r, and consider child v of u, then the nodes on that side that are "between u and v" are exactly:
// - all nodes in original subtree of v when considering original root at u? It's tricky.
// But we can get count of original nodes in the portion of original tree that belongs to subtree(v) when we consider u as parent, by:
// If v is descendant of u in original tree: then count = subsize_all[v]
// else: count = n - subsize_all[u]
// However in virtual tree nodes are LCAs and specials; so we can use tin/tout to test ancestor relations.
long long get_nodes_on_side(int u, int v){
    // return number of original nodes in the component that contains v when remove edge u-v
    if (is_ancestor(v, u)){
        // v is ancestor of u in original tree => removing edge u-v the side containing v is everything except subtree of child of v that leads to u
        // find child c of v that is ancestor of u
        int cur = u;
        for (int k = LOGN-1; k>=0; --k){
            int w = up[cur][k];
            if (w && depth[w] > depth[v]) cur = w;
        }
        // now cur is child of v towards u
        int c = cur;
        return n - subsize_all[c];
    } else {
        // v is not ancestor of u -> v is inside subtree of u or separate; if v is in subtree of u then simply its subtree size
        return subsize_all[v];
    }
}

int main(){
     #ifdef ON_PC
      FILE* f1 = freopen("d:\\C++\\CP\\Share\\input.txt","r",stdin);
      FILE* f2 = freopen("d:\\C++\\CP\\Share\\ans.txt","w",stdout);
      if (!f1 || !f2) {
        cerr << "Failed to open input/output file!\n";
        return 1;
     }
      clock_t start = clock();
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
     int t; cin >> t;
    cin >> n;
    cerr<< n;
    g.assign(n+1, {});
    for (int i=0;i<n-1;++i){
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> m;
    vector<int> specials(m);
    for (int i=0;i<m;++i) cin >> specials[i];

    // prepare LCA
    LOGN = 1;
    while ((1<<LOGN) <= n) LOGN++;
    up.assign(n+1, vector<int>(LOGN));
    depth.assign(n+1, 0);
    tin.assign(n+1,0);
    tout.assign(n+1,0);
    parent1.assign(n+1,0);
    timerv = 0;
    depth[1] = 0;
    dfs_lca(1, 0);

    // compute subtree sizes for original tree (rooted at 1)
    subsize_all.assign(n+1,0);
    parent1.assign(n+1, 0);
    depth.assign(n+1, 0);
    // iterative compute to avoid recursion limit
    // build parent1 and depth by BFS/stack
    {
        stack<pair<int,int>> st;
        st.push({1,0});
        vector<int> order;
        while(!st.empty()){
            auto [u,p] = st.top(); st.pop();
            order.push_back(u);
            parent1[u]=p;
            for (int v: g[u]){
                if (v==p) continue;
                depth[v]=depth[u]+1;
                st.push({v,u});
            }
        }
        for (int u: order) subsize_all[u]=1;
        for (int i=(int)order.size()-1;i>=0;--i){
            int u = order[i];
            for (int v: g[u]){
                if (v==parent1[u]) continue;
                subsize_all[u] += subsize_all[v];
            }
        }
    }

    // Build list of nodes for virtual tree: specials + their LCAs
    vector<int> nodes = specials;
    sort(nodes.begin(), nodes.end(), [](int a,int b){ return tin[a] < tin[b]; });
    for (int i=1;i<(int)nodes.size();++i){
        int w = lca(nodes[i-1], nodes[i]);
        nodes.push_back(w);
    }
    sort(nodes.begin(), nodes.end(), [](int a,int b){ return tin[a] < tin[b]; });
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    // Build virtual tree adjacency (using stack method)
    // We'll reuse build_virtual_tree but that used tin/tout from earlier dfs_lca; ensure those are set.
    // For correctness ensure tin/tout were computed: we called dfs_lca(1,0) earlier.
    vector<int> st;
    vector<vector<int>> vt(n+1);
    st.push_back(nodes[0]);
    for (int i=1;i<(int)nodes.size();++i){
        int u = nodes[i];
        int w = lca(u, st.back());
        if (w == st.back()){
            st.push_back(u);
            continue;
        }
        while (st.size() >= 2 && depth[ st[st.size()-2] ] >= depth[w]){
            int v = st.back(); st.pop_back();
            int par = st.back();
            vt[par].push_back(v);
            vt[v].push_back(par);
        }
        if (st.back() != w){
            int v = st.back(); st.pop_back();
            vt[w].push_back(v);
            vt[v].push_back(w);
            st.push_back(w);
        }
        st.push_back(u);
    }
    while (st.size() >= 2){
        int v = st.back(); st.pop_back();
        int par = st.back();
        vt[par].push_back(v);
        vt[v].push_back(par);
    }

    // For each virtual-tree node x we want the total number of original nodes in the "region" that belongs to that special when flowing out from that node, but easiest:
    // We'll compute for each virtual edge u-v (u parent, v child after rooting virtual tree), the number of original nodes that lie in v-side (when cut that edge).
    // Root virtual tree at nodes[0] (which is some lca/special).
    int root = nodes[0];
    // root vt parent using DFS
    vector<int> vpar(n+1, 0);
    vector<int> order;
    order.reserve(nodes.size());
    // BFS/stack on virtual tree but only nodes in 'nodes' set
    stack<int> sst;
    sst.push(root);
    vpar[root] = 0;
    while(!sst.empty()){
        int u = sst.top(); sst.pop();
        order.push_back(u);
        for (int v: vt[u]){
            if (v == vpar[u]) continue;
            vpar[v] = u;
            sst.push(v);
        }
    }
    // compute for each virtual edge (u->v where u is parent) the count of original nodes on v side:
    unordered_map<long long,int> edge_count; // key (min,max) => count
    auto key = [&](int a,int b)->long long{
        if (a>b) swap(a,b);
        return ((long long)a<<32) | (unsigned long long)b;
    };
    for (int idx = (int)order.size()-1; idx>=0; --idx){
        int u = order[idx];
        for (int v: vt[u]){
            if (v == vpar[u]) continue;
            // nodes u and v are virtual nodes (in original tree). We need number of original nodes on the v-side when cut u-v.
            long long k = key(u,v);
            int cnt = (int) get_nodes_on_side(u, v); // function we defined earlier uses is_ancestor+subsize_all
            edge_count[k] = cnt;
        }
    }

    // Now compute for each special s the total "region size" Rsize[s] = sum over edges from s to neighbor in vt of edge_count(s,neighbor) + (1 if s non-special? careful)
    // Actually Rsize[s] is sum of counts on all adjacent virtual edges plus 1 if s is non-special? But we want all original nodes that can be reached from s without passing other specials -> that's exactly 1 (s itself) + sum of counts on all vt edges s--child where path doesn't cross other specials.
    unordered_map<int,long long> Rsize;
    for (int u: nodes){
        long long tot = 1; // include u itself (original node u)
        for (int v: vt[u]){
            long long k = key(u,v);
            if (edge_count.count(k)) tot += edge_count[k];
        }
        Rsize[u] = tot;
    }

    // Now we compute Ai by summing contributions from specials s such that i is in the R_s (i is "reachable from s without passing other specials")
    // How to test whether i is in R_s? Path from s to i must not pass any other special.
    // That is equivalent to: along path s->i there are no other specials besides s (i may equal s).
    // We can test by using LCA and pref-special counts: build prefix count from root.
    vector<int> pref(n+1,0);
    // compute pref: number of specials on path root->v (inclusive)
    // do simple BFS/DFS from root (1)
    {
        vector<int> stk;
        stk.reserve(n);
        stack<pair<int,int>> st2;
        st2.push({1,0});
        pref[1] = (find(specials.begin(), specials.end(), 1) != specials.end()) ? 1 : 0; // but expensive to find; instead make boolean array special_map
    }
    vector<int> special_map(n+1,0);
    for (int s: specials) special_map[s]=1;
    // compute pref by simple dfs:
    {
        stack<pair<int,int>> st2;
        st2.push({1,0});
        pref[1] = special_map[1];
        while(!st2.empty()){
            auto [u,p] = st2.top(); st2.pop();
            for (int v: g[u]){
                if (v==p) continue;
                pref[v] = pref[u] + special_map[v];
                st2.push({v,u});
            }
        }
    }

    auto specials_on_path = [&](int a, int b)->int{
        int c = lca(a,b);
        int cnt = pref[a] + pref[b] - 2*pref[c] + special_map[c];
        return cnt;
    };

    // For each node i (1..n) compute Ai:
    vector<long long> A(n+1,0);
    // We'll iterate specials s (m up to n) and add contribution to i only if specials_on_path(s,i) == 1.
    // Contribution when i is in R_s:
    // If specials_on_path(s,i) != 1 => s doesn't contribute to Ai.
    // Else if s==i => contribute Rsize[s]
    // Else: find neighbor child of s on path s->i (the first step from s towards i). Then contribution = Rsize[s] - edge_count[key(s,child)].
    // To find that child: move one step from s towards i: if child is neighbor on original tree.
    auto step_from_to = [&](int s, int i)->int{
        // return neighbor of s that lies on path s->i
        if (s==i) return -1;
        // if s is ancestor of i (w.r.t. root 1), then child is the child of s that is ancestor of i
        if (is_ancestor(s,i)){
            int cur = i;
            for (int k=LOGN-1;k>=0;--k){
                int w = up[cur][k];
                if (w && depth[w] > depth[s]) cur = w;
            }
            return cur; // child of s on path to i
        } else {
            // i is not in subtree of s: then the neighbor is up[s][0] (parent of s) on path to i
            return up[s][0];
        }
    };

    for (int i=1;i<=n;++i){
        long long tot = 0;
        for (int s: specials){
            int cntsp = specials_on_path(s, i);
            if (cntsp != 1) continue;
            if (s == i){
                tot += Rsize[s];
            } else {
                int ch = step_from_to(s, i);
                long long k = key(s, ch);
                long long side = edge_count.count(k) ? edge_count[k] : 0;
                tot += Rsize[s] - side;
            }
        }
        A[i] = tot;
    }
cerr<<"hello";
    for (int i=1;i<=n;++i){
        cout << A[i] << (i==n?'\n':' ');
    }
    cerr<<"test";
cout.flush();
    return 0;
}
