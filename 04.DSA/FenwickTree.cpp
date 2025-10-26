#include <vector>
using namespace std;

// fenwick tree with one-based indexing
// supports range sum queries and point updates
// for one-based indexing, the first element is at index 1
// for zero-based indexing, the first element is at index 0
// this implementation uses one-based indexing for the Fenwick Tree
// and zero-based indexing for the input array
// and we want to perform range sum queries and point updates efficiently
struct FenwickTreeOneBasedIndexing {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTreeOneBasedIndexing(int n) {
        this->n = n + 1;
        bit.assign(n + 1, 0);
    }

    FenwickTreeOneBasedIndexing(vector<int> a)
        : FenwickTreeOneBasedIndexing(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (++idx; idx < n; idx += idx & -idx)
            bit[idx] += delta;
    }

    // range add from l to r (inclusive) with value val
    // this is equivalent to adding val to all elements in the range [l, r]
    // l and r are zero-based indices
    // to add val to all elements from index l to r (inclusive), use range_add(l, r, val)
    // to add val to all elements from index 0 to r (inclusive), use range_add(0, r, val)
    // to add val to all elements from index l to n-1 (inclusive), use range_add(l, n-1, val)
    // to add val to all elements from index 0 to n-1 (inclusive), use range_add(0, n-1, val)
    void range_add(int l, int r, int val) {
        add(l, val);
        add(r + 1, -val);
    }

    // point query at index idx
    // this returns the sum of all elements from index 0 to idx (inclusive)
    // idx is zero-based
    // to query the sum of all elements from index 0 to idx (inclusive), use point_query(idx)
    // to query the sum of all elements from index l to r (inclusive), use sum(l, r)
    // to query the sum of all elements from index 0 to r (inclusive), use sum(r)
    int point_query(int idx) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += bit[idx];
        return ret;
    }

};