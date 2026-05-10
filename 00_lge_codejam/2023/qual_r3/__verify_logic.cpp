#include <bits/stdc++.h>
using namespace std; using ll=long long;
const ll LIMIT=1000000000000000000LL; const ll MOD=1000000007LL;
vector<ll> mono,pref;
void gen(ll cur,int last){ mono.push_back(cur); for(int d=last;d<=9;d++){ if(cur>(LIMIT-d)/10) break; gen(cur*10+d,d);} }
bool ok(ll x){ string s=to_string(x); for(int i=1;i<(int)s.size();i++) if(s[i-1]>s[i]) return false; return true; }
ll bruteSx(ll x){ while(!ok(x)) --x; return x; }
void build(){ for(int d=1;d<=9;d++) gen(d,d); mono.push_back(0); sort(mono.begin(),mono.end()); mono.push_back(LIMIT+1); pref.assign(mono.size(),0); for(size_t i=0;i+1<mono.size();i++){ ll len=(mono[i+1]-mono[i])%MOD; pref[i+1]=(pref[i]+(mono[i]%MOD)*len)%MOD; } }
ll fastPref(ll x){ if(x<0) return 0; int idx=upper_bound(mono.begin(),mono.end(),x)-mono.begin()-1; ll cnt=(x-mono[idx]+1)%MOD; return (pref[idx]+(mono[idx]%MOD)*cnt)%MOD; }
int main(){ build();
  mt19937_64 rng(1);
  for(int t=0;t<2000;t++){
    ll x=rng()%1000000;
    ll fs=bruteSx(x);
    int idx=upper_bound(mono.begin(),mono.end(),x)-mono.begin()-1;
    if(mono[idx]!=fs){ cout<<"Mismatch S(x) at "<<x<<" "<<mono[idx]<<" "<<fs<<"\n"; return 0; }
  }
  for(int t=0;t<200;t++){
    ll l=rng()%20000, r=rng()%20000; if(l>r) swap(l,r);
    ll b=0; for(ll x=l;x<=r;x++) b=(b+bruteSx(x))%MOD;
    ll f=(fastPref(r)-fastPref(l-1)+MOD)%MOD;
    if(b!=f){ cout<<"Mismatch range "<<l<<" "<<r<<" "<<b<<" "<<f<<"\n"; return 0; }
  }
  cout<<"OK"<<"\n";
}
