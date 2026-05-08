// Use it when:

// You need to track subsets of elements (e.g., which items are taken/visited).
// The total number of states is around 
// 2^N*N or less
// Classic examples: TSP (Traveling Salesman Problem), Set Cover, Matching problems.
// Bitmask Basics
// An integer is used to represent a subset. Each bit 𝑖 i of the integer tells whether element 𝑖 i is included.
// For example, mask = 5 (binary 0101) means element 0 and 2 are included.

// Bitmask Dynamic Programming (DP) Template for TSP
// Given a cost matrix cost[i][j], find the minimum cost to visit all nodes exactly once and return to the start.
#include <bits/stdc++.h>
const int INF = 1e9;
int n;
int dp[1<<16][16]; // dp[mask][i]: min cost to reach node i having visited 'mask' nodes
int cost[16][16];  // cost[i][j]: cost from i to j

using namespace std;
int tsp(int mask, int u) {
    if (mask == (1<<n) - 1) return cost[u][0]; // all visited, return to start

    int &res = dp[mask][u];
    if (res != -1) return res;

    res = INF;
    for (int v = 0; v < n; ++v) {
        if (!(mask & (1<<v))) { // if v not visited
            res = min(res, cost[u][v] + tsp(mask | (1<<v), v));
        }
    }
    return res;
}

//Example 2: Count the number of ways to assign tasks
// You have n people and n tasks, where can[i][j] = 1 means person 𝑖 i can do task j. Count the number of valid assignments.
const int MAXN = 20;
int n;
int can[MAXN][MAXN]; // can[i][j] = 1 if person i can do task j
long long dp2[1 << MAXN]; // dp[mask] = number of ways to assign tasks in mask

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> can[i][j];

    dp2[0] = 1; // base case: no task assigned yet

    for (int mask = 0; mask < (1 << n); ++mask) {
        int person = __builtin_popcount(mask); // number of tasks assigned so far = current person
        for (int task = 0; task < n; ++task) {
            if ((mask & (1 << task)) == 0 && can[person][task]) {
                dp2[mask | (1 << task)] += dp2[mask];
            }
        }
    }

    cout << dp2[(1 << n) - 1] << endl; // all tasks assigned
    return 0;
}


// Common Techniques
// mask | (1<<i): Add item // i to the set.  mask & ~(1<<i): Remove item i from the set.
// mask & (1<<i): Check if item i is in the set.
// __builtin_popcount(mask): Count how many items are in the set.


// Common Bitmask DP Complexity
// O(N⋅2^N): Efficient for N≤20.
// Use memoization or bottom-up DP with arrays.


