#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

#define ar array
#define vt vector
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define endl '\n'

using namespace std;
// compress values
// set<int> all;
// for (...) all.insert(value);
// map<int, int> compressed;
// int id = 0;
// for (int x : all) compressed[x] = ++id;
// compressed[value] gives the compressed id of value


//lower_bound on decreasing array
// it means that we want the first element which is less than or equal to x
// auto it = lower_bound(arr.rbegin(), arr.rend(), x, greater<int>());

//lower_bound on increasing array
// it means that we want the first element which is greater than or equal to x




// multiset with custom comparator
// sorted by first value in ascending order
// and by second value in descending order if first values are equal
// Custom comparator
struct Comp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second; // Descending order for second value
    }
};

int main() {
    multiset<pair<int, int>, Comp> ms;

    ms.insert({2, 100});
    ms.insert({2, 105});
    ms.insert({2, 101});
    ms.insert({1, 200});
    ms.insert({3, 50});

    for (auto& p : ms) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
}
