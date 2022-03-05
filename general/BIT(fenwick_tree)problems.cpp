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

template <typename T>
struct BIT {
    // each function has an independant functionality.
    // no functions are communicated one another except
    // one_baesd_idx and N

    int N;
    vector<T> values;
    vector<T> one_based_idx; // one_based_indexing
    // vector<T> fenwick;
    BIT(const vector<T> &_values = {}) {
        if (!_values.empty()) {
            values = _values;
            one_based_index(_values);
        }
    }
    void one_based_index(const vector<T> &_values) {
        N = _values.size();
        one_based_idx.assign(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            one_based_idx[i] = _values[i - 1];
        }
    }
    void build_fenwick() {
        // fenwick tree
        vector<T> fenwick;
        fenwick.assign(N + 1, 0);

        auto update = [&](int i, T delta) -> void {
            // add, stair_case up approach
            while (i <= N) {
                fenwick[i] += delta;
                i += i & -i;
            }
        };
        auto sum = [&](int i) -> int {
            // query, stair_case bottom approach
            T ans = 0;
            while (i > 0) {
                ans += fenwick[i];
                i -= i & -i;
            }
            return ans;
        };
        auto range_sum = [&](int i, int j) -> int { return sum(j) - sum(i - 1); };

        for (int i = 1; i <= N; i++) {
            update(i, one_based_idx[i]);
        }
    }
    void build_inversion_n() {
        // tested : https://www.spoj.com/problems/INVCNT/
        // O(n log(size of N))
        // converting is only work when range is large say up to 10^9 or negative vals
        // process negative val as well {7, -90, 100, 1}
        // convert the given array to an array with values from 1 to n
        // {7, -90, 100, 1} converts to {3, 1, 4 , 2}

        vector<T> temp = values;
        vector<T> fenwick;
        fenwick.assign(N + 1, 0);
        auto convert = [&](vector<int> &vals) -> vector<int> {
            vector<int> B = vals;
            sort(B.begin(), B.end());
            B.erase(unique(B.begin(), B.end()), B.end());

            // {-90, 1 , 7 , 100}
            for (int i = 0; i < N; i++) {
                int idx = lower_bound(B.begin(), B.end(), vals[i]) - B.begin() + 1;
                vals[i] = idx;
            }
            return vals;
        };

        convert(temp);

        auto update = [&](int i, T delta) -> void {
            // add, stair_case up approach
            while (i <= N) {
                fenwick[i] += delta;
                i += i & -i;
            }
        };
        auto sum = [&](int i) -> int {
            // query, stair_case bottom approach
            T ans = 0;
            while (i > 0) {
                ans += fenwick[i];
                i -= i & -i;
            }
            return ans;
        };
        vector<int> non_negatives(N + 1); // one-based-indexing array
        for (int i = 1; i <= N; i++) {
            non_negatives[i] = temp[i - 1];
        }
        int64_t cnt_inversions = 0;
        for (int i = N; i >= 1; i--) {
            cnt_inversions += sum(non_negatives[i] - 1);
            update(non_negatives[i], 1);
        }
        cout << cnt_inversions << endl;
    }
    void build_inversion_mx() {
        // converting is only work when range is greater than 10^7
        // tested : https://www.spoj.com/problems/INVCNT/
        // O(n log (max element))
        // how many inversions above me, if so, cnt

        // cons : cannot process negative vals such as {7, -90, 100, 1}
        int64_t mx = *max_element(one_based_idx.begin(), one_based_idx.end());
        vector<T> fenwick;
        fenwick.assign(mx + 1, 0);

        auto update = [&](int i, T delta) -> void {
            // add, stair_case up approach
            while (i <= mx) {
                fenwick[i] += delta;
                i += i & -i;
            }
        };
        auto sum = [&](int i) -> int {
            // query, stair_case bottom approach
            T ans = 0;
            while (i > 0) {
                ans += fenwick[i];
                i -= i & -i;
            }
            return ans;
        };
        int64_t inversions = 0;
        for (int i = 1; i <= N; i++) {
            inversions += sum(mx) - sum(one_based_idx[i]);
            update(one_based_idx[i], 1);
        }
        cout << inversions << endl;
    }
    int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }
    int binary_lifting_technique(int k) {
        // codeforces D : multiset
        // https://codeforces.com/contest/1354/status
        // time complexity O(n log n) solution binary lifting technique
        int N, Q;
        cin >> N >> Q;
        vector<int> A(N);
        for (auto &x : A)
            cin >> x;

        vector<int> BIT(N + 1);
        auto sum = [&](vector<int> &fenwick, int i) -> int {
            int total = 0;
            while (i > 0) {
                total += fenwick[i];
                i -= i & -i;
            }
            return total;
        };
        auto update = [&](vector<int> &fenwick, int i, int delta) -> void {
            while (i <= N) {
                fenwick[i] += delta;
                i += i & -i;
            }
        };

        // auto convert = [&](vector<int> &vals) -> vector<int> {
        //      vector<int> B = vals;
        //      sort(B.begin(), B.end());
        //      for (int i = 0; i < N; i++) {
        //           int idx = lower_bound(B.begin(), B.end(), vals[i]) - B.begin() + 1;
        //           vals[i] = idx;
        //      }
        //      return vals;
        // };

        // convert(A);

        for (int i = 0; i < N; i++) {
            update(BIT, A[i], 1);
        }

        // this search function is binary lifting technique
        // https://codeforces.com/blog/entry/61364
        auto search = [&](vector<int> &BIT, int k) -> int {
            int sum = 0;
            int pos = 0;
            int bit = largest_bit(N);
            for (int i = bit; i >= 0; i--) {
                if (pos + (1 << i) < N && sum + BIT[pos + (1 << i)] < k) {
                    sum += BIT[pos + (1 << i)];
                    pos += (1 << i);
                }
            }
            return pos + 1;
        };

        for (int i = 0; i < Q; i++) {
            int x;
            cin >> x;
            if (x < 0) { // delete
                int t = -x;
                int aa = search(BIT, t);
                update(BIT, aa, -1);
            } else {
                // isnert
                update(BIT, x, 1);
            }
        }
        if (sum(BIT, N) == 0)
            cout << 0 << endl;
        else {
            int res = 0;
            for (int i = 1; i <= N; i++) {
                if (sum(BIT, i) > 0) {
                    res = i;
                    break;
                }
            }
            cout << res << endl;
        }
    }
    int find_kth_tallest_person(int k) {
        // O(n(log^2 N))
        // https://codeforces.com/blog/entry/61364 binary lifting technique
        // we can short it down to O(n log n ) using binary lifting technique

        //  1 2 3  4   5 6  => index && height (height 1cm, height 2cm,... 6cm)
        // [8,2,10,100,1,2] => number of people
        // find 121-th tallest person is height of 5 (index 5)

        vector<T> fenwick(N + 1, 0);

        auto sum = [&](int i) -> int64_t {
            int64_t total = 0;
            while (i > 0) {
                total += fenwick[i];
                i -= i & -i;
            }
            return total;
        };

        auto update = [&](int i, int delta) -> void {
            while (i <= N) {
                fenwick[i] += delta;
                i += i & -i;
            }
        };
        for (int i = 1; i <= N; i++) {
            update(i, one_based_idx[i]);
        }
        // time complexity O(n log^2 n), this is too strict, can't use long long sometimes
        int l = 0, r = values.size();
        while (l < r) {
            int mid = (l + r) / 2;
            if (k <= sum(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }

    int64_t find_triplets_inversion_n2() {
        // this problem is same as "count increasing subsequences of length 3"
        // oppositie inversion a[i] < a[j] < a[k] and i < j < k
        // O(n^2)
        // point : you set an a[j] as a middle element
        // then a[i] < a[j] && a[j] < a[k]

        // another opposite inverion a[i] > a[j] > a[k] and i > j > k
        // is just to change A[i] > A[j], A[j] > A[k]
        vector<int> A = {1, 2, 3, 4};
        int N = A.size();
        int cnt = 0;
        for (int j = 1; j < N; j++) {
            int greater = 0;
            for (int i = 0; i < j; i++) {
                if (A[i] < A[j]) {
                    greater++;
                }
            }
            int smaller = 0;
            for (int k = j + 1; k < N; k++) {
                if (A[j] < A[k]) {
                    smaller++;
                }
            }
            cnt += (greater * smaller);
        }
        return cnt;
    }
    int64_t find_triplets_right() {
        // O(N log(N))
        // O(N^2) is written above function called "find_triplets_n2" for understanding purpose.
        // https://practice.geeksforgeeks.org/problems/magic-triplets4003/1#
        // a[i] < a[j] < a[k] and i < j < k
        // opposite inversion 3 elements
        vector<int> A = {4, 3, 2, 1};
        vector<int> B = A;
        int N = A.size();

        sort(B.begin(), B.end());
        B.erase(unique(B.begin(), B.end()), B.end());
        for (int i = 0; i < N; i++) {
            int idx = lower_bound(B.begin(), B.end(), A[i]) - B.begin() + 1;
            A[i] = idx;
        }
        vector<int> one_index(N + 1);

        for (int i = 1; i <= N; i++) {
            one_index[i] = A[i - 1];
        }
        vector<int> fenwick(N + 1);

        auto sum = [&](int i) -> int64_t {
            int64_t total = 0;
            while (i > 0) {
                total += fenwick[i];
                i -= i & -i;
            }
            return total;
        };

        auto update = [&](int i, int delta) -> void {
            while (i <= N) {
                fenwick[i] += delta;
                i += i & -i;
            }
        };

        // find from last, whose cost is less than current val
        vector<int64_t> ans(N + 1);

        for (int i = N; i >= 1; i--) {
            ans[i] = sum(N) - sum(one_index[i]);
            update(one_index[i], 1);
        }

        fenwick.assign(N + 1, 0);

        vector<int64_t> ans2(N + 1);
        for (int i = 1; i <= N; i++) {
            ans2[i] = sum(one_index[i] - 1);
            update(one_index[i], 1);
        }

        int64_t real = 0;
        for (int i = 1; i <= N; i++) {
            real += ans[i] * ans2[i];
        }
        return real;
    }
    int64_t find_triplets_left() {
        // O N log(N)
        // https://www.geeksforgeeks.org/find-number-of-triplets-in-array-such-that-aiajak-and-ijk/?ref=rp
        // a[i] > a[j] > a[k] and i < j < k
        // inversions but 3 elements
        vector<int> A = {4, 3, 2, 1};
        vector<int> B = A;
        int N = A.size();

        sort(B.begin(), B.end());

        for (int i = 0; i < N; i++) {
            int idx = lower_bound(B.begin(), B.end(), A[i]) - B.begin() + 1;
            A[i] = idx;
        }
        vector<int> one_index(N + 1);

        for (int i = 1; i <= N; i++) {
            one_index[i] = A[i - 1];
        }
        vector<int> fenwick(N + 1);

        auto sum = [&](int i) -> int64_t {
            int64_t total = 0;
            while (i > 0) {
                total += fenwick[i];
                i -= i & -i;
            }
            return total;
        };

        auto update = [&](int i, int delta) -> void {
            while (i <= N) {
                fenwick[i] += delta;
                i += i & -i;
            }
        };

        // find from last, whose cost is less than current val
        vector<int64_t> ans(N + 1);

        for (int i = N; i > 0; i--) {
            ans[i] = sum(one_index[i] - 1);
            update(one_index[i], 1);
        }

        fenwick.assign(N + 1, 0);

        vector<int64_t> ans2(N + 1);
        for (int i = 1; i <= N; i++) {
            ans2[i] = (i - 1) - sum(one_index[i]);
            update(one_index[i], 1);
        }
        int64_t real = 0;
        for (int i = 1; i <= N; i++) {
            real += ans[i] * ans2[i];
        }
        return real;
    }
};
