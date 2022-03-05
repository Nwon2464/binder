#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// PRIME NUMBER - Only having 2 factors (1,itself) == gcd(1,itset) == 1
// i.e)  2  => 1,2,  17 => 1,17
// COMPOSITE NUMBER (to be composite number, you have to have more than 2
// factors) i.e) 24 => 1,2,3,4,6,8,12,24 it has more factors than just 1 and
// itself NEITHER i.e) 1 => it only has 1 factor. to be prime number, it has to
// have 2 factors

// Sieve of Eratosthenes

// Sieve of Eratosthenes is an algorithm for finding all the prime numbers in a
// segment [1;n] using
// -------------------------
// Time Complexity         |
// O(nloglogn) operations. |
// O(n) for space          |
// -------------------------

// int n;
// vector<int> is_prime(n + 1, true); // when declaring int vector global, 10^7
// max size. inside function 10^6 is_prime[0] = is_prime[1] = false; for (int i
// = 2; i <= n; i++) {
//     if (is_prime[i] && (long long)i * i <= n) {
//         for (int j = i * i; j <= n; j += i)
//             is_prime[j] = false;
//     }
// }

// when n = 15 [is_prime:[0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0]]
//---------------------------------------------------------------------------------------------------

// global boolean or vector<char> is bit compression. you can store up to 10^8,
// vector<char> recommend
// const nax = 1e8 + 5;
// vector<char> is_prime(nax, 1); //global
// bool is_prime[nax + 1]; //global

// for (int i = 2; i * i <= nax; i++) {
//     if (is_prime[i]) {
//         for (int j = i * i; j <= nax; j+=i) {
//             is_prime[j] = 0;
//         }
//     }
// }

// ---------------------------------------------------------------------------------------------------
// Sieve of Eratosthenes Having Linear Time Complexity

// 10^7 for global, 10^6 for inside function and not greater.
// N should be 10^16 -> sqrt(10^16) = 10^8
// if time limit is 1.5sec then it is okay to use 10^8 for global array

const int nax = 1e7 + 1; // check what is maximum sqrt(N) ? seive max = 10000000 = 10^7

vector<int> smallest_factor;
vector<bool> prime;
vector<int> primes;

void sieve() {
    assert(nax >= 1);
    smallest_factor.assign(nax + 1, 0);
    prime.assign(nax + 1, true);
    prime[0] = prime[1] = false;
    primes = {};

    for (int p = 2; p <= nax; p++)
        if (prime[p]) {
            smallest_factor[p] = p;
            primes.push_back(p);

            for (int64_t i = int64_t(p) * p; i <= nax; i += p)
                if (prime[i]) {
                    prime[i] = false;
                    smallest_factor[i] = p;
                }
        }
}
// 6 = (2,1), (3,1)
vector<pair<int64_t, int>> prime_factorize(int64_t n) {
    int64_t sieve_max = int64_t(smallest_factor.size()) - 1;
    assert(1 <= n && n <= sieve_max * sieve_max);
    vector<pair<int64_t, int>> result;
    if (n <= sieve_max) {
        while (n != 1) {
            int64_t p = smallest_factor[n];
            int exponent = 0;
            while (n % p == 0) {
                n /= p;
                exponent++;
            }
            result.emplace_back(p, exponent);
        }
        return result;
    }

    for (int64_t p : primes) {
        if (p * p > n)
            break;
        if (n % p == 0) {
            result.emplace_back(p, 0);

            while (n % p == 0) {
                n /= p;
                result.back().second++;
            }
        }
    }

    if (n > 1)
        result.emplace_back(n, 1);

    return result;
}

// 6 = 1 ,2 , 3 ,6
vector<int64_t> generate_factors(const vector<pair<int64_t, int>> &prime_factors, bool sorted = false) {
    // See http://oeis.org/A066150 and http://oeis.org/A036451 for upper bounds on number of factors.
    static vector<int64_t> buffer;
    int product = 1;

    for (auto &pf : prime_factors)
        product *= pf.second + 1;

    vector<int64_t> factors = {1};
    factors.reserve(product);

    if (sorted)
        buffer.resize(product);

    for (auto &pf : prime_factors) {
        int64_t p = pf.first;
        int exponent = pf.second;
        int before_size = int(factors.size());

        for (int i = 0; i < exponent * before_size; i++)
            factors.push_back(factors[factors.size() - before_size] * p);

        if (sorted && factors[before_size - 1] > p)
            for (int section = before_size; section < int(factors.size()); section *= 2)
                for (int i = 0; i + section < int(factors.size()); i += 2 * section) {
                    int length = min(2 * section, int(factors.size()) - i);
                    merge(factors.begin() + i, factors.begin() + i + section, factors.begin() + i + section, factors.begin() + i + length,
                          buffer.begin());
                    copy(buffer.begin(), buffer.begin() + length, factors.begin() + i);
                }
    }

    assert(int(factors.size()) == product);
    return factors;
}

// ---------------------------------------------------------------------------------------------------
// another way to prime factors (printing version)

void printPrimeFactors(int n) {
    if (n <= 1)
        return;

    while (n % 2 == 0) {
        cout << 2 << " ";
        n = n / 2;
    }

    while (n % 3 == 0) {
        cout << 3 << " ";
        n = n / 3;
    }

    for (int i = 5; i * i <= n; i = i + 6) {
        while (n % i == 0) {
            cout << i << " ";
            n = n / i;
        }

        while (n % (i + 2) == 0) {
            cout << (i + 2) << " ";
            n = n / (i + 2);
        }
    }

    if (n > 3)
        cout << n << " ";

    cout << endl;
}

