#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n; long long k;
        cin >> n >> k;
        vector<long long> a(n);
        unordered_set<long long> present;
        present.reserve(n * 2);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            present.insert(a[i]);
        }
        vector<long long> vals;
        vals.reserve(present.size());
        for (auto x : present) vals.push_back(x);
        sort(vals.begin(), vals.end());
        int D = (int)vals.size();
        long long maxVal = vals.empty() ? 0LL : vals.back();

        // Build candidate list: numbers v in S such that all multiples m*v (m >= 1, m*v <= k) are present.
        vector<long long> candidates;
        candidates.reserve(D);
        for (long long v : vals) {
            if (v <= 0) continue; // safety
            long long need = k / v; // number of multiples up to k
            if (need == 0) continue; // v > k cannot happen since v in S and S only contains <= k
            if (need > D) continue; // not enough distinct numbers to satisfy all multiples
            long long last = need * v;
            if (last > maxVal) continue; // last multiple must be present; if > maxVal it's impossible
            bool ok = true;
            for (long long m = 1; m <= need; ++m) {
                long long x = m * v;
                if (present.find(x) == present.end()) { ok = false; break; }
            }
            if (ok) candidates.push_back(v);
        }

        if (candidates.empty()) {
            cout << -1 << '\n';
            continue;
        }

        sort(candidates.begin(), candidates.end());
        // Assign coverage greedily by smallest candidate divisors
        unordered_map<long long, long long> coveredBy; // value -> smallest candidate divisor
        coveredBy.reserve(vals.size() * 2);
        vector<long long> used; used.reserve(candidates.size());
        unordered_set<long long> usedSet; usedSet.reserve(candidates.size() * 2);

        for (long long b : candidates) {
            long long need = k / b;
            long long last = need * b;
            if (last > maxVal) continue; // safety, though candidate check should guarantee this
            bool usedThis = false;
            for (long long m = 1; m <= need; ++m) {
                long long x = m * b;
                if (present.find(x) == present.end()) continue; // safety
                if (coveredBy.find(x) == coveredBy.end()) {
                    coveredBy[x] = b;
                    usedThis = true;
                }
            }
            if (usedThis) {
                if (usedSet.insert(b).second) used.push_back(b);
            }
        }

        // Verify all present values are covered by some candidate divisor
        bool allCovered = true;
        for (long long x : vals) {
            if (coveredBy.find(x) == coveredBy.end()) { allCovered = false; break; }
        }
        if (!allCovered) {
            cout << -1 << '\n';
            continue;
        }

        // Output minimal set: those candidates that actually covered at least one value when processed in ascending order
        cout << (int)used.size() << '\n';
        for (size_t i = 0; i < used.size(); ++i) {
            if (i) cout << ' ';
            cout << used[i];
        }
        cout << '\n';
    }
    return 0;
}
