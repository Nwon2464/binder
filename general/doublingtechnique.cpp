#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
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

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename T_vector> void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef MIPPON_LOCAL
#define dbg(...) cerr <<"\e[38;5;196m" << "(" << #__VA_ARGS__ << "):" << "\e[39m", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
// clang-format on

const int nax = 62;
const int MAX_N = 2e5 + 5;
vector<vector<int>> A(nax, vector<int>(MAX_N));

// doubling technique
// https://atcoder.jp/contests/abc167/tasks/abc167_d
void solve() {
     int N;
     int64_t K;
     cin >> N >> K;
     for (int i = 0; i < N; i++) {
          cin >> A[0][i];
          A[0][i]--;
     }
     for (int i = 0; i < nax - 1; i++) {
          // dont forget ranging from (i , nax - 1) since we push A[i+1][j] at
          // second for loop
          for (int j = 0; j < N; j++) {
               A[i + 1][j] = A[i][A[i][j]];  // A[i][j] collects current val, A[i][A[i][j]] collects next vals
          }
     }
     int64_t val = 0;
     for (int d = nax - 1; d >= 0; d--) {
          int64_t tmp = 1LL << d;
          if (tmp <= K) {
               K -= tmp;
               val = A[d][val];
          }
     }
     cout << val + 1 << endl;
}
int main() {
#ifdef MIPPON_LOCAL
     auto begin = std::chrono::high_resolution_clock::now();
#endif
     ios::sync_with_stdio(false);
#ifndef MIPPON_LOCAL
     cin.tie(nullptr);
#endif
     solve();

#ifdef MIPPON_LOCAL
     auto end = std::chrono::high_resolution_clock::now();
     cerr << setprecision(4) << fixed;
     cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count()
          << " seconds" << endl;
#endif

     return 0;
}