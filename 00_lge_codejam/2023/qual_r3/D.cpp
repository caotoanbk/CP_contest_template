#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vt vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define F0R(i, a) FOR(i, 0, a)

const ll mod = 1e9 + 7;
const ll LIMIT = 1'000'000'000'000'000'000ll;
const ll SENTINEL = LIMIT + 1;

vt<ll> mono; //
vt<ll> prefS;

void gen(ll cur, int last_dig){
    mono.pb(cur);

    FOR(d, last_dig, 10){
        if(cur > (LIMIT - d) / 10) break;
        gen(cur * 10 + d, d);
    }
}

void pre(){
    mono.pb(SENTINEL);
    ll n = mono.size();
    prefS.resize(n);
    for(ll i = 0; i+1 < n; i++){
        ll len = (mono[i+1] - mono[i])%mod;
        prefS[i+1] = (prefS[i] + mono[i] % mod * len) % mod;
    }
}

ll S(ll x){
    if(x < 0) return 0;
    int idx = upper_bound(mono.begin(), mono.end(), x) - mono.begin() - 1;
    ll cnt = (x - mono[idx]+1) % mod;
    return (prefS[idx] + cnt % mod * (mono[idx] % mod) % mod) % mod;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll t;
    cin >> t;

    FOR(i, 1, 10) gen(i, i);
    mono.pb(0);
    
    sort(mono.begin(), mono.end());
    pre();
    while(t--){
        ll n,m;
        cin >> n >> m;

        cout << (S(m) - S(n-1) + mod) % mod << "\n";
    }
}