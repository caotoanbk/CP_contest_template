// check prime number <= N
vector<bool> isPrime(N+1, true);
isPrime[0] = isPrime[1] = false;
for (int i = 2; i * i <= N; i++) {
    if (isPrime[i]) {
        for (int j = i*i; j <= N; j += i)
            isPrime[j] = false;
    }
}

// Modular Exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// Always reduce fractions to avoid overflow and simplify logic.
int g = __gcd(a, b);
a /= g; b /= g;


//  Precompute Sieve + Smallest Prime Factors (SPF)
// Faster factorization than trial division after Sieve.
vector<int> spf(N+1);
void sieve() {
    for (int i = 0; i <= N; ++i) spf[i] = i;
    for (int i = 2; i*i <= N; ++i)
        if (spf[i] == i)
            for (int j = i*i; j <= N; j += i)
                if (spf[j] == j) spf[j] = i;
}

// Factorize n
vector<int> factorize(int n) {
    vector<int> factors;
    while (n > 1) {
        factors.push_back(spf[n]);
        n /= spf[n];
    }
    return factors;
}

// Use Fermat's Little Theorem for Modular Inverse
// a^(-1) ≡ a^(MOD-2) mod MOD
long long mod_inv(long long a, long long mod) {
    return mod_pow(a, mod - 2, mod); // Only if mod is prime
}

// Always divide before multiply to avoid overflow.
lcm(a, b) = a / gcd(a, b) * b

// Binary Exponentiation
// Use to compute large powers mod m in O(log b)
long long mod_pow(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

//  Modular Add/Subtract/Mul Safely
inline int mod_add(int a, int b, int m) { return (a + b) % m; }
inline int mod_sub(int a, int b, int m) { return (a - b + m) % m; }
inline int mod_mul(int a, int b, int m) { return 1LL * a * b % m; }

// ------------------------------
// Avoid nCr recomputation by precomputing fact[] and invFact[]
// Code: Precompute fact[] and invFact[]
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

long long fact[N], invFact[N];

// Modular exponentiation
long long mod_pow(long long a, long long b, int mod) {
    long long res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
void precompute() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < N; ++i)
        fact[i] = fact[i-1] * i % MOD;

    invFact[N-1] = mod_pow(fact[N-1], MOD - 2, MOD);  // Fermat's inverse
    for (int i = N - 2; i >= 1; --i)
        invFact[i] = invFact[i+1] * (i+1) % MOD;
}



