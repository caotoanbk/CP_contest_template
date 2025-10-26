#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int N;
vector<int> tree[MAXN];
int val[MAXN];          // Node values

int size[MAXN], depth[MAXN], parent[MAXN], heavy[MAXN];
int head[MAXN], in[MAXN], out[MAXN], timer;
int flatTree[MAXN];
// dfs()	Compute subtree sizes, heavy child
// decompose()	Flatten tree & label chains
// build()	Segment tree on flat array
// query()	Range sum in segment tree
// getPathSum()	Climb up via HLD, combine segments
// updateNode()	Point update in segment tree


// Segment tree for point update & range sum
long long seg[4 * MAXN];

void dfs(int u, int p) {
    size[u] = 1;
    parent[u] = p;
    depth[u] = depth[p] + 1;
    int max_size = 0;
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);
        size[u] += size[v];
        if (size[v] > max_size) {
            max_size = size[v];
            heavy[u] = v;
        }
    }
}

void decompose(int u, int h) {
    in[u] = ++timer;
    flatTree[timer] = val[u];
    head[u] = h;

    if (heavy[u]) decompose(heavy[u], h);
    for (int v : tree[u]) {
        if (v != parent[u] && v != heavy[u])
            decompose(v, v);
    }

    out[u] = timer;
}

void build(int id = 1, int l = 1, int r = N) {
    if (l == r) {
        seg[id] = flatTree[l];
        return;
    }
    int mid = (l + r) / 2;
    build(id*2, l, mid);
    build(id*2+1, mid+1, r);
    seg[id] = seg[id*2] + seg[id*2+1];
}

void update(int pos, int val, int id = 1, int l = 1, int r = N) {
    if (l == r) {
        seg[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(pos, val, id*2, l, mid);
    else update(pos, val, id*2+1, mid+1, r);
    seg[id] = seg[id*2] + seg[id*2+1];
}

long long query(int u, int v, int id = 1, int l = 1, int r = N) {
    if (u > r || v < l) return 0;
    if (u <= l && r <= v) return seg[id];
    int mid = (l + r) / 2;
    return query(u, v, id*2, l, mid) + query(u, v, id*2+1, mid+1, r);
}

long long getPathSum(int u, int v) {
    long long res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        res += query(in[head[u]], in[u]);
        u = parent[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res += query(in[u], in[v]);
    return res;
}

void updateNode(int u, int newVal) {
    update(in[u], newVal);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> val[i];
    for (int i = 1; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1, 0);            // Root at 1
    decompose(1, 1);
    build();              // Segment tree

    int Q; cin >> Q;
    while (Q--) {
        string op;
        int u, v;
        cin >> op >> u >> v;
        if (op == "QUERY") {
            cout << getPathSum(u, v) << '\n';
        } else if (op == "UPDATE") {
            updateNode(u, v);
        }
    }
    return 0;
}

