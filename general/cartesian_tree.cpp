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

//
// Use compare = less<int>() for a min heap and compare = greater<int>() for a max heap.
// When there are ties, the left value will be the parent of the right value.
template <typename T, typename Compare>
vector<int> build_cartesian_tree(const vector<T> &A, const Compare &&compare) {
    // building cartesian tree O(N)
    int n = int(A.size());
    vector<int> parent(n, -1);
    vector<int> stack;

    for (int i = 0; i < n; i++) {
        int erased = -1;

        while (!stack.empty() && compare(A[i], A[stack.back()])) {
            erased = stack.back();
            stack.pop_back();
        }

        parent[i] = stack.empty() ? -1 : stack.back(); // sometimes need to replace -1 with i for the statement
        // where the smallest element becomes the root

        if (erased >= 0)
            parent[erased] = i;

        stack.push_back(i);
    }

    return parent;
}

void build_cartesian_tree_recursion(int l, int r, int cost, vector<int> &a, vector<int> &b) {
    if (l > r)
        return;
    int mx = l;
    for (int i = l; i <= r; i++) {
        if (a[i] > a[mx]) {
            mx = i; // finding max O(N)
        }
    }
    b[mx] = cost;

    build_cartesian_tree_recursion(l, mx - 1, cost + 1, a, b);
    build_cartesian_tree_recursion(mx + 1, r, cost + 1, a, b);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<int> A(N);

    for (auto &a : A)
        cin >> a;

    vector<int> parent = build_cartesian_tree(A, greater<int>());
    // use greater<int>() or less<int>()
    // cout << parent;
    vector<int> depth(N);

    // O(N^2)
    for (int i = 0; i < N; i++) {
        int loc = i;
        depth[i] = -1;

        while (loc >= 0) {
            depth[i]++;
            loc = parent[loc];
        }
    }
    cout << depth;

    // using recursion

    // int N;
    // cin >> N;
    // vector<int> a(N), b(N);
    // rep(i, 0, N) cin >> a[i];
    // build_cartesian_tree_recursion(0, N - 1, 0, a, b);

    // output_vector(b);
}
