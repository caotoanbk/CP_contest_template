#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

const int INF = INT_MAX;
// 0-1 BFS algorithm to find the shortest path in a graph with edges of weight 0 or 1.
// This algorithm uses a deque to efficiently process nodes based on edge weights. 
// It is particularly useful for graphs where edges can only have weights of 0 or 1.
// Time complexity: O(V + E), where V is the number of vertices and E is the number of edges.
// Space complexity: O(V) for the distance array and O(E) for the adjacency list.
// The graph is represented as an adjacency list where each edge is a pair (destination, weight).
// The function returns a vector of distances from the start node to all other nodes.
// The distance from the start node to itself is 0, and all other distances are initialized to INF.
// The algorithm processes nodes in a way that ensures that nodes connected by edges of weight 0 are processed first, followed by those connected by edges of weight 1.
// The deque is used to maintain the order of processing: nodes connected by edges of weight 0 are added to the front, while those connected by edges of weight 1 are added to the back.
// The function returns a vector containing the shortest distances from the start node to each node in the graph.

vector<int> zeroOneBFS(int n, vector<vector<pair<int, int>>> &adj, int start) {
    vector<int> dist(n, INF);
    dist[start] = 0;

    deque<int> dq;
    dq.push_front(start);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second; // weight is either 0 or 1

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }

    return dist;
}
