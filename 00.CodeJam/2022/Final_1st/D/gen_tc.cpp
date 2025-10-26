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

#define SHARE_PATH "D:/C++/CP/Share/"
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
        int n = 5*10000;
        println(n);
        FOR(i,n){
            cout << rnd.next(-100000000, 100000000) << " ";
        }
        cout << endl;
        int m = 5*100000;
        println(m);
        FOR(i,m){
            cout << rnd.next(1,n) << " " << rnd.next((int)-1e13, (int)1e13) << endl;
        }
        //println(rnd.wnext(1, 1000000, opt<int>(1)));
        //println(rnd.next("[a-zA-Z0-9]{1,1000}"))
        //println(rnd.next("[a-zA-Z0-9]{1,%d}", length));
        //println(rnd.next("[0000000001]{100}"));

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