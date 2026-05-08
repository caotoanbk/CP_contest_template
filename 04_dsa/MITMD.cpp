// Meet in the Middle (MITM) is a technique used in cryptography and algorithm design.
//A technique used when:
// The problem has too many combinations (usually 2^𝑛 ), and
// You can split the problem into two halves, solve both, and combine the results smartly.
// Typical when 𝑛 ≤ 40 n≤40 (too large for brute-force)
// Best when searching for subsets, sums, or paths
//  How It Works
// Divide the elements into two halves
// Generate all subsets of both halves (up to 2^ n/2 each)
// Use a smart search technique (like binary search or hash maps) to combine results efficiently
// Given an array A of n ≤ 40 integers and a target sum S, find the maximum sum ≤ S from any subset of A.
// naive approach would take O(2^n) time, which is infeasible for n = 40.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void generateSums(const vector<int>& arr, vector<ll>& sums) {
    int n = arr.size();
    for (int mask = 0; mask < (1 << n); ++mask) {
        ll sum = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
                sum += arr[i];
        sums.push_back(sum);
    }
}

ll maxSubsetSumLE(const vector<int>& A, int S) {
    int n = A.size();
    vector<int> left(A.begin(), A.begin() + n / 2);
    vector<int> right(A.begin() + n / 2, A.end());

    vector<ll> sumLeft, sumRight;
    generateSums(left, sumLeft);
    generateSums(right, sumRight);

    sort(sumRight.begin(), sumRight.end());

    ll best = 0;
    for (ll x : sumLeft) {
        if (x > S) continue;
        // Find max y in sumRight such that x + y <= S
        ll remain = S - x;
        auto it = upper_bound(sumRight.begin(), sumRight.end(), remain);
        if (it != sumRight.begin()) {
            --it;
            best = max(best, x + *it);
        }
    }

    return best;
}

// Meet in the Middle (MITM) approach to find the maximum subset sum less than or equal to S
// this version works with negative numbers and zero as well, ensuring that the best sum is initialized to LLONG_MIN
ll maxSubsetSumLE(const vector<int>& A, int S) {
    int n = A.size();
    vector<int> left(A.begin(), A.begin() + n / 2);
    vector<int> right(A.begin() + n / 2, A.end());

    vector<ll> sumLeft, sumRight;
    generateSums(left, sumLeft);
    generateSums(right, sumRight);

    sort(sumRight.begin(), sumRight.end());

    ll best = LLONG_MIN;
    for (ll x : sumLeft) {
        ll remain = S - x;
        auto it = upper_bound(sumRight.begin(), sumRight.end(), remain);
        if (it != sumRight.begin()) {
            --it;
            best = max(best, x + *it);
        }
    }

    return best;
}


// STEP
// Split array	Half into left and right
// Precompute all subsets	Up to 2^20 each
// Use smart search	Binary search or hash for best match