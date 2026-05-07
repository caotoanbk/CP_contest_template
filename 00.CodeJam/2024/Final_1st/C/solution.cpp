#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define nl '\n'

void solve(){
    int N; ll M,P,K;
    cin >> N >> M >> P >> K;
    vector<int> C(N);
    for(int i=0;i<N;i++) cin >> C[i];

    vector<vector<int>> in(N), out(N);
    for(ll i=0;i<M;i++){
        int X,Y; cin >> X >> Y; --X; --Y;
        out[X].push_back(Y);
        in[Y].push_back(X);
    }

    vector<int> countCross(N,0);
    for(int v=0; v<N; ++v){
        for(int u: in[v]) if(C[u] != C[v]) countCross[v]++;
    }

    queue<int> q;
    vector<char> removed(N,0);
    for(int v=0; v<N; ++v) if(countCross[v]==0) q.push(v);

    vector<ll> removedOnDay(P+1,0);
    ll removedCount=0;

    while(!q.empty()){
        int v=q.front(); q.pop();
        if(removed[v]) continue;
        removed[v]=1;
        removedOnDay[C[v]]++;
        removedCount++;
        for(int w: out[v]){
            if(C[v]!=C[w]){
                countCross[w]--;
                if(countCross[w]==0 && !removed[w]) q.push(w);
            }
        }
    }

    ll stableCount = N - removedCount;

    if(K <= P){
        ll ans = 0;
        for(int d=1; d<=K; ++d){
            ans += (ll)N - removedOnDay[d];
        }
        cout << ans << nl;
    }else{
        ll firstCycle = (ll)N * P - removedCount;
        ll ans = firstCycle + (K - P) * stableCount;
        cout << ans << nl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    if(!(cin>>T)) return 0;
    while(T--) solve();
    return 0;
}
