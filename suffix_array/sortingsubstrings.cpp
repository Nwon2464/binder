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
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

template <typename T, bool maximum_mode = false>
struct RMQ {
     int n = 0;
     vector<vector<T>> range_min;

     RMQ(const vector<T> &values = {}) {
          if (!values.empty()) build(values);
     }

     static int largest_bit(int x) { return 31 - __builtin_clz(x); }

     static T better(T a, T b) { return maximum_mode ? max(a, b) : min(a, b); }

     void build(const vector<T> &values) {
          n = int(values.size());
          int levels = largest_bit(n) + 1;
          range_min.resize(levels);

          for (int k = 0; k < levels; k++)
               range_min[k].resize(n - (1 << k) + 1);

          if (n > 0) range_min[0] = values;

          for (int k = 1; k < levels; k++)
               for (int i = 0; i <= n - (1 << k); i++)
                    range_min[k][i] =
                        better(range_min[k - 1][i],
                               range_min[k - 1][i + (1 << (k - 1))]);
     }

     T query_value(int a, int b) const {
          assert(0 <= a && a < b && b <= n);
          int level = largest_bit(b - a);
          return better(range_min[level][a],
                        range_min[level][b - (1 << level)]);
     }
};

template <typename T_string = string>
struct suffix_array {
     int n = 0;
     T_string str;
     vector<int> suffix;
     vector<int> rank;
     vector<int> lcp;
     RMQ<int> rmq;

     suffix_array() {}

     suffix_array(const T_string &_str, bool build_rmq = true) {
          build(_str, build_rmq);
     }

     void build(const T_string &_str, bool build_rmq = true) {
          str = _str;
          n = int(str.size());
          suffix.resize(n);

          for (int i = 0; i < n; i++) suffix[i] = i;

          bool large_alphabet = false;

          for (int i = 0; i < n; i++)
               if (str[i] < 0 || str[i] >= 128) large_alphabet = true;

          // Sort each suffix by the first character.
          if (large_alphabet) {
               sort(suffix.begin(), suffix.end(),
                    [&](int a, int b) { return str[a] < str[b]; });
          } else {
               vector<int> freq(128, 0);

               for (int i = 0; i < n; i++) freq[str[i]]++;

               for (int c = 1; c < 128; c++) freq[c] += freq[c - 1];

               for (int i = 0; i < n; i++) suffix[--freq[str[i]]] = i;
          }

          // Compute the rank of each suffix. Tied suffixes share the same rank.
          rank.resize(n);
          rank[suffix[0]] = 0;

          for (int i = 1; i < n; i++)
               rank[suffix[i]] = str[suffix[i]] == str[suffix[i - 1]]
                                     ? rank[suffix[i - 1]]
                                     : i;

          vector<int> next_index(n);
          vector<int> values(n);
          bool done = false;

          for (int len = 1; len < n && !done; len *= 2) {
               // next_index[i] = the next index to use for a suffix of rank i.
               // We insert them in order of the rank of the suffix that comes
               // len characters after the current suffix.
               for (int i = 0; i < n; i++) next_index[i] = i;

               // Compute the suffix array for 2 * len. Suffixes of length <=
               // len are prioritized first.
               for (int i = n - len; i < n; i++)
                    values[next_index[rank[i]]++] = i;

               for (int i = 0; i < n; i++) {
                    int prev = suffix[i] - len;

                    if (prev >= 0) values[next_index[rank[prev]]++] = prev;
               }

               swap(suffix, values);

               // Compute the rank array for 2 * len.
               values[suffix[0]] = 0;
               done = true;

               for (int i = 1; i < n; i++) {
                    int s = suffix[i], prev = suffix[i - 1];

                    if (s + len < n && prev + len < n &&
                        rank[s] == rank[prev] &&
                        rank[s + len] == rank[prev + len]) {
                         values[s] = values[prev];
                         done = false;
                    } else {
                         values[s] = i;
                    }
               }

               swap(rank, values);
          }

          compute_lcp();

          if (build_rmq) rmq.build(lcp);
     }

