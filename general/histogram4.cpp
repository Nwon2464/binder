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
#include <stack>
#include <vector>
using namespace std;

using ll = long long;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
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

// very well known problem. histogram problem, orange problem

// it can be solved with brute force(n^2) only if constraints 10^4, union find(any constraints), stack O(n).

// https://atcoder.jp/contests/abc189/tasks/abc189_c (Mandarin Orange)
// https://leetcode.com/problems/largest-rectangle-in-histogram/ (Largest Rectangle Histogram)
// https://www.codechef.com/problems/SPC1704 (Histogram)

// This implementation O(nlogn) it works for any case Union Find Version

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
#define all(x) x.begin(), x.end()
#define F0R(i, a) for (int i = 0; i < (a); i++)
const int MX = 100001;
template <int SZ>
struct DSU {
     int parent[SZ], size[SZ];
     ll num[SZ];

     DSU() {
          F0R(i, SZ)
          parent[i] = i,
          size[i] = 0, num[i] = 1;
     }

     int get(int x) {
          if (parent[x] != x) parent[x] = get(parent[x]);
          return parent[x];
     }

     void unify(int x, int y) {
          x = get(x);
          y = get(y);
          if (x == y) return;
          if (size[x] < size[y]) swap(x, y);
          if (size[x] == size[y]) size[x]++;
          num[x] += num[y];
          parent[y] = x;
     }
};
void solve() {
     DSU<MX> dsu;
     int N;
     cin >> N;
     vpi A(N);
     F0R(i, N)
     cin >> A[i].f;
     F0R(i, N)
     A[i].s = i;
     sort(all(A));
     reverse(all(A));
     bool in[N];
     F0R(i, N)
     in[i] = false;
     ll ans = 0;
     F0R(i, N) {
          int a = A[i].s;
          in[a] = true;
          if (a > 0 && in[a - 1]) {
               dsu.unify(a, a - 1);
          }
          if (a < N - 1 && in[a + 1]) {
               dsu.unify(a, a + 1);
          }
          ckmax(ans, dsu.num[dsu.get(a)] * ((ll)A[i].f));
     }
     cout << ans << "\n";
}

int main() {
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     solve();
}
