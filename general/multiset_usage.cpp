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

const int nax = 20;
void run() {
     int N, W;
     cin >> N >> W;
     multiset<int> st;

     for (int i = 0; i < N; i++) {
          int x;
          cin >> x;
          st.insert(x);
     }
     int ans = 0;
     while (!st.empty()) {
          int t = W;

          while (1) {
               auto it = st.upper_bound(t);
               // if iterator not found (upperbound always look for greater
               // iterator position. use it == st.begin() to make sure to break
               // the loop) {1,1,2,3} upper(1) or lowest val of upper points to
               // end
               if (it == st.begin()) break;
               --it;
               t -= *it;      //(val)
               st.erase(it);  //(iterator)
          }  // when erase in multiset, if you just put *it (val), whole
             // duplicate values are removed
          // if you want to one duplicate value to be removed, use iterator like
          // above
          ans++;
     }
     cout << ans << el;
}
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     // multiset can save duplicates
     multiset<int> mult;

     // it is sorted
     mult.insert(1);
     mult.insert(5);
     mult.erase(5);
     mult.erase(1);
     // mult.insert(5);
     // mult.insert(1);
     // mult.insert(3);
     // mult.insert(3);

     for (auto x : mult) {
          cout << x << endl;
     }
     // 1 1 3 3 5 5
     // int t;
     // cin >> t;
     // while (t--) {
     //      run();
     // }
}
