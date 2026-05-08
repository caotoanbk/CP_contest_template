// A Persistent Segment Tree allows you to keep multiple versions of the segment tree, each reflecting a different state of the array after updates.
// Instead of modifying the existing tree, it creates a new version, reusing unchanged nodes to save space.


// Use Cases
// Problem Type	Description
// K-th smallest number in range	Classic problem
// Range sum queries over different versions	Track historical array states
// Rollback support in segment trees	Undo/redo efficiently
// Offline dynamic connectivity	Persistent union-find variant


// Key Concepts
// Each version has its own root node.

// When updating, only nodes on the path from root to leaf are copied — all others are shared.

// Tree space: O(log N) per version


//  Example Problem
// Given an array A of N elements. You must:

// Build versioned segment trees

// Answer queries: "What is the k-th smallest number in A[L..R]?"
// Core Operations
// Build original tree

// Update (create new version) — O(log N)

// Query on a version — O(log N)


//  Idea
// We build a Persistent Segment Tree, where:

// Each version i of the tree contains the first i elements from the array.

// For a query (L, R, k), we use two versions:

// Version R (includes elements A[1] to A[R])

// Version L-1 (to subtract unwanted part)

// By comparing the frequencies of numbers in the trees, we can binary search for the k-th smallest in [L..R].

// Persistent Segment Tree lets you remember all previous array versions

// Perfect for queries on dynamic prefixes like "k-th smallest in subarray"

// Memory and time efficient with log-scale performance
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

struct Node {
    Node* left;
    Node* right;
    int count;

    Node(Node* l = nullptr, Node* r = nullptr, int c = 0)
        : left(l), right(r), count(c) {}
};

Node* build(int l, int r) {
    if (l == r) return new Node();
    int m = (l + r) / 2;
    return new Node(build(l, m), build(m + 1, r));
}

Node* update(Node* prev, int l, int r, int pos) {
    if (l == r) return new Node(nullptr, nullptr, prev->count + 1);
    int m = (l + r) / 2;
    if (pos <= m)
        return new Node(update(prev->left, l, m, pos), prev->right, prev->count + 1);
    else
        return new Node(prev->left, update(prev->right, m + 1, r, pos), prev->count + 1);
}

int query(Node* u, Node* v, int l, int r, int k) {
    if (l == r) return l;
    int cnt = v->left->count - u->left->count;
    int m = (l + r) / 2;
    if (k <= cnt)
        return query(u->left, v->left, l, m, k);
    else
        return query(u->right, v->right, m + 1, r, k - cnt);
}

int N, Q;
int A[MAXN];
vector<int> values;
Node* root[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        values.push_back(A[i]);
    }

    // Compress coordinates
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int M = values.size();

    auto get_id = [&](int x) {
        return lower_bound(values.begin(), values.end(), x) - values.begin() + 1;
    };

    root[0] = build(1, M);
    for (int i = 1; i <= N; ++i) {
        root[i] = update(root[i - 1], 1, M, get_id(A[i]));
    }

    while (Q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int compressed_idx = query(root[l - 1], root[r], 1, M, k);
        cout << values[compressed_idx - 1] << '\n';
    }

    return 0;
}



//Example 2
// Problem Statement:
// You are given an array A of N elements. You must support Q queries. Each query gives you:
// A range [L, R]
// A value X
// You need to return how many times X appears in the subarray A[L..R].
// We’ll:
// Compress values
// Use a persistent segment tree to track prefix frequency for each version (i.e., after each A[i])
// Then answer queries in O(log N) by subtracting two versions
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> A, sorted_vals;
map<int, int> compress;

struct Node {
    Node *left, *right;
    int count;

    Node(int count = 0, Node* left = nullptr, Node* right = nullptr)
        : count(count), left(left), right(right) {}
};

Node* build(int l, int r) {
    if (l == r) return new Node(0);
    int mid = (l + r) / 2;
    return new Node(0, build(l, mid), build(mid + 1, r));
}

Node* update(Node* prev, int l, int r, int pos) {
    if (l == r) return new Node(prev->count + 1);
    int mid = (l + r) / 2;
    if (pos <= mid)
        return new Node(prev->count + 1, update(prev->left, l, mid, pos), prev->right);
    else
        return new Node(prev->count + 1, prev->left, update(prev->right, mid + 1, r, pos));
}

int query(Node* u, Node* v, int l, int r, int pos) {
    if (l == r) return v->count - u->count;
    int mid = (l + r) / 2;
    if (pos <= mid)
        return query(u->left, v->left, l, mid, pos);
    else
        return query(u->right, v->right, mid + 1, r, pos);
}

int main() {
    int N, Q;
    cin >> N >> Q;

    A.resize(N + 1);  // 1-based
    sorted_vals.reserve(N);

    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        sorted_vals.push_back(A[i]);
    }

    // Coordinate compression
    sort(sorted_vals.begin(), sorted_vals.end());
    sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());
    for (int i = 0; i < sorted_vals.size(); ++i)
        compress[sorted_vals[i]] = i + 1; // compressed values in 1..M

    int M = sorted_vals.size();
    vector<Node*> root(N + 1);
    root[0] = build(1, M);

    for (int i = 1; i <= N; ++i)
        root[i] = update(root[i - 1], 1, M, compress[A[i]]);

    while (Q--) {
        int L, R, X;
        cin >> L >> R >> X;

        if (compress.find(X) == compress.end()) {
            cout << "0\n";
        } else {
            int cx = compress[X];
            int res = query(root[L - 1], root[R], 1, M, cx);
            cout << res << '\n';
        }
    }

    return 0;
}
