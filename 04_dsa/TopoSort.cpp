#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;
// Function to perform topological sort on a directed acyclic graph (DAG)
// It returns a vector containing the topological order of the vertices.
// If the graph has a cycle, it returns an empty vector.
// The input is the number of vertices 'n' and an adjacency list 'adj' where adj[i] contains the vertices directed from vertex i.
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> in_deg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : adj[u])
            in_deg[v]++;
    
    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (in_deg[i] == 0)
            q.push(i);

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);

        for (int v : adj[u]) {
            if (--in_deg[v] == 0)
                q.push(v);
        }
    }

    if (topo.size() != n) {
        // There is a cycle
        return {};
    }

    return topo;
}


// Function to perform topological sort using DFS
// It returns a vector containing the topological order of the vertices.
void dfs(int u, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& result) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v])
            dfs(v, visited, adj, result);
    result.push_back(u);  // postorder
}

vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    vector<int> result;

    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs(i, visited, adj, result);

    reverse(result.begin(), result.end());
    return result;
}

// Function to perform topological sort using DFS with a stack
// It returns a vector containing the topological order of the vertices.
void dfs(int u, vector<bool>& visited, stack<int>& st, vector<vector<int>>& adj) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v, visited, st, adj);
    }
    st.push(u);
}

vector<int> topoSort(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    stack<int> st;

    for (int i = 0; i < V; ++i)
        if (!visited[i]) dfs(i, visited, st, adj);

    vector<int> topo;
    while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }
    return topo;
}

