#include <iostream>
#include <vector> 
using namespace std;


const int MAXN = 1e5 + 5;
const int LOG = 20;
vector<int> tree[MAXN];
int up[MAXN][LOG]; // Binary lifting table
int depth[MAXN];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i < LOG; ++i)
        up[u][i] = up[up[u][i-1]][i-1];
    
    for (int v : tree[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    // 1. Lift u up to the same depth as v
    for (int i = LOG - 1; i >= 0; --i)
        if (depth[u] - (1 << i) >= depth[v])
            u = up[u][i];

    if (u == v) return u;

    // 2. Lift u and v together until their parents match
    for (int i = LOG - 1; i >= 0; --i)
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }

    return up[u][0];
}

// Function to calculate the distance between two nodes u and v
int dist(int u, int v) {
    int w = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[w];
}
