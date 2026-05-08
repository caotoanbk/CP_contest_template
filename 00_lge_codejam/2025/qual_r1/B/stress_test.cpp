#include <bits/stdc++.h>
#include "lib/debug2.h"
#include "lib/testlib.h"

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

const int testcount = 1000; //number of test
const int MAX_TC = 10; //max number of testcase each test
const int testcase = rnd.wnext(1,MAX_TC,3); //random number of testcase

bool writeTest(int test) {
    FILE* fp = freopen("../../../Share/input.txt", "w", stdout);
    int tc = 0;
    if(tc != 0) {
        println(tc);
    }else tc++;
    const int MAX_N = 5;
    const int MAX_TIME = 10;
    const int MAX_P = 100;
    const int MAX_D = 10;
    for(int i=0; i<tc; i++){
        int n = rnd.next(1, MAX_N);
        int k= rnd.next(1, n);
        println(n,k);
       FOR(j, 0, n) {
           int s = rnd.next(1, MAX_TIME/2);
           int e = rnd.next(s + 1, MAX_TIME);  // e > s
           int d = rnd.next(1, MAX_D);
           
           // p > (e - s) * d
           int min_p = (e - s) * d + 1;
           
        //    dbg(s,e,d,min_p);
        int p;
        if(min_p > MAX_P) {
            p = rnd.next(min_p, min_p + 10);     // sinh p >= min_p
        }else{
            p = rnd.next(min_p, MAX_P);     // sinh p >= min_p
        }

            // In ra hoặc xử lý tiếp
            println(s, e, p, d);
        }
        // println(rnd.next(1, 10));
        //println(rnd.wnext(1, 1000000, opt<int>(1)));
        //println(rnd.next("[a-zA-Z0-9]{1,1000}"))
        //println(rnd.next("[a-zA-Z0-9]{1,%d}", length));
        //println(rnd.next("[0000000001]{100}"));

    }
    fclose(fp);

    system("solution.exe"); // run solution
    system("brute_force.exe"); // run brute force
    freopen("../../../Share/stress-test-result.txt", "w", stdout); // redirect output to a file
    if (system("fc /w ..\\..\\..\\Share\\output.txt ..\\..\\..\\Share\\ans.txt") != 0) //compare output files
    {
        cout << "Test " << test << ": WRONG!\n";
        return false;
    }
    cout << "Test " << test << ": CORRECT!\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    
    return true;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    for (int i = 1; i <= testcount; i++){
        if(!writeTest(i)) break;
    }
}