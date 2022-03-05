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

// fenwick tree range 10^6 or 7 is max, other wise need convert (coordinate compressions)

template <typename T>
struct BIT {
    // should be invoked from 0 index.
    // when querying, if index that are given is one-based, then l-1,r-1 for query, otherwise l,r
    int N = 0;
    vector<T> fenwick;

    BIT(const vector<T> &_values) {
        init(_values);
    }

    BIT(int _N = 0) {
        init(_N);
    }

    void init(int _N) {
        N = _N + 1;
        fenwick.assign(N, 0);
    }

    void init(const vector<T> &_values) {
        assert(_values.size() != 0);
        init(_values.size());
        for (int i = 0; i < (int)_values.size(); i++) {
            update(i, _values[i]);
        }
    }

    // Point update, Range Query
    void update(int i, T delta) {
        ++i;
        while (i < N) {
            fenwick[i] += delta;
            i += i & -i;
        }
    }
    T sum(int i) {
        T total = 0;
        i++;
        while (i > 0) {
            total += fenwick[i];
            i -= i & -i;
        }
        return total;
    }
    // return [l-1, r]
    T range_sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // Range update, Point Query
    // always remember when you need to do RANGE UPDATE, you need to seperate range update vals and original fenwick
    // do not mix them up in one fenwick array
    // BIT<int64_t> fw(A);
    // BIT<int64_t> range_update(N);
    // fw have vals in it.
    // range_update is empty array but size of fw (we need to do range update here)
    // so when point querying, you need to add both of them -> fw.range_sum(idx, idx) + range_update.sum(idx)
    void range_update(int l, int r, T val) {
        update(l, val);
        update(r + 1, -val);
    }

    // Range update , Range Query
    void RURQ(int l, int r, T x) {
        RURQ_add(B1, l, x);
        RURQ_add(B1, r + 1, -x);
        RURQ_add(B2, l, x * (l - 1));
        RURQ_add(B2, r + 1, -x * r);
    }
    void RURQ_add(vector<int> &b, int idx, int x) {
        while (idx <= N) {
            b[idx] += x;
            idx += idx & -idx;
        }
    }
    T RURQ_sum(vector<int> b, int idx) {
        T total = 0;
        while (idx > 0) {
            total += b[idx];
            idx -= idx & -idx;
        }
        return total;
    }

    T RURQ_range_sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
    T prefix_sum(int idx) {
        return RURQ_sum(B1, idx) * idx - RURQ_sum(B2, idx);
    }
    int count_inversion() {
        // 2 methods (maxelements O(nlog(maxelement)), usual update from backward O(nlog(size of N)))
        // first one cannot proccess neg, second one proccess neg
    }
    int find_kth_tallest_person(int k) {
        // Time Complexity O(n(log^2 N))
        // we can short it down to O(n log n) using binary lifting technique
        // https://codeforces.com/blog/entry/61364
        // https://codeforces.com/contest/1354/problem/D (this algorithms is used)

        //  1 2 3 4 5 6  => index && height (height 1cm, height 2cm,... 6cm)
        // [8,2,10,100,1,2] => number of people
        // find 121-th tallest person is height of 5 (index 5)

        // time complexity O(n log^2 n), this is too strict, can't use long long sometimes
        int l = 0, r = fenwick.size();
        while (l < r) {
            int mid = (l + r) / 2;
            if (k <= sum(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l + 1; // avoiding 0-index
    }
    int _largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }
    int find_kth_tallest_person2(int k) {
        // Time Complexity O(n log n)
        // https://codeforces.com/blog/entry/61364 (binary lifting technique)
        // https://codeforces.com/contest/1354/problem/D (this algorithms is used)
        // Walking down from largest bit on to 0
        // fenwick tree from algorithms live Youtube
        int sum = 0;
        int pos = 0;
        int largest_bit = _largest_bit(N);
        for (int i = largest_bit; i >= 0; i--) {
            if (pos + (1 << i) < N && sum + fenwick[pos + (1 << i)] < k) {
                sum += fenwick[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1;
    }
};

const int INF = 10000000;
template <typename T>
struct binary_indexed_tree {
    int N;
    vector<T> BIT;
    binary_indexed_tree(int N) : N(N), BIT(N + 1, 0) {
    }
    binary_indexed_tree() {
    }
    void add(int i, T x) {
        i++;
        while (i <= N) {
            BIT[i] += x;
            i += i & -i;
        }
    }
    T sum(int i) {
        T ans = 0;
        while (i > 0) {
            ans += BIT[i];
            i -= i & -i;
        }
        return ans;
    }
    T range_sum(int L, int R) {
        return sum(R) - sum(L);
    }
};
struct same_query {
    vector<int> hash;
    vector<int> C;
    binary_indexed_tree<long long> BIT;
    same_query(vector<int> A) {
        int N = A.size();
        hash = vector<int>(N);
        mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0; i < N; i++) {
            hash[i] = mt() % ((long long)1 << 31);
        }
        C = vector<int>(N);
        for (int i = 0; i < N; i++) {
            C[i] = hash[A[i]];
        }
        BIT = binary_indexed_tree<long long>(N);
        for (int i = 0; i < N; i++) {
            BIT.add(i, C[i]);
        }
    }
    void update(int p, int x) {
        BIT.add(p, -C[p]);
        C[p] = hash[x];
        BIT.add(p, C[p]);
    }
    // bool range_same(int L, int R, int x) { return BIT.sum(L, R) == (long long)hash[x] * (R - L); }
};
int main() {
    vector<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    return 0;
}
