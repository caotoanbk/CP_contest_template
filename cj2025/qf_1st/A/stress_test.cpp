#include <bits/stdc++.h>
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
    FILE* fp = freopen("../shared/input.txt", "w", stdout);
    int tc = testcase;
    if(tc != 0) {
        println(tc);
    }else tc++;
    for(int i=0; i<tc; i++){
        println(rnd.next(1, 10));
        //println(rnd.wnext(1, 1000000, opt<int>(1)));
        //println(rnd.next("[a-zA-Z0-9]{1,1000}"))
        //println(rnd.next("[a-zA-Z0-9]{1,%d}", length));
        //println(rnd.next("[0000000001]{100}"));

    }
    fclose(fp);

    system("solution.exe"); // run solution
    system("brute_force.exe"); // run brute force
    freopen("../shared/stress-test-result.txt", "w", stdout); // redirect output to a file
    if (system("fc /w ..\\shared\\output.txt ..\\shared\\ans.txt") != 0) //compare output files
    {
        cout << "Test " << test << ": WRONG!\n";
        return false;
    }
    cout << "Test " << test << ": CORRECT!\n";
    
    return true;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    for (int i = 1; i <= testcount; i++){
        if(!writeTest(i)) break;
    }
}