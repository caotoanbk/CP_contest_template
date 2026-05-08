// dynamic segment tree implementation in C++
// This code implements a dynamic segment tree that allows for point updates and range queries.
// It supports operations to update a value at a specific position and to query the sum of values in a given range.
// The segment tree is implemented using a recursive structure, where each node represents a segment of the array.
// The tree is built dynamically, meaning nodes are created as needed during updates and queries.
// this implementation is efficient for scenarios where the array size can change or where frequent updates and queries are required.
// time complexity for updates and queries is O(log n), where n is the number of elements in the segment tree.
#include <iostream>
using namespace std;

struct Node {
    long long val = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

const int MAX_RANGE = 1e9; // Range [0, 1e9 - 1]

// Point update: add value at position pos
void update(Node*& node, int l, int r, int pos, long long value) {
    if (!node) node = new Node();

    if (l == r) {
        node->val += value;
        return;
    }

    int mid = l + (r - l) / 2;
    if (pos <= mid)
        update(node->left, l, mid, pos, value);
    else
        update(node->right, mid + 1, r, pos, value);

    node->val = 0;
    if (node->left) node->val += node->left->val;
    if (node->right) node->val += node->right->val;
}

// Range query: sum of [ql, qr]
long long query(Node* node, int l, int r, int ql, int qr) {
    if (!node || ql > r || qr < l)
        return 0;

    if (ql <= l && r <= qr)
        return node->val;

    int mid = l + (r - l) / 2;
    return query(node->left, l, mid, ql, qr) +
           query(node->right, mid + 1, r, ql, qr);
}

// -------- Test --------
int main() {
    Node* root = nullptr;

    // Update index 5 to +10
    update(root, 0, MAX_RANGE - 1, 5, 10);
    // Update index 100000000 to +20
    update(root, 0, MAX_RANGE - 1, 100000000, 20);

    // Query [0, 10] -> should be 10
    cout << "Query [0,10]: " << query(root, 0, MAX_RANGE - 1, 0, 10) << endl;

    // Query [0, 1e9-1] -> should be 30
    cout << "Query [0,1e9-1]: " << query(root, 0, MAX_RANGE - 1, 0, MAX_RANGE - 1) << endl;

    return 0;
}
