#include <bits/stdc++.h>
#include "../../../Share/lib/debug2.h"
#include "../../../Share/lib/testlib.h"

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
#define endl '\n'

const int testcount = 100; //number of test
const int MAX_TC = 10; //max number of testcase each test
const int testcase = rnd.wnext(1,MAX_TC,3); //random number of testcase

bool writeTest(int test) {
    FILE* fp = freopen("../../../Share/input.txt","w",stdout);
    int tc = testcase;
    if(tc != 0) {
        println(tc);
    }else tc++;
    for(int i=0; i<tc; i++){
        int n = rnd.next(1, 3);
        int k= rnd.next(1, 3);
        println(n,k);

        

        //println(rnd.wnext(1, 1000000, opt<int>(1)));
        //println(rnd.next("[a-zA-Z0-9]{1,1000}"))
        //println(rnd.next("[a-zA-Z0-9]{1,%d}", length));
        //println(rnd.next("[0000000001]{100}"));

    }
    fclose(fp);

    system("solution.exe"); // run solution
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    return true;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    for (int i = 0; i < testcount; i++){
        writeTest(i);
    }
}