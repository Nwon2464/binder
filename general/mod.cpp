
// clang-format off

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Mod arithmetic addition,substraction,division, multiplecation
// binaryexponential, modinverse

/*
Modular Arithmetic
Sometimes, the answer to a problem is a very large number,
it suffices to use the types int and long long
(a + b) mod m = (a mod m + b mod m) mod m
(a − b) mod m = (a mod m − b mod m) mod m
(a · b) mod m = (a mod m · b mod m) mod m

division is not possible (we need mod inverse)
(a / b) mod m = (a mod m / b mod m) mod m is WRONG


what if a remainder is negative?
An easy way to make sure there are no negative remainders is to first calculate the
remainder as usual and then add m if the result is negative:
x = x%m;
if (x < 0) x += m;
However, this is only needed when there are subtractions in the code, and the
remainder may become negative
*/
// ------------------------------------------------------------------------------

const int MOD = 1e9 + 7;
int print_mod(int a) { return (a % MOD + MOD) % MOD; }
int mul(int a, int b){return (1LL * a * b) % MOD;}
int add(int a, int b){int s = (a + b);if (s >= MOD)s -= MOD; return s;}
int sub(int a, int b){int s = (a + MOD - b);if (s >= MOD)s -= MOD;return s;}
int binpow(int a, ll deg){if (deg == 0) return 1;if (deg % 2 == 1) return mul(a, binpow(a, deg - 1)); int t = binpow(a, deg / 2); return mul(t, t);}
int inv(int n){return binpow(n, MOD - 2);}


/*when binpower is too big*/
// https://www.spoj.com/problems/PON/   -  Prime or Not
using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod)
{
    //integer range [2 <= N <= 2^63-1] can be AC
    //                       = 9*10^18
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = (u128)result * base % mod;
        }
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

//regular binpow
using ll = long long;

ll binpower(ll a, ll b, ll mod)
{
    a %= mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// clang-format on
