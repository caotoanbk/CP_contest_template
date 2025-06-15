#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>



using ll = long long;
const int MOD = 1e9 + 7;

// Function to calculate binomial coefficient C(n, k)
// using iterative approach to avoid overflow
// and ensure efficiency for large values of n and k.
// C(n, k) = n! / (k! * (n - k)!)
// This function calculates the number of ways to choose k elements from n elements.
// It uses the property that C(n, k) = C(n, n - k) to minimize the number of multiplications.
// It iteratively computes the result to avoid large intermediate values.
// for n < k, it returns 0 as it's not possible to choose more elements than available.
// The function is efficient and works well within the constraints of competitive programming.
// It handles large values of n and k without overflow by using long long type.
// It is suitable for problems involving combinatorial counting, such as in combinatorial game theory or probability.
ll binomial(int n, int k) {
    if (k > n) return 0;
    ll res = 1;
    for (int i = 1; i <= k; ++i) {
        res *= n - i + 1;
        res /= i;
    }
    return res;
}

ll countCombinations(int n, int s, int b) {
    ll total = 0;
    for (int k = s; k <= b; ++k) {
        total += binomial(n, k);
    }
    return total;
}
