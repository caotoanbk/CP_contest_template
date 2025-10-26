#include <bits/stdc++.h>
using namespace std;

vector<int> reconstructLIS(vector<int>& A) {
    int n = A.size();
    vector<int> dp(n, 1);      // dp[i] = LIS length ending at i
    vector<int> prev(n, -1);   // prev[i] = previous index in the LIS

    int max_len = 1, last = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (A[j] < A[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            last = i;
        }
    }

    // Reconstruct the sequence from back to front
    vector<int> lis;
    for (int i = last; i != -1; i = prev[i])
        lis.push_back(A[i]);
    
    reverse(lis.begin(), lis.end());
    return lis;
}


#include <bits/stdc++.h>
using namespace std;

vector<int> lis_with_reconstruction(const vector<int>& a) {
    int n = (int)a.size();
    const int INF = 1e9;
    vector<int> d(n+1, INF);
    vector<int> pos(n+1, -1);    // pos[l] = index of element ending LIS of length l
    vector<int> parent(n, -1);   // parent[i] = index of predecessor of a[i] in LIS

    d[0] = -INF;

    for (int i = 0; i < n; i++) {
        // find the smallest l where d[l] > a[i]
        int l = (int)(upper_bound(d.begin(), d.end(), a[i]) - d.begin());
        // update if a[i] can improve subsequence length l
        if (d[l-1] < a[i] && a[i] < d[l]) {
            d[l] = a[i];
            pos[l] = i;
            parent[i] = pos[l-1];
        }
    }

    // find length of LIS
    int length = 0;
    for (int l = 0; l <= n; l++) {
        if (d[l] < INF) length = l;
    }

    // reconstruct LIS from pos[length]
    vector<int> lis_seq(length);
    int curr = pos[length];
    for (int i = length - 1; i >= 0; i--) {
        lis_seq[i] = a[curr];
        curr = parent[curr];
    }

    return lis_seq;
}

int main() {
    vector<int> a = {3, 10, 2, 1, 20};
    vector<int> lis_seq = lis_with_reconstruction(a);

    cout << "Length of LIS: " << (int)lis_seq.size() << "\n";
    cout << "LIS: ";
    for (int x : lis_seq) cout << x << ' ';
    cout << "\n";

    return 0;
}
