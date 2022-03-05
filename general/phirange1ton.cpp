#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>

using namespace std;

using ll = long long;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define repp(i, a, b) for (int i = a; i <= (b); ++i)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on
vector<int> phi_1_to_n(int n) {
     vector<int> phi(n + 1);
     phi[0] = 0;
     phi[1] = 1;
     for (int i = 2; i <= n; i++) phi[i] = i;

     for (int i = 2; i <= n; i++) {
          if (phi[i] == i) {
               for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
          }
     }
     return phi;
}
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);

     // Euler's totient function, also known as phi-function ϕ(n), counts the
     // number of integers between 1 and n inclusive, which are coprime to n.
     // Two numbers are coprime if their greatest common divisor equals 1

     // If we need all the totient of all numbers between 1 and n, then
     // factorizing all n numbers is not efficient.
     // this is optimization for simple calculation of phi to get range all
     // numbers [1,n]

     // [1,2,3,4,5,6,7,8,9,10] just numbers
     // [1,1,2,2,4,2,6,4,6,4] how many primes range from [1,n]
     // suppose n = 5. which should satisfy Euler's totient function which says
     // that if n == prime, then  ϕ(n) = n - 1 , in this case n = 5, so 5 - 1 =
     // 4 (1,5) of gcd = 1 (2,5) of gcd = 1 (3,5) of gcd = 1 (4,5) of gcd = 1
     // total 4
     // gcd(p,q)=1 for all 1≤q<p.

     // O(nloglogn)

     //  n = 10
     //  [0,1,1,2,2,4,2,6,4,6,4,]
     int n;
     cin >> n;

     auto a = phi_1_to_n(n);
     cout << a;
}
