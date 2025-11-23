#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define nl '\n'
#ifdef ON_PC
  #include "lib\debug2.h"
  #define VEC(v, i) (v.at(i))
  #define MAT(mat, i, j) (mat.at(i).at(j))
#else
  #define VEC(v, i) (v[i])
  #define MAT(mat, i, j) (mat[i][j])
  #define dbg(...)
  #define dbgArr(...)
#endif

struct VecHash {
    size_t operator()(const vector<uint64_t>& v) const {
        uint64_t h = 1469598103934665603ULL;
        for(uint64_t x: v){
            h ^= x;
            h *= 1099511628211ULL;
        }
        return (size_t)h;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T=1;
    if(!(cin>>T)) return 0;
    while(T--){
        int N; ll M,P,K;
        cin>>N>>M>>P>>K;
        vector<int> C(N);
        for(int i=0;i<N;i++) cin>>VEC(C,i);

        vector<vector<int>> adj(N);
        for(ll i=0;i<M;i++){
            int X,Y; cin>>X>>Y; --X; --Y;
            VEC(adj,X).push_back(Y);
        }
        vector<vector<int>> clean(P+1);
        for(int i=0;i<N;i++) clean[VEC(C,i)].push_back(i);

        vector<uint64_t> infected((N+63)>>6, ~0ULL);
        int extra = (int)infected.size()*64 - N;
        if(extra>0){
            uint64_t mask = (~0ULL) >> extra;
            infected.back() &= mask;
        }
        auto isInf = [&](int u)->bool{
            return (infected[u>>6] >> (u & 63)) & 1ULL;
        };
        auto setInf = [&](int u){
            infected[u>>6] |= (1ULL << (u & 63));
        };
        auto clearInf = [&](int u){
            infected[u>>6] &= ~(1ULL << (u & 63));
        };
        auto popcountAll = [&]()->ll{
            ll s=0;
            for(uint64_t w: infected) s += __builtin_popcountll(w);
            return s;
        };

        unordered_map<vector<uint64_t>, pair<ll,ll>, VecHash> seen;

        vector<ll> perDay; perDay.reserve((size_t)P*2);
        ll total = 0;

        for(ll day=1; day<=K; ++day){
            int dayIdx = int((day-1)%P)+1;

            for(int u: VEC(clean,dayIdx)) if(isInf(u)) clearInf(u);

            vector<int> newly;
            for(int u=0; u<N; ++u){
                if(!isInf(u)) continue;
                for(int v: VEC(adj,u)){
                    if(!isInf(v)) newly.push_back(v);
                }
            }
            for(int v: newly) setInf(v);

            ll cnt = popcountAll();
            total += cnt;
            perDay.push_back(cnt);

            if(dayIdx == P){
                vector<uint64_t> key = infected;
                auto it = seen.find(key);
                if(it != seen.end()){
                    ll prevDay = it->second.first;
                    ll prevSum = it->second.second;
                    ll cycleLenDays = day - prevDay;
                    ll cycleSum = total - prevSum;

                    ll remaining = K - day;
                    ll fullCycles = remaining / cycleLenDays;
                    total += fullCycles * cycleSum;

                    ll tail = remaining % cycleLenDays;
                    vector<ll> cycleSeq(perDay.end()-cycleLenDays, perDay.end());
                    for(ll i=0;i<tail;i++) total += VEC(cycleSeq,i);
                    cout << total << nl;
                    goto END_TESTCASE;
                }else{
                    VEC(seen,key) = { day, total };
                }
            }
        }
        cout << total << nl;
        END_TESTCASE:;
    }
    return 0;
}
