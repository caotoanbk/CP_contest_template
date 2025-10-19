#include <bits/stdc++.h>
//update include path if have error
#include "../../../Share/lib/debug2.h"
#include "../../../Share/lib/testlib.h"

using namespace std;
#define FOR(i,a,b) for(int i=(a); i<(b); ++i)
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