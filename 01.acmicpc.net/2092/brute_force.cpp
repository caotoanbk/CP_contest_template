#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1000000;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int T, A, S, B;
    cin >> T >> A >> S >> B;

    vector<int> count(T + 1, 0);
    for (int i = 0; i < A; ++i) {
        int x;
        cin >> x;
        count[x]++;
    }

    vector<int> freq;
    for (int i = 1; i <= T; ++i) {
        if (count[i]) freq.push_back(count[i]);
    }

    int n = freq.size();
    vector<vector<int>> dp(n + 1, vector<int>(B + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        int limit = freq[i];
        for (int j = 0; j <= B; ++j) {
            if (dp[i][j] == 0) continue;
            for (int k = 0; k <= limit && j + k <= B; ++k) {
                dp[i + 1][j + k] = (dp[i + 1][j + k] + dp[i][j])%MOD;
            }
        }
    }

    int ans = 0;
    for (int i = S; i <= B; ++i) {
        ans = (ans + dp[n][i])%MOD;
    }

    cout << (ans%MOD) << '\n';
    return 0;
}
