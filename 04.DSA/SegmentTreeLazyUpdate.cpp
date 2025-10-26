// Segment trees with lazy updates allow you to:
// Update all elements in a range [l, r] (e.g., add +5 to all of them)
// Query (sum/min/max) in a range [l, r]
// Efficiently in O(log N) per operation.
// When you do a range update, don't immediately update all children. Instead:
// Store the update in a lazy tag
// Apply it only when needed (i.e., during query or further updates)
// This avoids unnecessary recursion and keeps performance optimal.
// The purpose of the push() function in a segment tree with lazy propagation is:
//  To apply any pending (lazy) updates to the current node and
//  pass those updates down to its children (if any).

// We'll build a segment tree that:
// Supports range add updates
// Supports range sum queries
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
long long tree[4 * MAXN];
long long lazy[4 * MAXN];

int A[MAXN];

// Build the segment tree
void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = A[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Propagate lazy update to children
void push(int node, int l, int r) {
    if (lazy[node] != 0) {
        tree[node] += (r - l + 1) * lazy[node]; // apply lazy to segment

        if (l != r) { // if not leaf node
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }

        lazy[node] = 0; // clear lazy
    }
}

// Range update: add val to [ul..ur]
void update(int node, int l, int r, int ul, int ur, int val) {
    push(node, l, r);

    if (r < ul || l > ur) return; // completely outside

    if (ul <= l && r <= ur) { // completely inside
        lazy[node] += val;
        push(node, l, r);
        return;
    }

    int mid = (l + r) / 2;
    update(2 * node, l, mid, ul, ur, val);
    update(2 * node + 1, mid + 1, r, ul, ur, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Range query: sum of [ql..qr]
long long query(int node, int l, int r, int ql, int qr) {
    push(node, l, r);

    if (r < ql || l > qr) return 0; // completely outside

    if (ql <= l && r <= qr) return tree[node]; // completely inside

    int mid = (l + r) / 2;
    return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
}

int main() {
    int N, Q;
    cin >> N >> Q;

    for (int i = 1; i <= N; ++i) cin >> A[i];

    build(1, 1, N);

    while (Q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Range update: add val to [l..r]
            int l, r, val;
            cin >> l >> r >> val;
            update(1, 1, N, l, r, val);
        } else {
            // Range query: sum of [l..r]
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, N, l, r) << '\n';
        }
    }

    return 0;
}




//Example 2
// Range minimum queries (RMQ)
// Range add updates (i.e. add a value to all elements in a range)
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const long long INF = 1e18;

int A[MAXN];
long long tree[4 * MAXN];
long long lazy[4 * MAXN];

// Build the segment tree
void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = A[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

// Propagate pending lazy updates
void push(int node, int l, int r) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node];
        if (l != r) { // not a leaf node
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

// Range update: add val to [ul..ur]
void update(int node, int l, int r, int ul, int ur, int val) {
    push(node, l, r);
    if (r < ul || l > ur) return; // completely outside

    if (ul <= l && r <= ur) { // completely inside
        lazy[node] += val;
        push(node, l, r);
        return;
    }

    int mid = (l + r) / 2;
    update(2 * node, l, mid, ul, ur, val);
    update(2 * node + 1, mid + 1, r, ul, ur, val);
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

// Range query: min of [ql..qr]
long long query(int node, int l, int r, int ql, int qr) {
    push(node, l, r);
    if (r < ql || l > qr) return INF; // completely outside
    if (ql <= l && r <= qr) return tree[node]; // completely inside

    int mid = (l + r) / 2;
    return min(
        query(2 * node, l, mid, ql, qr),
        query(2 * node + 1, mid + 1, r, ql, qr)
    );
}

int main() {
    int N, Q;
    cin >> N >> Q;

    for (int i = 1; i <= N; ++i) cin >> A[i];

    build(1, 1, N);

    while (Q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Add value to range [l..r]
            int l, r, val;
            cin >> l >> r >> val;
            update(1, 1, N, l, r, val);
        } else {
            // Query min in range [l..r]
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, N, l, r) << '\n';
        }
    }

    return 0;
}
