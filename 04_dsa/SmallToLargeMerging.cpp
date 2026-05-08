// What is it?
// Small-to-Large is a clever technique used to solve subtree-based problems on trees where you maintain some data (like color counts, frequency maps, sets, etc.) for each subtree.

// It’s commonly known as DSU on Tree because it's inspired by Disjoint Set Union logic — always merge smaller sets into larger ones to keep operations fast.

// ✅ When to Use
// You need to compute information for each node’s subtree.

// Example:

// Count how many distinct colors exist in the subtree of each node.

// Compute frequency of a certain value in each node’s subtree.

// Find the mode color in each node’s subtree.

// 🧠 Why it Works
// If you always merge the smaller subtree's data into the larger, then the total number of merges over the whole tree is O(N log N).

// So your complex queries (e.g., maintaining maps, multisets) stay efficient.
//  Example Problem
// You are given a tree with N nodes. Each node has a color.
// For every node, compute how many distinct colors are present in its subtree.

// This is a classic problem that DSU on Tree solves in O(N log N) time.



vector<int> adj[N];
int size[N], color[N], answer[N];
map<int, int> freq[N]; // maps for each subtree

void dfs_size(int u, int p) {
    size[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs_size(v, u);
        size[u] += size[v];
    }
}

void dfs(int u, int p, bool keep) {
    int bigChild = -1, maxSize = -1;
    for (int v : adj[u]) {
        if (v != p && size[v] > maxSize) {
            maxSize = size[v];
            bigChild = v;
        }
    }

    for (int v : adj[u]) {
        if (v != p && v != bigChild) {
            dfs(v, u, false); // process and discard
        }
    }

    if (bigChild != -1) {
        dfs(bigChild, u, true); // process and keep
        freq[u] = freq[bigChild]; // reuse map from big child
    }

    freq[u][color[u]]++;

    for (int v : adj[u]) {
        if (v != p && v != bigChild) {
            for (auto& [col, cnt] : freq[v]) {
                freq[u][col] += cnt;
            }
        }
    }

    // Now freq[u] contains full color frequency of u's subtree
    answer[u] = freq[u].size(); // example: distinct color count

    if (!keep) freq[u].clear(); // discard map if not keeping
}
