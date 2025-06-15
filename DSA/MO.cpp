// MO algorithm is used for answering range queries efficiently after some updates.
// Given array A[1..N], answer Q queries:
// "What's the answer for range A[L..R]?"
// It is used when:
// The array is static (no updates)
// There are many queries (up to ~1e5)
// The answer for range [L, R] can be updated incrementally by adding/removing elements

// How it works:
// The key idea is to sort the queries cleverly to minimize the number of array operations (add, remove) between queries.
// Divide array into √N blocks
// Sort queries by (L / block_size, R)
// Process queries in this order, shifting a sliding window

// Time Complexity
// Naive approach: O(Q⋅N) Mo’s Algorithm: O((N+Q)⋅ sqrt(N) ​)
// Count distinct in range
// Sum of elements in range
// Frequency of K in range
// Most frequent element


//  Example: Count Distinct Numbers in Range
// You are given:

// Array A[1..N]

// Q queries [L, R]
// Output: Number of distinct values in A[L..R]
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int A[MAXN], cnt[MAXN], answer[MAXN];
int block_size;

struct Query {
    int l, r, idx;
    bool operator<(const Query& other) const {
        int block_a = l / block_size;
        int block_b = other.l / block_size;
        if (block_a != block_b) return block_a < block_b;
        return (block_a & 1) ? r > other.r : r < other.r;  // optimize order
    }
};

int distinct = 0;

void add(int x) {
    cnt[x]++;
    if (cnt[x] == 1) distinct++;
}
void remove(int x) {
    cnt[x]--;
    if (cnt[x] == 0) distinct--;
}

int main() {
    int N, Q;
    cin >> N >> Q;
    block_size = sqrt(N);

    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<Query> queries(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--, queries[i].r--;  // 0-based
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end());

    int L = 0, R = -1;
    for (auto q : queries) {
        while (L > q.l) add(A[--L]);
        while (R < q.r) add(A[++R]);
        while (L < q.l) remove(A[L++]);
        while (R > q.r) remove(A[R--]);

        answer[q.idx] = distinct;
    }

    for (int i = 0; i < Q; ++i)
        cout << answer[i] << '\n';

    return 0;
}
