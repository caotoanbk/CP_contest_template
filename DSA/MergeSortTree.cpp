// What It Does:
// It allows binary search within a range!
// Built like a segment tree, but each node stores a sorted vector of its segment.
//  Use Cases:
// Count numbers ≤ X in range [L, R]

// Count numbers > X, < X, or in [a, b]

// Find the K-th smallest element in a range (with extra techniques)

// Used in: Mo’s Algorithm, Wavelet Tree alternatives
// Example: Count numbers ≤ x in [l, r]
//  Step 1: Build Tree
const int N = 1e5 + 5;
vector<int> tree[4 * N];

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = {a[tl]};
        return;
    }
    int tm = (tl + tr) / 2;
    build(a, 2*v, tl, tm);
    build(a, 2*v+1, tm+1, tr);
    merge(tree[2*v].begin(), tree[2*v].end(),
          tree[2*v+1].begin(), tree[2*v+1].end(),
          back_inserter(tree[v]));
}



// Step 2: Query number of elements ≤ x in [l, r]
int query(int v, int tl, int tr, int l, int r, int x) {
    if (r < tl || tr < l) return 0;
    if (l <= tl && tr <= r) {
        return upper_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin();
    }
    int tm = (tl + tr) / 2;
    return query(2*v, tl, tm, l, r, x) +
           query(2*v+1, tm+1, tr, l, r, x);
}
//example
int a[N] = {5, 1, 2, 3, 4};

build(a, 1, 0, 4);

// How many numbers ≤ 3 in range [1, 4]?
int res = query(1, 0, 4, 1, 4, 3); // Output: 3 (1,2,3)








// Given an array a[1..n], and multiple queries of the form:
// What is the K-th smallest element in the subarray [l, r]?
// Merge Sort Tree + Binary Search on Answer
// Build a Merge Sort Tree.
// For each query, binary search the answer x such that:
// count of elements ≤ x in [l, r] ≥ K
// This x is the K-th smallest.

// 1. Build a Merge Tree:
// Each node stores a sorted list of the elements in its segment.
vector<int> seg[4 * N];

void build(int v, int tl, int tr, const vector<int> &a) {
    if (tl == tr) {
        seg[v] = {a[tl]};
        return;
    }
    int tm = (tl + tr) / 2;
    build(2*v, tl, tm, a);
    build(2*v+1, tm+1, tr, a);
    merge(seg[2*v].begin(), seg[2*v].end(),
          seg[2*v+1].begin(), seg[2*v+1].end(),
          back_inserter(seg[v]));
}


// 2. Query: Count of values ≤ x in [l, r]
int count(int v, int tl, int tr, int l, int r, int x) {
    if (tr < l || r < tl) return 0;
    if (l <= tl && tr <= r)
        return upper_bound(seg[v].begin(), seg[v].end(), x) - seg[v].begin();

    int tm = (tl + tr) / 2;
    return count(2*v, tl, tm, l, r, x) + count(2*v+1, tm+1, tr, l, r, x);
}

// 3. Binary Search on Answer
// You binary search over all possible values in the array.
int kth_smallest(int l, int r, int k, const vector<int>& sorted_vals) {
    int lo = 0, hi = sorted_vals.size() - 1, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int x = sorted_vals[mid];
        int cnt = count(1, 0, n-1, l, r, x);
        if (cnt >= k) {
            ans = x;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
// sorted_vals is the sorted unique values of a[].
//usage
vector<int> a = {1, 5, 2, 6, 3, 7, 4};
vector<int> sorted_vals = a;
sort(sorted_vals.begin(), sorted_vals.end());
build(1, 0, a.size() - 1, a);

int ans = kth_smallest(1, 5, 3, sorted_vals); // 3rd smallest in [1, 5]
