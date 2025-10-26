#include <bits/stdc++.h>
//update include path if have error
#include "lib/debug2.h"
#include "lib/testlib.h"

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

void writeTest() {
    FILE* fp = freopen("../../../Share/input.txt", "w", stdout);
    int tc = 1;
    if(tc != 0) {
        println(tc);
    }else tc++;
    const int MAX_N = 200000;
    const int MAX_M = 10000;
    for(int i=0; i<tc; i++){
        int n = rnd.next(1, MAX_N);
        int m = rnd.next(1, MAX_M);
        cout << n << " " << m << "\n";

        for (int i = 0; i < m; i++) {
            int x = rnd.next(1, n);
            int a = rnd.next(0, n);
            int b = rnd.next(0, 5);
            int c = rnd.next(0, 1000000);
            cout << x << " " << a << " " << b << " " << c << "\n";
        }

    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    const int TEST_COUNT = 1000;
    FOR(i, 0, TEST_COUNT){
        cerr<<"Running test "<<i+1<<"\n";
        writeTest();
        int ret = system("solution.exe"); // run solution
        if(ret != 0){
            cerr << "Runtime Error or non-zero exit code detected!\n";
            cerr << "Exit code = " << ret << "\n";
            return 0;
        }
        
        // this_thread::sleep_for(chrono::milliseconds(200));
    }
}