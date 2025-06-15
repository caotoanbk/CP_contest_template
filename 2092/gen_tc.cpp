#include <bits/stdc++.h>
//update include path if have error
#include "../shared/lib/testlib.h"
#include "../shared/lib/debug2.h"

using namespace std;
#define F_OR(i, a, b, s) for (int i=(a); (s)>0?i<(b):i>(b); i+=(s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)
#define EACH(x, a) for (auto& x: a)

//Max of testcase each test
const int MAX_TC = 10;
//Num of testcase each test
const int testcase = rnd.wnext(1,MAX_TC,3);

void writeTest() {
    FILE* fp = freopen("../shared/input.txt", "w", stdout);
    int tc = 0;
    if(tc != 0) {
        println(tc);
    }else tc++;
    for(int i=0; i<tc; i++){
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
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    writeTest();
}