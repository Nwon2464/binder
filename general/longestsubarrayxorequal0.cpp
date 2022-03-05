#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
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
#define sfint(a) scanf("%d", &a)
// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }
auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);

// clang-format on
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     // Given array, you need to find longest subarrays or entire array that
     // equals to 0 variation of this problem can be as count subarrays with xor
     // as k
     vector<int> a = {4, 6, 1, 2, 3, 3, 1, 2, 4, 6};
     map<int, int> map;  // storing xor and index
     // O(n log N)
     int maxlen = 0;
     int prexor = 0;
     for (int i = 0; i < (int)a.size(); i++) {
          prexor = prexor ^ a[i];
          if (prexor ==
              0) {  // if prexor is 0 then from 0 to current index xor is 0.
               // which means it is maxlen. so we just get the len of it
               maxlen = i + 1;
          } else if (map.find(prexor) !=
                     map.end()) {  // if prexor is in the hash, then that index
                                   // +1 to current index is maxlen
               // {4,6}'s xor is 2
               // {4,6,1,2,3}'s xor is 2
               //      | | | xor should be 0 then. this is len
               maxlen = max(maxlen, i - map[prexor]);
          } else {  // we just xoring it
               map[prexor] = i;
          }
     }

     cout << maxlen;
     cout << map;
     return 0;
}
