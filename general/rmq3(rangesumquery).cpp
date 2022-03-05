#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>

using namespace std;

using ll = long long;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define f first
#define s second
#define pb push_back
const char el = '\n';

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

// st[here][] means biggest possible array length
// st[][here] means 2 ^ array length
// this is also same as prefix sum
const int MAXN = 100005;
const int K = 25;
ll st[MAXN][K + 1];
void build(vector<int> A) {
     int N = sz(A);
     for (int i = 0; i < N; i++)
          st[i][0] = A[i];

     for (int j = 1; j <= K; j++)
          for (int i = 0; i + (1 << j) <= N; i++)
               st[i][j] = st[i][j - 1] + st[i + (1 << (j - 1))][j - 1];
}
ll sum(int L, int R) {
     ll sum = 0;
     for (int j = K; j >= 0; j--) {
          if ((1 << j) <= R - L + 1) {
               sum += st[L][j];
               L += 1 << j;
          }
     }
     return sum;
}
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     vector<int> A = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
     build(A);
     int L, R;
     cin >> L >> R;
     cout << sum(L, R) << el;
}
