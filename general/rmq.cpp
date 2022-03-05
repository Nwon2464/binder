#include <algorithm>
#include <array>
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
// clang-format on

template <class T>
struct sparse_gcd {
    // Returns GCD on segment [l, r] of predefined array a
    vector<vector<T>> sp;
    vector<int> H;
    T get(int l, int r) {
        assert(l >= 0);
        assert(r < sz(H) - 1);
        int h = H[r - l + 1];
        return __gcd(sp[h][l], sp[h][r - (1 << h) + 1]);
    }
    sparse_gcd(vector<T> a) {
        int n = a.size();
        H = vector<int>(n + 1);
        for (int i = 3; i < n + 1; i++) {
            H[i] = H[i - 1] + (((i - 1) & (i - 2)) == 0);
        }
        int s = 0;
        while ((1 << s) < n)
            s++;
        sp = vector<vector<T>>(s, vector<T>(n));
        for (int i = 0; i < n; i++) {
            sp[0][i] = a[i];
        }
        for (int j = 1; j < s; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                sp[j][i] = get(i, i + (1 << j) - 1);
            }
        }
    }
};

template <class T>
struct sparse_min {
    // Returns min on segment [l, r] of predefined array a
    //
    // Correctness tested on the following problem:
    // https://codeforces.com/contest/1304/problem/E
    // Speed tested on random tests with n = 4e6, q = 4e6, T = int, average = 0.508ms/test (local)
    // Speed tested on random tests with n = 4e6, q = 4e7, T = int, average = 1.778ms/test (local)
    //
    vector<vector<T>> sp;
    vector<int> H;
    T get(int l, int r) {
        assert(l >= 0);
        assert(r < sz(H) - 1);
        int h = H[r - l + 1];
        return min(sp[h][l], sp[h][r - (1 << h) + 1]);
    }
    sparse_min(vector<T> a) {
        int n = a.size();
        H = vector<int>(n + 1);
        for (int i = 3; i < n + 1; i++) {
            H[i] = H[i - 1] + (((i - 1) & (i - 2)) == 0);
        }
        int s = 0;
        while ((1 << s) < n)
            s++;
        sp = vector<vector<T>>(s, vector<T>(n));
        for (int i = 0; i < n; i++) {
            sp[0][i] = a[i];
        }
        for (int j = 1; j < s; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                sp[j][i] = get(i, i + (1 << j) - 1);
            }
        }
    }
};

template <class T>
struct sparse_max {
    // Returns max on segment [l, r] of predefined array a

    // Correctness tested on the following problem:
    // https://codeforces.com/contest/1304/problem/E
    // Speed tested on random tests with n = 4e6, q = 4e6, T = int, average = 0.508ms/test (local)
    // Speed tested on random tests with n = 4e6, q = 4e7, T = int, average = 1.778ms/test (local)
    //
    vector<vector<T>> sp;
    vector<int> H;
    T get(int l, int r) {
        int h = H[r - l + 1];
        return max(sp[h][l], sp[h][r - (1 << h) + 1]);
    }
    sparse_max(vector<T> a) {
        int n = a.size();
        H = vector<int>(n + 1);
        for (int i = 3; i < n + 1; i++) {
            H[i] = H[i - 1] + (((i - 1) & (i - 2)) == 0);
        }
        int s = 0;
        while ((1 << s) < n)
            s++;
        sp = vector<vector<T>>(s, vector<T>(n));
        for (int i = 0; i < n; i++) {
            sp[0][i] = a[i];
        }
        for (int j = 1; j < s; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                sp[j][i] = get(i, i + (1 << j) - 1);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // RMQ usage
    int N;
    cin >> N;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];
    sparse_min<int> B(A);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        cout << B.get(l, r) << el;
    }

    // IgorI
}