     void compute_lcp() {
          lcp.assign(n, 0);
          int match = 0;

          for (int i = 0; i < n; i++) {
               if (rank[i] == 0) continue;

               int a = suffix[rank[i]] + match;
               int b = suffix[rank[i] - 1] + match;

               while (a < n && b < n && str[a++] == str[b++]) match++;

               // lcp[r] = the longest common prefix length of the suffixes
               // starting at suffix[r] and at suffix[r - 1]. Note that lcp[0]
               // is always 0.
               lcp[rank[i]] = match;
               match = max(match - 1, 0);
          }
     }

     int get_lcp_from_ranks(int a, int b) const {
          if (a == b) return n - suffix[a];

          if (a > b) swap(a, b);

          return rmq.query_value(a + 1, b + 1);
     }

     int get_lcp(int a, int b) const {
          if (a >= n || b >= n) return 0;

          if (a == b) return n - a;

          return get_lcp_from_ranks(rank[a], rank[b]);
     }

     // Compares the substrings starting at `a` and `b` up to `length` in O(1).
     int compare(int a, int b, int length = -1) const {
          if (length < 0) length = n;
          // cout << "this is a : " << a << endl;
          // cout << "this is b : " << b << endl;

          if (a == b) return 0;

          int common = get_lcp(a, b);
          cout << "common : " << common << endl;
          if (common >= length) return 0;

          if (a + common >= n || b + common >= n)
               return a + common >= n ? -1 : 1;

          return str[a + common] < str[b + common]
                     ? -1
                     : (str[a + common] == str[b + common] ? 0 : 1);
     }
};

// Finds the longest substring common of two strings in O(L log L) where L is
// the combined length of the strings. When tied, returns the lexicographically
// minimal longest substring. Returns {string, vector of the two starting
// positions}.
pair<string, vector<int>> longest_common_substring(const string &S,
                                                   const string &T) {
     static const char SENTINEL = '$';
     assert(S.find(SENTINEL) == string::npos);
     assert(T.find(SENTINEL) == string::npos);
     int n = int(S.size());
     int m = int(T.size());
     suffix_array<string> SA(S + SENTINEL + T, false);
     int L = n + m + 1;
     // cout << SA.suffix << endl;
     // cout << SA.lcp << endl;
     auto &&which_string = [&](int index) { return index < n ? 0 : 1; };

     auto &&dist_from_start = [&](int index) {
          return index < n ? index : index - (n);
     };

     int best = -1;
     vector<int> positions = {-1, -1};

     for (int i = 1; i < L; i++) {
          int a = SA.suffix[i - 1], b = SA.suffix[i];

          if (which_string(a) != which_string(b) && SA.lcp[i] > best) {
               best = SA.lcp[i];
               positions[which_string(a)] = dist_from_start(a);
               positions[which_string(b)] = dist_from_start(b);
          }
     }

     string answer = S.substr(positions[0], best);
     return {answer, positions};
}
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);

     string S;
     int Q;
     cin >> S >> Q;
     vector<array<int, 2>> substrings(Q);

     for (auto &sub : substrings) {
          cin >> sub[0] >> sub[1];
          sub[0]--;
     }

     suffix_array<string> SA(S);  // rmq acivated
     cout << SA.lcp << endl;
     sort(substrings.begin(), substrings.end(),
          [&](array<int, 2> a, array<int, 2> b) {
               cout << a[1] << " " << a[0] << " " << b[1] << " " << b[0] << " ";
               int shorter = min(a[1] - a[0], b[1] - b[0]);
               cout << shorter;
               int comp = SA.compare(a[0], b[0], shorter);
               cout << " " << comp << endl;
               if (comp != 0) return comp < 0;

               if (a[1] - a[0] != b[1] - b[0]) return a[1] - a[0] < b[1] - b[0];

               return a < b;
          });

     for (auto &sub : substrings) cout << sub[0] + 1 << ' ' << sub[1] << '\n';
}

// 3,7   0,2   0,1    2,4   4,7   0,3
// 3

// abacaba a
// bacaba  aba
//  acaba  abacaba
//   caba  acaba
//    aba  ba
//     ba  bacaba
//      a  caba
