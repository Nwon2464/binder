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
#define repp(i, a, b) for (int i = a; i <= (b); ++i)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

void solve() {
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // find all the subsets of the array
    // power set problem. time complexity O(2^n * n)
    // variation of this problem is to remove duplicate
    // https://leetcode.com/problems/subsets/

    // this would only work if constraint is n <= 20
    // why? because suppose max n = 20, 2^20 = 1048576 , 1048576 * 20(inner) =
    // 20971520 near about 2 * 10 ^ 7.
    // maximum possible time complexity is O(10^7) while constraints is n
    // <= 20.
    vector<int> p = {1, 2, 3};
    // vector<int> p = {1, 1, 1, 1, 1};
    vector<vector<int>> ans;
    for (ll msk = 0; msk < (1 << p.size()); ++msk) { // O(2^n)
        vector<int> temp;
        for (ll i = 0; i < (ll)p.size(); ++i) { // O(n)
            if (msk & (1 << i)) {
                // when solving traveling salesmen problem,recommend to use (msk >> i) & 1
                // because  TSP(traveling salemsent problem) constraint is always small like 15 or sometimes 40,
                // if you do  1 << 40 this is overflow. so it is safe to use (msk >> i) & 1
                temp.push_back(p[i]);
            }
        }
        ans.push_back(temp);
    }
    cout << ans.size();
    // ll sum = 0;
    // for (ll msk = 1; msk < (1 << p.size()); ++msk) {
    //      double mult = 1;
    //      ll bits = 0;
    //      for (ll i = 0; i < (ll)p.size(); ++i)
    //           if (msk & (1 << i)) {
    //                ++bits;
    //                mult *= p[i];
    //           }

    //      ll cur = r / (ll)mult;
    //      if (bits % 2 == 1)
    //           sum += cur;
    //      else
    //           sum -= cur;
    // }
}
