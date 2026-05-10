#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll LIMIT=1000000000000000000LL;
vector<ll> mono;
void gen(ll cur,int last){
  mono.push_back(cur);
  for(int d=last; d<=9; ++d){
    if(cur>(LIMIT-d)/10) break;
    gen(cur*10+d,d);
  }
}
long long C(int n,int k){
  long long r=1;
  for(int i=1;i<=k;i++) r=r*(n-k+i)/i;
  return r;
}
int main(){
  for(int d=1;d<=9;d++) gen(d,d);
  sort(mono.begin(),mono.end());
  mono.erase(unique(mono.begin(),mono.end()),mono.end());
  vector<int> bylen(20);
  for(ll x:mono) bylen[to_string(x).size()]++;
  long long total=0,formula=0;
  for(int d=1;d<=18;d++){
    total += bylen[d];
    long long f=C(d+8,8);
    formula+=f;
    cout<<d<<" "<<bylen[d]<<" "<<f<<"\n";
  }
  cout<<"TOTAL "<<total<<" FORMULA "<<formula<<"\n";
}
