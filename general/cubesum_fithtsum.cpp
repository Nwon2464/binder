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
#define dbg(...) cerr <<"\e[38;5;214m" << "(" << #__VA_ARGS__ << "):" << "\e[39m", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
// clang-format on

// find a^3 + b^3 = x , x is given
// https://codeforces.com/contest/1490/problem/C
// x - a^3 = b^3
void run_case() {
     int64_t X;
     cin >> X;
     for (int64_t A = 1; A * A * A <= X; A++) {
          int64_t B3 = X - A * A * A;
          int64_t B = int64_t(round(pow(B3, 1.0 / 3)));

          if (B > 0 && B3 == B * B * B) {
               cout << "YES" << '\n';
               return;
          }
     }

     cout << "NO" << '\n';
}
// find a^3+b^3 = x , using map, easy to implement
// approach - find the range, this problem  1<= X <= 10^12
// since it is power of three(cube), and 10^(4 * 3) == 10^12
// 1 <= 10^4 is enough for A (fix A)
// if this doesnt work, increase range by *10

// and check to see if map has X - A^3. why? because A^3 + B^3 = X
// so B^3(what we are looking for) = X - A^3  (what we have it)
void run_case2() {
     int64_t X;
     cin >> X;
     // A2 + B2  = X
     map<int64_t, int64_t> mp;
     // fix A,  calculate A*A*A , store it
     for (int a = 1; a <= 10000; a++) mp[1LL * a * a * a] = a;
     for (auto x : mp) {
          int64_t a3 = x.first;
          // int64_t a = x.second;
          //
          if (mp.count(X - a3) && a3 > 0) {
               cout << "YES" << endl;
               return;
          }
     }
     cout << "NO" << endl;
}

// https://atcoder.jp/contests/abc166/tasks/abc166_d?lang=en
// find A^5 - B^5 = X where X<= 10^9
// then A^5 = X + B^5
void run_case1() {
     int64_t X;
     cin >> X;
     map<int64_t, int64_t> mp;
     for (int b = -1000; b <= 1000; b++) mp[1LL * b * b * b * b * b] = b;
     // dbg(mp);
     for (auto x : mp) {
          int64_t b5 = x.first;
          int64_t b = x.second;
          // finding A
          if (mp.count(X + b5)) {
               dbg(X, b5, b);
               int64_t A = mp[X + b5];
               cout << A << " " << b << endl;
               return;
          }
     }
}
int main() {
#ifdef MIPPON_LOCAL
     auto begin = std::chrono::high_resolution_clock::now();
#endif
     ios::sync_with_stdio(false);
#ifndef MIPPON_LOCAL
     cin.tie(nullptr);
#endif
     // int tests;
     // cin >> tests;

     // while (tests-- > 0)
     run_case1();

#ifdef MIPPON_LOCAL
     auto end = std::chrono::high_resolution_clock::now();
     cerr << setprecision(4) << fixed;
     cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count()
          << " seconds" << endl;
#endif

     return 0;
}