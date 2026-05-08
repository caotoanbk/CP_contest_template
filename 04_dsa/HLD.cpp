
const int N = 1e5 + 5;
vector<int> tree[N];
int parent[N], depth[N], heavy[N], head[N], pos[N];
int cur_pos;
int subtree_size[N];

// Heavy-Light Decomposition (HLD) for tree queries
// This algorithm decomposes a tree into heavy and light edges to allow efficient path queries.
// // The tree is represented as an adjacency list, and the decomposition is done in two main steps:
// 1. DFS to calculate subtree sizes and identify heavy edges.
// 2. Decompose the tree into chains, where each chain is represented by a head node and a position in the chain.
// The heavy edge is the edge leading to the child with the largest subtree size, while light edges are all other edges.
// The head of a chain is the first node in that chain, and the position is the index of the node in its chain.
// // The `dfs` function calculates the size of each subtree and identifies heavy edges.
// The `decompose` function builds the heavy-light decomposition by assigning heads and positions to each node.
// The `parent` array stores the parent of each node, `depth` stores the depth of each node in the tree,
// `heavy` stores the heavy child of each node, `head` stores the head of the chain for each node, and `pos` stores the position of each node in its chain.
// The `cur_pos` variable keeps track of the current position in the chain as we decompose the tree.
// The `subtree_size` array stores the size of the subtree rooted at each node.
// The time complexity of the HLD algorithm is O(n log n) for the decomposition, where n is the number of nodes in the tree.
// The space complexity is O(n) for storing the tree and the decomposition arrays.
// This algorithm is useful for efficiently answering path queries in trees, such as finding the sum of values along a path or the maximum value along a path.
// The heavy-light decomposition allows us to break down the path queries into smaller segments that can be processed more efficiently.
// The heavy-light decomposition is particularly useful in competitive programming and algorithmic challenges involving trees.
// / It allows for efficient updates and queries on paths in trees, making it a powerful technique for solving various problems involving tree structures.
// The algorithm is often used in conjunction with segment trees or Fenwick trees to handle range queries and updates efficiently.
// The heavy-light decomposition is a fundamental technique in tree algorithms, enabling efficient path queries and updates.
// It is widely used in competitive programming and algorithmic challenges involving trees.
#include <iostream>
#include <vector>

int dfs(int u) {
    subtree_size[u] = 1;
    int max_subtree = 0;
    for (int v : tree[u]) {
        if (v == parent[u]) continue;
        parent[v] = u;
        depth[v] = depth[u] + 1;
        int sz = dfs(v);
        subtree_size[u] += sz;
        if (sz > max_subtree) {
            max_subtree = sz;
            heavy[u] = v;
        }
    }
    return subtree_size[u];
}

void decompose(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;
    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }
    for (int v : tree[u]) {
        if (v != parent[u] && v != heavy[u]) {
            decompose(v, v); // new chain
        }
    }
}
