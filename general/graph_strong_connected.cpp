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

struct graph_scc {
    // Finds Strongly Connected Components of given graph
    //
    // Correctness tested on the following problem:
    // https://atcoder.jp/contests/arc069/tasks/arc069_d
    //
    int n;
    vector<vector<int>> graph;
    vector<vector<int>> inv_graph;
    vector<int> fr, to;
    vector<int> fn;
    vector<int> vis;
    vector<int> component;
    int col;
    void inv_dfs(int v) {
        vis[v] = 1;
        for (auto id : inv_graph[v]) {
            int u = fr[id];
            if (!vis[u]) {
                inv_dfs(u);
            }
        }
        fn.push_back(v);
    }
    void dfs(int v) {
        component[v] = col;
        for (auto id : graph[v]) {
            int u = to[id];
            if (component[u] == -1) {
                dfs(u);
            }
        }
    }
    graph_scc(int _n) {
        n = _n;
        graph = vector<vector<int>>(n);
        inv_graph = vector<vector<int>>(n);
    }
    void add_edge(int v, int u) {
        graph[v].push_back(fr.size());
        inv_graph[u].push_back(fr.size());
        fr.push_back(v);
        to.push_back(u);
    }
    vector<vector<int>> scc() {
        vis = vector<int>(n);
        component = vector<int>(n, -1);
        fn = {};
        col = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                inv_dfs(i);
            }
        }
        reverse(fn.begin(), fn.end());
        for (auto i : fn) {
            if (component[i] == -1) {
                dfs(i);
                col++;
            }
        }
        vector<vector<int>> res(col);
        for (int i = 0; i < n; i++) {
            res[component[i]].push_back(i);
        }
        return res;
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // refer to strivers youtube for SCC.
    // solve();
}
