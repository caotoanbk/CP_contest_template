#include <iostream>
#include <vector>
using namespace std;



// Function to perform depth-first search to find valid combinations
// of ants from different families that meet the size constraints
// Parameters:
// - i: current family index
// - sum: current total number of ants in the group
// - current: current combination of ants
// - counts: vector containing the number of ants in each family
// - S: minimum group size
// - B: maximum group size
// - result: vector to store all valid combinations
// Returns: void
// This function explores all combinations of ants from different families
// by recursively adding ants from each family and checking if the
// resulting group size is within the specified limits (S to B).
// time complexity: O(n^k), where n is the number of families and k is the maximum number of ants in any family.
void dfs(int i, int sum, vector<int>& current, const vector<int>& counts, int S, int B, vector<vector<int>>& result) {
    if (sum > B) return;
    if (i == counts.size()) {
        if (sum >= S) {
            result.push_back(current);
        }
        return;
    }

    for (int x = 0; x <= counts[i]; ++x) {
        current.push_back(x);
        dfs(i + 1, sum + x, current, counts, S, B, result);
        current.pop_back();
    }
}

int main() {
    vector<int> counts = {2, 2, 1}; // Number of ants per family
    int S = 2, B = 3;               // Valid group size range

    vector<vector<int>> result;
    vector<int> current;

    dfs(0, 0, current, counts, S, B, result);

    cout << "Valid combinations (from S=" << S << " to B=" << B << "):\n";
    for (const auto& comb : result) {
        for (int x : comb) {
            cout << x << " ";
        }
        cout << '\n';
    }

    cout << "Total combinations: " << result.size() << '\n';

    return 0;
}
