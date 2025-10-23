#include <bits/stdc++.h>
#include "d:\C++\CP\Share\lib\debug2.h"
#include "d:\C++\CP\Share\lib\testlib.h"

using namespace std;
#define FOR(i,a,b) for(int i=(a); i<(b); ++i)
#define REP(i,n) FOR(i,0,n)
#define PER(i,n) for(int i=(n)-1; i>=0; --i)

typedef pair<int,int> pii;
#define ll long long
#define ld long double
#define ar array
#define vt vector
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define nl '\n'

const int testcount = 100; //number of test
const int MAX_TC = 10; //max number of testcase each test
const int testcase = rnd.wnext(1,MAX_TC,3); //random number of testcase

// Hàm sinh cây
vector<pair<int,int>> genTree(int n, string type = "random") {
    vector<int> parent(n + 1, 0);
    vector<pair<int,int>> edges;

    if (type == "chain") {
        for (int i = 2; i <= n; i++) edges.push_back({i-1, i});
    }
    else if (type == "star") {
        for (int i = 2; i <= n; i++) edges.push_back({1, i});
    }
    else if (type == "binary") {
        vector<int> childrenCount(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            int p;
            do {
                p = rnd.next(1, i - 1);
            } while (childrenCount[p] >= 2);
            parent[i] = p;
            childrenCount[p]++;
            edges.push_back({p, i});
        }
    }
    else { // random
        for (int i = 2; i <= n; i++) {
            parent[i] = rnd.next(1, i - 1);
            edges.push_back({parent[i], i});
        }
        // shuffle bằng Fisher-Yates dùng rnd
        for (int i = edges.size() - 1; i > 0; i--) {
            int j = rnd.next(0, i);
            swap(edges[i], edges[j]);
        }
    }

    return edges;
}
// Hàm chọn m node đặc biệt
vector<int> chooseSpecialNodes(int n, int m) {
    vector<int> nodes(n);
    for (int i = 0; i < n; i++) nodes[i] = i+1;

    // Fisher-Yates shuffle để lấy m node
    for (int i = n-1; i > n-m-1; i--) {
        int j = rnd.next(0, i);
        swap(nodes[i], nodes[j]);
    }

    return vector<int>(nodes.end()-m, nodes.end());
}

const int MAX_N = 6;

bool writeTest(int test) {
    FILE* fp = freopen("d:\\C++\\CP\\Share\\input.txt", "w", stdout);
    int tc = 2;
    if(tc != 0) {
        println(tc);
    }else tc++;
    for(int i=0; i<tc; i++){
        int n = rnd.wnext(1, MAX_N, 2);
        int m = rnd.next(1,n);

        auto edges = genTree(n);
        auto specialNodes = chooseSpecialNodes(n, m);

        // In cây
        cout << n << "\n";
        for (auto e : edges) cout << e.first << " " << e.second << "\n";

        // In m node đặc biệt
        cout << m << "\n";
        for (int x : specialNodes) cout << x << " ";
        cout<< "\n";

    }
    fclose(fp);

    // system("solution.exe"); // run solution
    // system("brute_force.exe"); // run brute force
    // freopen("../../../Share/stress-test-result.txt", "w", stdout); // redirect output to a file
    // if (system("fc /w ..\\..\\..\\Share\\output.txt ..\\..\\..\\Share\\ans.txt") != 0) //compare output files
    // {
    //     cout << "Test " << test << ": WRONG!\n";
    //     return false;
    // }
    // cout << "Test " << test << ": CORRECT!\n";
    
    return false;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    for (int i = 1; i <= testcount; i++){
        if(!writeTest(i)) break;
    }
}