int main() {
    int n = 450;

    printPrimeFactors(n);

    return 0;
}

//---------------------------------------------------------------------------------
// segmented prime
// [L,R] of small size (e.g. R−L+1≈1e7)
// where R can be very large (e.g. 1e12).
// https://www.spoj.com/problems/PRIME1/
// constraints : m and n (1 <= m <= n <= 1000000000, n-m<=100000)
// approach : store n-m possible prime check => calculate n,m => range(1,10)
// [0,1,1,0,1,0,1,....]

vector<bool> segmentedSieve(long long L, long long R) {
    // generate all primes up to sqrt(R)
    long long lim = sqrt(R);
    vector<bool> mark(lim + 1, false);
    vector<long long> primes;
    for (long long i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (long long j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vector<bool> isPrime(R - L + 1, true);
    for (long long i : primes)
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;
    return isPrime;
}

int main() {
    ll n, m;
    cin >> n >> m;

    auto a = segmentedSieve(n, m);
    ll x = n;
    for (int i = 0; i <= m - n; i++) {
        if (a[i] == 1) {
            cout << x << "\n";
        }
        x++;
    }
}
// test case
// 2
// 1 10  [1,.....10] printing 2,3,5,7,...
// 3 5
//----------------------------------------------------------------------------------

// Miller-Rabin primality test
// intentionally using unsigned
// codeforces 725 D tested

unsigned pow_mod(unsigned a, unsigned b, unsigned mod) {
    unsigned result = 1;

    while (b > 0) {
        if (b & 1)
            result = unsigned(uint64_t(result) * a % mod);

        a = unsigned(uint64_t(a) * a % mod);
        b >>= 1;
    }

    return result;
}

bool miller_rabin(int64_t n) {
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    // small prime check
    for (unsigned p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29})
        if (n % p == 0)
            return n == p;

    int64_t d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Testing_against_small_sets_of_bases
    for (unsigned a : {2, 7, 61}) {
        if (n <= a)
            break;
        int64_t t = d;
        int64_t y = pow_mod(a, t, n); // over
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = __int128_t(y) * y % n; // flow
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}

// prime at-sh sieve

#include <assert.h>
#include <bitset>
#include <cassert>
#include <iostream>
#include <numeric>
#include <stdio.h>
#include <vector>
using namespace std;

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}

void dbg_out() {
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef MIPPON_LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

using std::bitset;

// Sieve <= lim (<= LIM_SIEVE)
// isPrime[n]: 2 n + 1
constexpr int LIM_SIEVE = 500'000'010;
bitset<((LIM_SIEVE + 1) >> 1)> is_prime;
vector<int> primes;
void sieve_at_kin(int64_t lim) {
    // when you solve segment sieve problem, be sure to make limit to be sqrt(limit)
    // otherwise, ignore it.
    // lim = sqrt(lim)

    assert(lim <= LIM_SIEVE);
    int64_t N = lim;
    lim = (lim + 1) >> 1;
    // n == 1, 5 (mod 4): 4 x^2 + y^2
    //   x == 0 (mod 3), y == 1, 5 (mod 6)
    //   x == 1, 2 (mod 3), y == 1 (mod 2)
    for (int y = 1, m; (m = (y * y + 36) >> 1) < lim; y += 2) {
        if (y % 3 != 0) {
            for (int k = 0; m < lim; m += (k += 36) + 18)
                is_prime.flip(m);
        }
    }
    for (int x = 1, m; (m = (4 * x * x + 1) >> 1) < lim; ++x) {
        if (x % 3 != 0) {
            for (int k = 0; m < lim; m += (k += 4))
                is_prime.flip(m);
        }
    }
    // n == 7 (12): 3 x^2 + y^2
    //   x == 1 (2), y == 2, 4 (6)
    for (int y = 2, m; (m = (y * y + 3) >> 1) < lim; y += 2) {
        if (y % 3 != 0) {
            for (int k = 0; m < lim; m += (k += 12))
                is_prime.flip(m);
        }
    }
    // n == 11 (12): 3 x^2 - y^2 (x > y)
    //   x == 0 (2), y == 1, 5 (6)
    //   x == 1 (2), y == 2, 4 (6)
    for (int y = 1, m; (m = ((2 * y + 6) * y + 3) >> 1) < lim; ++y) {
        if (y % 3 != 0) {
            for (int k = 6 * y; m < lim; m += (k += 12))
                is_prime.flip(m);
        }
    }
    // non square-free
    for (int p = 5, p2; (p2 = p * p) >> 1 < lim; p += 2) {
        if (is_prime[p >> 1]) {
            for (int m = p2 >> 1; m < lim; m += p2)
                is_prime.reset(m);
        }
    }
    // 3
    if (1 < lim)
        is_prime.set(1);

    primes.push_back(2); // edge cases for sieve-at-kin
    for (int n = 3; n <= N; n += 2) {
        if (is_prime[n >> 1]) {
            primes.push_back(n);
        }
    }
}

// same as prime sieve, but more fast in large scale
// sieveOfAtkin
// edge case is 2 is not included, so size is always - 1
int main() {

    int64_t N;
    cin >> N;
    sieve_at_kin(N);
    cout << primes.size() << endl;
    return 0;
}