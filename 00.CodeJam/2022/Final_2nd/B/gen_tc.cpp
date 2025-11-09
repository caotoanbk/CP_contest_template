#include <bits/stdc++.h>
//update include path if have error
#include "../../../../99.Share/lib/debug2.h"
#include "../../../../99.Share/lib/testlib.h"

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

void writeTest() {
    FILE* fp = freopen(SHARE_PATH "input.txt", "w", stdout);
    int T = TEST_CASE;
    if(T != 0) {
        println(T);
    }else T++;
    for(int i=0; i<T; i++){
        //--CODE START HERE---
        // Generate tree with n nodes
        int n = rnd.next(10, 1000); // larger test cases
        println(n);
        
        // Generate values v[1..n]
        FOR(j, 1, n+1){
            cout << rnd.next(-100000, 100000) << " ";
        }
        cout << endl;
        
        // Generate parent array p[1..n], forming a valid tree
        // Node 1 is root (p[1] = 0), others have random parent in [1, i-1]
        cout << 0; // p[1] = 0 (root)
        FOR(j, 2, n+1){
            cout << " " << rnd.next(1, (int)j-1); // parent is any node before this one
        }
        cout << endl;

    }
    fclose(fp);

    system("solution.exe"); 
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