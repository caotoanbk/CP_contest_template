#include <iostream>
#include <vector>
using namespace std;
// This code finds a path from node u to node v with at most k edges in an unweighted directed graph.
// It uses Depth First Search (DFS) to explore the graph and prints the first path found within k edges.
// it can use same edge multiple times, so it is not suitable for finding the simple path.
// Remove found = true; to find all paths instead of stopping after the first one.
// time complexity when find all path is O(n^k) in the worst case, where n is the number of nodes.
vector<vector<int>> adj;
vector<int> path;
bool found = false;

void dfs(int u, int v, int k) {
    if (k < 0 || found) return;  // stop if over k or already found
    path.push_back(u);

    if (u == v) {
        // found path within k edges
        for (int node : path) cout << node << " ";
        cout << "\n";
        found = true; // stop after finding one path
        path.pop_back();
        return;
    }

    for (int neighbor : adj[u]) {
        dfs(neighbor, v, k - 1);
    }

    path.pop_back();
}

int main() {
    int n, m;
    cin >> n >> m;  // number of nodes and edges
    adj.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // if undirected, also add adj[v].push_back(u);
    }

    int start, end, k;
    cin >> start >> end >> k;

    dfs(start, end, k);

    if (!found) cout << "No path within " << k << " edges.\n";
    return 0;
}



//for simple path, you can use visited array to avoid cycles
// but it will not work for finding all paths, as it will skip some paths that may be valid.
// why? because it will not allow to visit the same node again, so it will not find all paths.
// but we set visted[u]=false; after dfs call, so it will allow to visit the same node again in other paths ==> why you said it will not work for finding all paths?
void dfs(int u, int v, int k, vector<bool>& visited) {
    if (k < 0 || found) return;
    if (visited[u]) return;

    visited[u] = true;
    path.push_back(u);

    if (u == v) {
        for (int node : path) cout << node << " ";
        cout << "\n";
        found = true;
        path.pop_back();
        visited[u] = false;
        return;
    }

    for (int neighbor : adj[u]) {
        dfs(neighbor, v, k - 1, visited);
    }

    path.pop_back();
    visited[u] = false;
}

// This code finds all paths from node u to node v with at most k edges in an unweighted directed graph.
// It uses Depth First Search (DFS) to explore the graph and prints all valid paths found within k edges.
// It can handle cycles by using a visited array to avoid revisiting nodes.
// time complexity is O(n^k) in the worst case, where n is the number of nodes.
// This implementation allows for finding all paths instead of stopping after the first one.
// It can be used for both directed and undirected graphs by adjusting the adjacency list accordingly.

vector<vector<int>> adj;
vector<int> path;

void dfs(int u, int v, int k, vector<bool>& visited) {
    if (k < 0) return;       // too many edges
    if (visited[u]) return;  // avoid cycles

    path.push_back(u);
    visited[u] = true;

    if (u == v) {
        // print valid path
        for (int node : path) cout << node << " ";
        cout << "\n";
    }

    for (int neighbor : adj[u]) {
        dfs(neighbor, v, k - 1, visited);
    }

    path.pop_back();
    visited[u] = false;
}

int main() {
    int n, m;
    cin >> n >> m;  // nodes and edges
    adj.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // directed graph
        // for undirected: adj[v].push_back(u);
    }

    int start, end, k;
    cin >> start >> end >> k;

    vector<bool> visited(n, false);
    dfs(start, end, k, visited);

    return 0;
}

