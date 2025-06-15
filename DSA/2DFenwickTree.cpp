// A 2D Fenwick Tree (or 2D Binary Indexed Tree) is a data structure used to efficiently update elements and calculate prefix sums over a 2D array (matrix). It supports:

// Point updates: Add a value to an element.

// Range sum queries: Query the sum of values in a submatrix from ( 1 , 1) (1,1) to ( 𝑥 , 𝑦) (x,y) (or any rectangular range with modification).
struct Fenwick2D {
    int n, m;
    vector<vector<int>> bit;

    Fenwick2D(int _n, int _m) : n(_n), m(_m) {
        bit.assign(n + 1, vector<int>(m + 1, 0));
    }

    void add(int x, int y, int delta) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                bit[i][j] += delta;
    }

    int sum(int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                res += bit[i][j];
        return res;
    }

    int range_sum(int x1, int y1, int x2, int y2) {
        return sum(x2, y2) - sum(x1 - 1, y2)
             - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }
};
int main() {
    Fenwick2D ft(5, 5);  // 5x5 grid
    ft.add(2, 3, 5);     // Add 5 at (2,3)
    ft.add(1, 1, 4);     // Add 4 at (1,1)

    cout << ft.range_sum(1, 1, 2, 3) << endl;  // Should output 9
}


// for GCD, query from (1,1) to (x,y)
struct Fenwick2DGCD {
    int n, m;
    vector<vector<int>> bit;

    Fenwick2DGCD(int _n, int _m) : n(_n), m(_m) {
        bit.assign(n + 1, vector<int>(m + 1, 0));
    }

    void update(int x, int y, int val) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                bit[i][j] = __gcd(bit[i][j], val);
    }

    int query(int x, int y) {
        int res = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                res = __gcd(res, bit[i][j]);
        return res;
    }
};

//for max, query from (1,1) to (x,y)
struct Fenwick2DMAX {
    int n, m;
    vector<vector<int>> bit;

    Fenwick2DMAX(int _n, int _m) : n(_n), m(_m) {
        bit.assign(n + 1, vector<int>(m + 1, INT_MIN));
    }

    void update(int x, int y, int val) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                bit[i][j] = max(bit[i][j], val);
    }

    int query(int x, int y) {
        int res = INT_MIN;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                res = max(res, bit[i][j]);
        return res;
    }
};

