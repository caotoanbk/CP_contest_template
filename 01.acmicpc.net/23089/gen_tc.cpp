#include <bits/stdc++.h>
//update include path if have error
#include "lib/debug2.h"
#include "lib/testlib.h"
#define VEC(v, i) (v.at(i))
#define MAT(mat, i, j) (mat.at(i).at(j))

using namespace std;
#define FOR(i,a,b) for(ll i=(a); i<(b); ++i)
#define REP(i,n) FOR(i,0,n)
#define PER(i,n) for(ll i=(n)-1; i>=0; --i)


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

#define SHARE_PATH "D:/C++/CP/99.Share/"
const int TEST_CASE = 10;
const int TEST_COUNT = 100;


// Hàm sinh cây node tu 1 den n
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

void writeTest() {
    FILE* fp = freopen(SHARE_PATH "input.txt", "w", stdout);
    int T = 0;
    if(T != 0) {
        println(T);
    }else T++;
    for(int i=0; i<T; i++){
       int n = rnd.next(1, 200000);
       int k = rnd.next(1,20);
       auto edges = genTree(n, "random");
       println(n, k);
       for(auto [u, v] : edges){
           println(u, v);
       }
    }
    fclose(fp);

    system("solution_copy.exe"); 
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    FOR(i, 0, TEST_COUNT){
        cerr<<"Running test "<<i+1<<"\n";
        writeTest();
        int ret = system("solution.exe");
        if(ret != 0){
            cerr << "Runtime Error or non-zero exit code detected!\n";
            cerr << "Exit code = " << ret << "\n";
            return 0;
        }
        
        // this_thread::sleep_for(chrono::milliseconds(200));
    }
}