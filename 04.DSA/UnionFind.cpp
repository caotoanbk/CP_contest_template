#include <vector>

using namespace std;

struct DSU {
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false; // already in the same set

        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        return true;
    }
};

// Example 1: connected components in graph
int n, m;
cin >> n >> m;
DSU dsu(n);

for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    dsu.unite(u, v);
}

int components = 0;
for (int i = 0; i < n; ++i) {
    if (dsu.find(i) == i)
        components++;
}
cout << "Connected components: " << components << "\n";


//Example 2: Krushal Algo MST
struct Edge {
    int u, v, w;
    bool operator<(const Edge &e) const { return w < e.w; }
};

vector<Edge> edges;
DSU dsu(n);
sort(edges.begin(), edges.end());

int total_cost = 0;
for (Edge e : edges) {
    if (dsu.unite(e.u, e.v)) {
        total_cost += e.w;
    }
}

