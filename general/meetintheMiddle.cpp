#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <climits>
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
#include <unordered_map>
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
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
// clang-format on
int main() {
#ifdef MIPPON_LOCAL
    auto begin = std::chrono::high_resolution_clock::now();
#endif
    ios::sync_with_stdio(false);
#ifndef MIPPON_LOCAL
    cin.tie(nullptr);
#endif

    // Meet in the middle
    // https://cses.fi/problemset/task/1628
    // when N is <= 40, this algo works
    // 2^40 is too big to calculate, so divide it by half
    // and the BS search

    // this Meet in the middle technique can solve the problem
    // "count subsequence where sum % K == 0" where N <= 40 using modular arthemethic
    // explanation is at the bottom of this page

    int N, X;
    cin >> N >> X;
    int left = N / 2;
    vector<int64_t> A, B;
    for (int i = 0; i < left; i++) {
        int x;
        cin >> x;
        A.push_back(x);
    }
    for (int i = left; i < N; i++) {
        int x;
        cin >> x;
        B.push_back(x);
    }
    vector<int64_t> l, r;

    auto power_set = [&](vector<int64_t> &p, bool flag = 1) -> void {
        for (int64_t msk = 0; msk < (1 << p.size()); ++msk) {
            int64_t add = 0;
            for (ll i = 0; i < (int64_t)p.size(); ++i)
                if (msk & (1 << i)) {
                    add += p[i];
                }
            if (flag == 0)
                r.push_back(add);
            if (flag == 1)
                l.push_back(add);
        }
    };
    power_set(A, 1);
    power_set(B, 0);
    sort(r.begin(), r.end());
    int64_t cnt = 0;
    for (int i = 0; i < sz(l); i++) {
        // when you are finding sum less than or equal to X
        // cnt += upper_bound(r.begin(), r.end(), X - l[i]) - r.begin();

        // when you are finding sum exactly X(CSES question was this method)
        // cnt += upper_bound(r.begin(), r.end(), X - l[i]) - lower_bound(r.begin(), r.end(), X - l[i]);
    }
    cout << cnt << endl;
    dbg(l, r);

#ifdef MIPPON_LOCAL
    auto end = std::chrono::high_resolution_clock::now();
    cerr << setprecision(4) << fixed;
    cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " seconds" << endl;
#endif

    return 0;
}

// "count subsequence where sum % K == 0" where N <= 40 using modular arthemethic
// example
// 6 3
// 1 2 3 3 6 1
// sum % K (K = 3) == 0
// we divide it half
// {1,2,3} ,   {3,6,1}
// call power set function twice
// get sum for each subset
// i,e)  {0} {1} {2} {3} {1,2} {1,3} {2,3} {1,2,3}
// SUM    0   1   2   3    3     4     5      6
// and we do % K for each and then store it to vector
// A[SUM%K]++,  B[SUM%K]++

// A =>  0 1 2 0 0 1 2 0
// A[0] = 4 , A[1] = 2 , A[2] = 2
// B[0] = 4,  B[1] = 4,  B[2] = 0

// for loop, if ( i== 0 ) it means sum % k == 0  for A and B
// we multiple to get total  A[0] * B[0] = 16
// else if idx i is 1 we need K-i = 2 idx, A[i] * B[X-i]
// so final answer is A[0] * B[0] = 16, A[1] * B[2] = 0, A[2] * B[1] = 8
// total 24 subsets

// int N, X;
//     cin >> N >> X;
//     int left = N / 2;
//     vector<int64_t> A, B;
//     for (int i = 0; i < left; i++) {
//          int x;
//          cin >> x;
//          A.push_back(x);
//     }
//     for (int i = left; i < N; i++) {
//          int x;
//          cin >> x;
//          B.push_back(x);
//     }
//     vector<int64_t> l(X), r(X);

//     auto power_set = [&](vector<int64_t> &p, bool flag = 1) -> void {
//          for (int64_t msk = 0; msk < (1 << p.size()); ++msk) {
//               int64_t add = 0;
//               for (ll i = 0; i < (int64_t)p.size(); ++i)
//                    if (msk & (1 << i)) {
//                         add += p[i];
//                    }
//               if (flag == 0) r[add % X]++; //important
//               if (flag == 1) l[add % X]++;
//          }
//     };
//     power_set(A, 1);
//     power_set(B, 0);
//     int64_t cnt = 0;
//     for (int i = 0; i < sz(l); i++) {
//          if (i == 0) {
//               cnt += l[i] * r[i];
//          } else {
//               cnt += l[i] * r[X - i];
//          }
//     }
//     cout << cnt << endl;
//     dbg(l, r);

// meet in the middle knapsack
int main() {
    ios::sync_with_stdio(false);
#ifndef MIPPON_LOCAL
    cin.tie(nullptr);
#endif

    int N;
    int64_t W;
    cin >> N >> W;
    vector<int64_t> value(N), weight(N);
    for (int i = 0; i < N; i++) {
        cin >> value[i] >> weight[i];
    }

    vector<int64_t> cl, cr;
    vector<int64_t> vl, vr;
    int M = N / 2;
    for (int i = 0; i < N; i++) {
        if (i < M) {
            cl.push_back(value[i]);
            vl.push_back(weight[i]);
        } else {
            cr.push_back(value[i]);
            vr.push_back(weight[i]);
        }
    }
    auto knapsack = [&](const vector<int64_t> &c, const vector<int64_t> &w, vector<pair<int64_t, pair<int64_t, int64_t>>> &S) -> void {
        int N = int(c.size());
        for (int64_t msk = 0; msk < (1 << N); msk++) {
            int64_t wei = 0;
            int64_t val = 0;
            for (int64_t i = 0; i < N; i++) {
                if (msk & (1 << i)) {
                    wei += w[i];
                    val += c[i];
                }
            }
            if (wei <= W) {
                S.push_back({val, {wei, 0}});
            }
        }
    };
    vector<pair<int64_t, pair<int64_t, int64_t>>> Sl, Sr; // {value,{weight,maxweight = 0}}
    knapsack(cl, vl, Sl);
    knapsack(cr, vr, Sr);
    sort(Sr.begin(), Sr.end());

    sort(Sr.begin(), Sr.end(), [](const pair<int64_t, pair<int64_t, int64_t>> &a, const pair<int64_t, pair<int64_t, int64_t>> &b) {
        return (a.second.first != b.second.first) ? a.second.first < b.second.first : a.first < b.first;
    });
    // return (a.weight != b.weight) ? a.weight < b.weight : a.value < b.value; });
    int64_t maxval = 0;
    for (auto &x : Sr) {
        maxval = max(maxval, x.first);
        x.second.second = maxval;
    }

    int64_t res = 0;
    for (auto &y : Sl) {
        for (int l = 0, r = int(Sr.size()) - 1; l <= r;) {
            int m = (l + r) >> 1;
            auto x = Sr[m];
            if (x.second.first + y.second.first <= W) {
                res = max(res, x.second.second + y.first);
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
    }

    cout << res << endl;
    // cout << ans << endl;
}
