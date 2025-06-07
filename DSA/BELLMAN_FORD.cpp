#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;
// Bellman-Ford algorithm to find the shortest paths from a single source in a graph with possible negative weights.
// It can also detect negative weight cycles.
// The graph is represented as a list of edges, where each edge is defined by its start node, end node, and weight.
// Time complexity: O(V * E), where V is the number of vertices and E is the number of edges.
// Space complexity: O(V) for the distance array.
// The function returns true if no negative weight cycle is detected, and false otherwise.
// The edges are represented as a struct with three fields: u (start node), v (end node), and w (weight).
// The distance from the start node to each node is stored in the dist vector, which is initialized to INF for all nodes except the start node.
// The algorithm relaxes all edges up to n-1 times, where n is the number of nodes. After that, it checks for negative weight cycles by trying to relax the edges one more time.
// If any edge can still be relaxed, it indicates the presence of a negative weight cycle.
struct Edge {
    int u, v, w; // from u to v with weight w
};

bool bellmanFord(int n, int start, const vector<Edge> &edges, vector<int> &dist) {
    dist.assign(n, INF);
    dist[start] = 0;

    // Relax edges up to n-1 times
    for (int i = 0; i < n - 1; ++i) {
        for (const Edge &e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    // Check for negative weight cycles
    for (const Edge &e : edges) {
        if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            return false; // Negative cycle detected
        }
    }

    return true; // No negative cycles
}
