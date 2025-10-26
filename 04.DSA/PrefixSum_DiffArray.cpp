// Definition:
// Given array A[0..n-1], construct prefix[i] = A[0] + A[1] + ... + A[i]

// prefix[0] = A[0];
// for (int i = 1; i < n; i++)
//     prefix[i] = prefix[i-1] + A[i];
// Use:
// To calculate sum of any range [l, r] in 𝑂 ( 1) O(1):
// sum(l,r)=prefix[r]−(l>0?prefix[l−1]:0)



// 2D prefix sum array
// Let prefix[i][j] be the sum of all elements in the rectangle from (0,0) to (i,j).
// prefix[i][j] = A[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
// To find the sum from (x1, y1) to (x2, y2):
// sum(x1,y1,x2,y2)=prefix[x2][y2]−prefix[x1−1][y2]−prefix[x2][y1−1]+prefix[x1−1][y1−1]
// Be careful with boundaries (x1 = 0 or y1 = 0) to avoid negative indices.
//Time Complexity: O(n * m) for building the prefix sum array, and O(1) for each query.
// Space Complexity: O(n * m) for the prefix sum array.
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int a[N][N], prefix[N][N];

int main() {
    int n, m, q;
    cin >> n >> m;

    // Input matrix
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> a[i][j];

    // Build prefix sum
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            prefix[i][j] = a[i][j];
            if (i > 0) prefix[i][j] += prefix[i-1][j];
            if (j > 0) prefix[i][j] += prefix[i][j-1];
            if (i > 0 && j > 0) prefix[i][j] -= prefix[i-1][j-1];
        }

    cin >> q; // number of queries
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2; // 0-indexed
        int ans = prefix[x2][y2];
        if (x1 > 0) ans -= prefix[x1-1][y2];
        if (y1 > 0) ans -= prefix[x2][y1-1];
        if (x1 > 0 && y1 > 0) ans += prefix[x1-1][y1-1];
        cout << ans << "\n";
    }

    return 0;
}




// Differential Array
// Definition:
// Given an array A[0..n-1], construct a difference array D[0..n-1] such that: 
// D[i] = A[i] - A[i-1] for i > 0, and D[0] = A[0]
// To get the original array A from the difference array D: 
// A[0] = D[0];
// for (int i = 1; i < n; i++)
//     A[i] = A[i-1] + D[i];
// Use:
// To update a range [l, r] by adding a value x in 𝑂 ( 1) O(1)
// D[l] += x;
// D[r + 1] -= x; // if r + 1 < n
// To get the original array A after updates, compute it from D as shown above.:
// 2D differential array
// Let diff[i][j] be the difference array for a 2D matrix A.
// diff[i][j] = A[i][j] - A[i-1][j] - A[i][j-1] + A[i-1][j-1]
// To update a submatrix from (x1, y1) to (x2, y2) by adding a value v:
// diff[x1][y1]       += v;
// diff[x1][y2 + 1]   -= v; // if y2 + 1 < m
// diff[x2 + 1][y1]   -= v; // if x2 + 1 < n
// diff[x2 + 1][y2 + 1] += v; // if x2 + 1 < n and y2 + 1 < m   
// time Complexity: O(n * m) for building the difference array, and O(1) for each update.
// Space Complexity: O(n * m) for the difference array.
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int n, m, q;
int diff[N][N]; // Difference matrix
int mat[N][N];  // Final matrix after applying prefix sum

// Apply value v to submatrix (x1, y1) to (x2, y2)
void add(int x1, int y1, int x2, int y2, int v) {
    diff[x1][y1]       += v;
    diff[x1][y2 + 1]   -= v;
    diff[x2 + 1][y1]   -= v;
    diff[x2 + 1][y2 + 1] += v;
}

int main() {
    cin >> n >> m >> q;

    // Perform Q updates
    while (q--) {
        int x1, y1, x2, y2, val;
        cin >> x1 >> y1 >> x2 >> y2 >> val;
        add(x1, y1, x2, y2, val);
    }

    // Compute the final matrix using 2D prefix sum
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            mat[i][j] = diff[i][j];
            if (i > 0) mat[i][j] += mat[i - 1][j];
            if (j > 0) mat[i][j] += mat[i][j - 1];
            if (i > 0 && j > 0) mat[i][j] -= mat[i - 1][j - 1];
        }

    // Output final matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << mat[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
