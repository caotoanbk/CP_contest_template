#include <bits/stdc++.h>
using namespace std;
#ifdef ON_PC
    #include "../shared/lib/debug2.h"
#else
    #define dbg(...) 
    #define dbgArr(...)
#endif

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

#define F_OR(i, a, b, s) for (int i=(a); (s)>0?i<(b):i>(b); i+=(s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)
#define EACH(x, a) for (auto& x: a)

#define int int64_t
int r,c;
vt<string> grid;
string ms;
const vt<pii> dir = {{1, -1}, {1, 0}, {1, 1}, {0, -1}, {0,0}, {0,1}, {-1,-1}, {-1, 0}, {-1,1}};
pii src;
vt<pii> rpos;

pii getNewPos(int rr, int rc, int pr, int pc){
   pii ans = {rr, rc}; 
   if(rr != pr){
        rr += (rr < pr ? 1 : -1);
   }
   if(rr <0) rr = 0;
   if(rr >= r) rr = r-1;
   if(rc != pc){
        rc += (rc < pc ? 1 : -1);
   }
   if(rc < 0) rc = 0;
   if(rc >= c) rc = c-1;

   return {rr, rc};
}

void solve(){
   cin>>r>>c;
   grid.resize(r);
   
    FOR(i, r){
        cin>>grid[i];
        FOR(j,c){
            if(grid[i][j] == 'I'){
                src = {i, j};
            }else if(grid[i][j] == 'R'){
                rpos.pb({i,j});
            }
        }
    } 
    cin>>ms;
    // dbg(ms);
    FOR(i, sz(ms)){
        vt<vt<bool>> vis(r, vt<bool>(c, false));
        auto [dr,dc] = dir[ms[i] - '0' -1];
        if(grid[src.fi+dr][src.se+dc] == 'R'){
            cout<<"kraj "<<i+1<<endl;
            return;
        }else{
            grid[src.fi][src.se] = '.';
            src.fi += dr;
            src.se += dc;
            grid[src.fi][src.se] = 'I';
        }
        vt<string> newGrid(r, string(c, '.'));
        newGrid[src.fi][src.se] = 'I';
        FOR(j, r){
            FOR(k,c){
                if(grid[j][k] == 'R'){
                    pii newPos = getNewPos(j, k, src.fi, src.se);
                    if(newGrid[newPos.fi][newPos.se] == 'I'){
                        cout<<"kraj "<<i+1<<endl;
                        return;
                    }else if(newGrid[newPos.fi][newPos.se] == '.'){
                        newGrid[newPos.fi][newPos.se] = 'R';
                        // newGrid[j][k] = '.';
                    }else{
                        newGrid[newPos.fi][newPos.se] = 'X';
                        // newGrid[j][k] = '.';
                    }
                }
            }

        }
        FOR(j,r){
            FOR(k,c){
                if(newGrid[j][k] == 'X') newGrid[j][k] = '.';
            }
        }
        grid = newGrid;
        dbg(newGrid);

        // FOR(ii,r){
        //     cout<<grid[ii]<<endl;
        // }
    }

    FOR(i,r){
        cout<<grid[i]<<endl;
    }

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    #ifdef ON_PC
        freopen("../shared/input.txt", "r", stdin);
        freopen("../shared/ans.txt", "w", stdout);

        //freopen("../shared/error.txt", "w", stderr);
        clock_t start, end;
        start = clock();
    #endif // ON_PC

    int t=1; 
    // cin >> t;
    while(t--){
        solve();
    }


    #ifdef ON_PC
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cerr << "Finished in " << time_taken*1000<< " ms " << endl;
    #endif // ON_PC   

    return 0;
}