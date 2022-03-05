#include <algorithm>
#include <array>
#include <bitset>
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
#define rep(i, a, b) for (ll i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define f first
#define s second
#define pb push_back

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

// const ll template_array_size = 1e6 + 4265;
// ll a[template_array_size];
// ll b[template_array_size];
// ll c[template_array_size];

int main() {
     // http://poj.org/problem?id=2825
     // A permutation of 1..n {An} is called a Perfect Permutation if the sequence {|Ai − i|} is a permutation of 0..(n − 1).
     // For example, {3, 2, 4, 1} is a perfect permutation for {2, 0, 1, 3} is a permutation of 0..3.
     // Given an integer n, your mission is to find a perfect permutation of 1..n.

     int N, k;
     while (scanf("%d", &N) == 1) {
          if (N % 4 == 0) {
               k = N / 4;
               printf("%d ", 2 * k + 1);
               for (int i = 4 * k; i >= 3 * k + 2; i--)
                    printf("%d ", i);
               for (int i = 3 * k; i >= 2 * k + 2; i--)
                    printf("%d ", i);
               for (int i = 2 * k; i >= k + 1; i--)
                    printf("%d ", i);
               printf("%d ", 3 * k + 1);
               for (int i = k; i >= 1; i--)
                    printf("%d ", i);
          } else if (N % 4 == 1) {
               k = (N - 1) / 4;
               printf("%d ", 4 * k + 1);
               for (int i = 4 * k; i >= 3 * k + 2; i--)
                    printf("%d ", i);
               for (int i = 3 * k; i >= 2 * k + 2; i--)
                    printf("%d ", i);
               for (int i = 2 * k; i >= k + 1; i--)
                    printf("%d ", i);
               if (k) printf("%d ", 3 * k + 1);
               for (int i = k; i >= 1; i--)
                    printf("%d ", i);
               if (k) printf("%d ", 2 * k + 1);
          } else {
               printf("0");
          }
          putchar('\n');
     }
     return 0;
}