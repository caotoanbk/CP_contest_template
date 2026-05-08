#include <bits/stdc++.h>
using namespace std;

static vector<int> sieve_primes(int n){
    vector<int> primes; vector<bool> is(n+1,true); if(n>=0) is[0]=false; if(n>=1) is[1]=false;
    for(int i=2;i*i<=n;i++) if(is[i]) for(long long j=1LL*i*i;j<=n;j+=i) is[(int)j]=false;
    for(int i=2;i<=n;i++) if(is[i]) primes.push_back(i);
    return primes;
}

static bool is_prime_int(int x){
    if(x<2) return false; if(x%2==0) return x==2; for(int d=3;1LL*d*d<=x;d+=2) if(x%d==0) return false; return true;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    // Target minimum prime count across c_i
    int target = (n/3) - 1;
    if(target < 0) target = 0;

    // Available numbers
    std::set<int> avail; for(int i=1;i<=n;i++) avail.insert(i);
    vector<int> perm; perm.reserve(n);

    // Precompute primes up to n for target values
    vector<int> primes = sieve_primes(n);
    auto next_prime_ge = [&](long long x)->int{
        if(x <= 2) return 2;
        auto it = lower_bound(primes.begin(), primes.end(), (int)x);
        if(it==primes.end()) return primes.back();
        return *it;
    };

    long long S = 0; // prefix sum
    int made_prime = 0; // count of prime c_i achieved so far
    int i = 0; // number of elements placed

    auto get_extremes = [&](int k)->vector<int>{
        vector<int> out; out.reserve(2*k);
        // k smallest
        auto it = avail.begin();
        for(int t=0; t<k && it!=avail.end(); t++, ++it) out.push_back(*it);
        // k largest
        auto rit = avail.rbegin();
        for(int t=0; t<k && rit!=avail.rend(); t++, ++rit) out.push_back(*rit);
        return out;
    };

    auto try_make_even_prime = [&]()->bool{
        if((int)avail.size() < 2) return false;
        int i_new = i + 2; // target index after placing two numbers
        // Start with prime near current average
        long long avg_floor = (S + 0) / i_new; // floor
        int P = next_prime_ge(avg_floor);
        const int MAX_TRIES_P = 50; // try next few primes if needed
        for(int tP=0; tP<MAX_TRIES_P; tP++){
            long long L = 1LL*(P-1)*i_new - S + 1; // strict lower bound +1 for integer sums
            long long R = 1LL*P*i_new - S;         // inclusive upper bound
            if(R < 3){ P = next_prime_ge(P+1); continue; }
            if(L > 2LL*n - 1){ P = next_prime_ge(P+1); continue; }
            long long Lc = max<long long>(3, L);
            long long Rc = min<long long>(2LL*n-1, R);
            if(Lc > Rc){ P = next_prime_ge(P+1); continue; }
            // Try a handful of extremes for first element
            vector<int> candA = get_extremes(3);
            for(int a: candA){
                long long lowB = Lc - a;
                long long highB = Rc - a;
                if(lowB > n || highB < 1) continue;
                int lb = (int)max<long long>(1, lowB);
                int rb = (int)min<long long>(n, highB);
                // find b in [lb, rb] different from a
                auto it = avail.lower_bound(lb);
                if(it==avail.end()) continue;
                int b = *it;
                if(b==a){ ++it; if(it==avail.end()) continue; b = *it; }
                if(b >= lb && b <= rb){
                    // success
                    perm.push_back(a); perm.push_back(b);
                    avail.erase(a); avail.erase(b);
                    S += a + b;
                    i = i_new;
                    made_prime++;
                    return true;
                }
                // Also check next within range
                auto it2 = it; ++it2;
                if(it2!=avail.end()){
                    int bb = *it2; if(bb==a){ ++it2; if(it2==avail.end()) continue; bb = *it2; }
                    if(bb>=lb && bb<=rb){
                        perm.push_back(a); perm.push_back(bb);
                        avail.erase(a); avail.erase(bb);
                        S += a + bb;
                        i = i_new;
                        made_prime++;
                        return true;
                    }
                }
            }
            // Try swapping order: pick b extremes and solve for a
            vector<int> candB = get_extremes(3);
            for(int b: candB){
                long long lowA = Lc - b;
                long long highA = Rc - b;
                if(lowA > n || highA < 1) continue;
                int la = (int)max<long long>(1, lowA);
                int ra = (int)min<long long>(n, highA);
                auto it = avail.lower_bound(la);
                if(it==avail.end()) continue;
                int a = *it;
                if(a==b){ ++it; if(it==avail.end()) continue; a = *it; }
                if(a>=la && a<=ra){
                    perm.push_back(a); perm.push_back(b);
                    avail.erase(a); avail.erase(b);
                    S += a + b;
                    i = i_new;
                    made_prime++;
                    return true;
                }
            }
            P = next_prime_ge(P+1);
        }
        return false;
    };

    auto try_make_odd_prime = [&]()->bool{
        if(avail.empty()) return false;
        int i_new = i + 1;
        long long avg_floor = (S + 0) / i_new;
        int P = next_prime_ge(avg_floor);
        const int MAX_TRIES_P = 50;
        for(int tP=0;tP<MAX_TRIES_P;tP++){
            long long need = 1LL*P*i_new - S - 1; // p = need, since S + p = P*i - 1
            if(need < 1 || need > n){ P = next_prime_ge(P+1); continue; }
            auto it = avail.find((int)need);
            if(it!=avail.end()){
                int p = (int)need;
                perm.push_back(p);
                avail.erase(it);
                S += p;
                i = i_new;
                made_prime++;
                return true;
            }
            P = next_prime_ge(P+1);
        }
        return false;
    };

    while(!avail.empty()){
        bool done=false;
        // Prefer even-step prime constructions (2 numbers -> 1 prime count)
        if((int)avail.size() >= 2 && made_prime < target){
            done = try_make_even_prime();
            if(done) continue;
        }
        // Try odd-step prime construction if still below target
        if(made_prime < target){
            done = try_make_odd_prime();
            if(done) continue;
        }
        // Fallback: place arbitrary smallest to progress
        int x = *avail.begin();
        perm.push_back(x);
        avail.erase(avail.begin());
        S += x;
        i += 1;
    }

    // Output permutation
    for(int idx=0; idx<n; idx++){
        if(idx) cout << ' ';
        cout << perm[idx];
    }
    cout << "\n";

    // Optional: compute and print prime count for verification to stderr
    long long sum=0; int cntPrime=0;
    for(int idx=0; idx<n; idx++){
        sum += perm[idx];
        long long ci = (sum + (idx+1) - 1) / (idx+1);
        if(is_prime_int((int)ci)) cntPrime++;
    }
    cerr << "prime_count=" << cntPrime << ", target>=" << target << "\n";
    return 0;
}
