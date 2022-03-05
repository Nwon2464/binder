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

int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);

     // https://leetcode.com/problems/longest-increasing-subsequence/

     // O(NlogN) solution using Binary search
     vector<int> A = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };

     vector<int> res;
     // O(N LOG N)
     for (int i = 0; i < sz(A); i++) {
          auto d = lower_bound(res.begin(), res.end(), A[i]);
          if (d == res.end()) { // d is value not index . so it means
               // if d value which is greater or equal to A[i]  is not in res vector, we push it
               // suppose you have array 2 5 1 2 3 4
               // obviously LIS is 1 2 3 4
               // at first index A[0] = 2, we search it in res, not found greater or equal to 2 so push it
               // second index A[1] = 5 , we search it in res, not found greater or equal to 5 so push it
               // third index A[2] = 1, we search it in res, found greater or equal to 1, which is 2 at 0 index
               // so we delete or replace A[0] = 2 with 1 which results in [1,5]
               res.push_back(A[i]);
          } else {
               *d = A[i]; // it updates *d values with A[i] basically means,
               // throw off the current *d value and replace it with A[i] at position *d
          }
     }

     // [1,2,7,8,3,4,5,9,0]
     // 1 -> [1]
     // 2 -> [1,2]
     // 7 -> [1,2,7]
     // 8 -> [1,2,7,8]
     // 3 -> [1,2,3,8]  // we replaced 7 with 3, since for the longest sequence we need only the last number and 1,2,3 is our new shorter sequence
     // 4 -> [1,2,3,4] // we replaced 8 with 4, since the max len is the same but 4 has more chances for longer sequence
     // 5 -> [1,2,3,4,5]
     // 9 -> [1,2,3,4,5,9]
     // 0 -> [0,2,3,4,5,9] // we replaced 1 with 0, so that it can become a new sequence


     // O(N LOG N) another approah
     vector<int> res(N, 1e9);
     for(int i = 0; i  <N  ; i ++){
          auto itr = lower_bound(res.begin(), res.end(),A[i]);
          *itr = A[i];     
     }
     int res =0 ;
     for(auto x : A){
          if(x < 1e9){
               res++;
          }
     }
     cout << res << endl;



     // O(N^2) solution using DP
     vector<int> a = { 10, 9, 2, 5, 3, 7, 101, 18 };
     vector<int> dp(sz(a));
     for (int i = 0; i < sz(a); i++) {
          for (int j = 0; j < i; j++) {
               if (a[j] < a[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
               }
          }
     }
     int ans = 0;
     for (auto x : dp) {
          ans = max(ans, x);
     }
     cout << ans + 1 << el;
     return 0;
}
// clang-format on
