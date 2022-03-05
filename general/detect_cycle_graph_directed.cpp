#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <ostream>
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

const int nax = 5e5 + 5;
vector<pair<int, int>> adj[nax];
vector<int> color(nax, 0);
vector<int> parent(nax, -1);

int main() {
#ifdef MIPPON_LOCAL
    auto begin = std::chrono::high_resolution_clock::now();
#endif
    ios::sync_with_stdio(false);
#ifndef MIPPON_LOCAL
    cin.tie(nullptr);
#endif
    // https://cses.fi/problemset/task/1678/ directed cycle
    // https://judge.yosupo.jp/submission/54250 tested

    int n, m;
    cin >> n >> m;
    int cycle_start, cycle_end;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back({y, i});
        // adj[y].push_back(x);
    }

    auto dfs = [&](int v, auto &&dfs) -> bool { // passing vertex and its parent vertex
        color[v] = 1;
        for (auto u : adj[v]) {
            if (color[u.first] == 0) {
                parent[u.first] = v;
                if (dfs(u.first, dfs))
                    return true;
            } else if (color[u.first] == 1) {
                cycle_end = v;
                cycle_start = u.first;
                return true;
            }
        }
        color[v] = 2;
        return false;
    };

    auto find_cycle = [&]() -> void {
        cycle_start = -1;

        for (int v = 0; v < n; v++) {
            if (color[v] == 0 && dfs(v, dfs))
                break;
        }

        if (cycle_start == -1) {
            cout << -1 << endl;
            // cout << "Acyclic" << endl;
        } else {
            vector<int> cycle;
            cycle.push_back(cycle_start);
            for (int v = cycle_end; v != cycle_start; v = parent[v])
                cycle.push_back(v);
            cycle.push_back(cycle_start);
            reverse(cycle.begin(), cycle.end());

            // cout << "Cycle found: ";
            cout << sz(cycle) - 1 << endl;
            dbg(cycle, adj[0], adj[1], adj[2]);
            for (int i = 0; i < sz(cycle) - 1; i++) {
                pair<int, int> p = make_pair(cycle[i], cycle[i + 1]);
                for (auto [to, idx] : adj[p.first]) {
                    if (to == p.second) {
                        cout << idx << endl;
                        break; // we may have same edges twice, only want one
                    }
                }
            }
            // original cycle print path
            // for (int v : cycle) cout << v << " ";
            // cout << endl;
        }
    };
    find_cycle();

#ifdef MIPPON_LOCAL
    auto end = std::chrono::high_resolution_clock::now();
    cerr << setprecision(4) << fixed;
    cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " seconds" << endl;
#endif

    return 0;
}

// another easy method

// int N, M;
// cin >> N >> M;
// const int nax = 5e5 + 5;
// vector<pair<int, int>> edges[nax];
// vector<int> parents(nax, -1);
// vector<bool> dfsvisited(nax);
// vector<bool> visited(nax);
// for (int i = 0; i < M; i++) {
//      int x, y;
//      cin >> x >> y;
//      edges[x].push_back({y, i});
// }
// // why cycle_start = -1, we will recover the path when cycle is detected
// // we will recover the path by iterating until val is -1
// int cycle_start = -1;
// int cycle_end = 0;
// auto dfs = [&](int x, int parent, auto &&dfs) -> bool {
//      visited[x] = 1;
//      dfsvisited[x] = 1;
//      for (auto [to, idx] : edges[x]) {
//           if (!visited[to]) {  // if unvisited, for sure, we need to visit it and then keep dfsing with keep
//                // recording the path in parents
//                parents[to] = x;
//                // we pass 2 vals, first - where we are going to, second previous path
//                if (dfs(to, x, dfs)) return 1;
//           } else if (dfsvisited[to] == 1) {
//                // why else if clause? as long as visited is all visited, it will be here
//                // we need another check if parents(previous node) and y(current node) val is not same, it is cycle
//                cycle_start = to;
//                cycle_end = x;
//                return 1;
//           }
//      }
//      dfsvisited[x] = 0;
//      return 0;
// };

// auto is_cycle = [&]() -> bool {
//      for (int i = 1; i <= N; i++) {
//           if (!visited[i]) {
//                if (dfs(i, -1, dfs)) return 1;
//           }
//      }
//      return 0;
// };