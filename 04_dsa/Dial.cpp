#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

const int INF = INT_MAX;
// dialsAlgorithm is a modified version of the 0-1 BFS algorithm that can handle weights greater than 1.
// It uses a deque to efficiently process nodes based on edge weights.
// This algorithm is particularly useful for graphs where edges can have weights greater than 1.
// O(W × V + E) Where W = max edge weight, V = vertices, E = edges

vector<int> dialsAlgorithm(int n, const vector<vector<pair<int, int>>> &adj, int start, int maxW) {
    vector<int> dist(n, INF);
    dist[start] = 0;

    vector<deque<int>> buckets(maxW * n + 1);
    buckets[0].push_back(start);

    int idx = 0;
    while (idx < buckets.size()) {
        while (idx < buckets.size() && buckets[idx].empty()) idx++;
        if (idx == buckets.size()) break;

        int u = buckets[idx].front();
        buckets[idx].pop_front();

        if (dist[u] < idx) continue;

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                buckets[dist[v]].push_back(v);
            }
        }
    }

    return dist;
}
