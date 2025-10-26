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

#define SHARE_PATH "D:/C++/CP/Share/"

const int TEST_COUNT = 100;
const int TEST_CASE = 10;

bool writeTest(int test) {
    FILE* fp = freopen("input.txt", "w", stdout);
    int T = TEST_CASE;
    if(T != 0) {
        println(T);
    }else T++;
    for(int i=0; i<T; i++){
        println(rnd.next(1, 10));
        //println(rnd.wnext(1, 1000000, opt<int>(1)));
        //println(rnd.next("[a-zA-Z0-9]{1,1000}"))
        //println(rnd.next("[a-zA-Z0-9]{1,%d}", length));
        //println(rnd.next("[0000000001]{100}"));

    }
    fclose(fp);

    system("solution.exe");
    system("brute_force.exe");

    FILE* fp2 = freopen(SHARE_PATH "stress-test-result.txt", "w", stdout); 
    string cmd = string("fc /w \"") + SHARE_PATH + "output.txt\" \"" + SHARE_PATH + "ans.txt\"";
    if (system(cmd.c_str()) != 0) 
    {
        cout << "Test " << test << ": WRONG!\n";
        return false;
    }
    cout << "Test " << test << ": CORRECT!\n";
    fclose(fp2);
    
    return true;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    for (int i = 0; i < TEST_COUNT; i++){
        if(!writeTest(i)) break;
    }
}