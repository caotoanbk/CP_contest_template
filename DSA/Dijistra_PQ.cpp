#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
// Dijkstra's algorithm using priority queue (min-heap) only works for non-negative weights
// This implementation finds the shortest path from a single source to all other nodes in a graph.
// The graph is represented as an adjacency list where each edge is a pair (destination, weight).
// The function returns a vector of distances from the source to each node.
// Time complexity: O((V + E) log V), where V is the number of vertices and E is the number of edges.
// Space complexity: O(V) for the distance array and O(E) for the adjacency list.
const int INF = INT_MAX;

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
