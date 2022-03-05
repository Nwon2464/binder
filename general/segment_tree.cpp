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
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define f first
#define s second
#define pb push_back
#define endl "\n"

// clang-format off
// template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }


void xout_out() { cerr << endl; }
template<typename Head, typename... Tail> void xout_out(Head H, Tail... T) { cerr << ' ' << H; xout_out(T...); }
#define xout(...) cerr << "(" << #__VA_ARGS__ << "):", xout_out(__VA_ARGS__)

// clang-format on

const int INF = 10000000;
struct segment_tree {
     int N;
     vector<int> mn, mx;
     segment_tree(vector<int> A) {
          int N2 = A.size();
          N = 1;
          while (N < N2) {
               N *= 2;
          }
          mn = vector<int>(N * 2 - 1, INF);
          mx = vector<int>(N * 2 - 1, -INF);
          for (int i = 0; i < N2; i++) {
               mn[N - 1 + i] = A[i];
               mx[N - 1 + i] = A[i];
          }
          for (int i = N - 2; i >= 0; i--) {
               mn[i] = min(mn[i * 2 + 1], mn[i * 2 + 2]);
               mx[i] = max(mx[i * 2 + 1], mx[i * 2 + 2]);
          }
     }
     void update(int p, int x) {
          p += N - 1;
          mn[p] = x;
          mx[p] = x;
          while (p > 0) {
               p = (p - 1) / 2;
               mn[p] = min(mn[p * 2 + 1], mn[p * 2 + 2]);
               mx[p] = max(mx[p * 2 + 1], mx[p * 2 + 2]);
          }
     }
     pair<int, int> range_minmax(int L, int R, int i, int l, int r) {
          if (r <= L || R <= l) {
               return make_pair(INF, -INF);
          } else if (L <= l && r <= R) {
               return make_pair(mn[i], mx[i]);
          } else {
               int m = (l + r) / 2;
               pair<int, int> A = range_minmax(L, R, i * 2 + 1, l, m);
               pair<int, int> B = range_minmax(L, R, i * 2 + 2, m, r);
               return make_pair(min(A.first, B.first), max(A.second, B.second));
          }
     }
     bool range_same(int L, int R, int x) {
          if (L == R) {
               return true;
          }
          pair<int, int> P = range_minmax(L, R, 0, 0, N);
          return P.first == x && P.second == x;
     }
};