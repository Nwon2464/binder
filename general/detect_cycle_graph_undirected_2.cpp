#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
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

// void solve() {

// }

int main() {
#ifdef MIPPON_LOCAL
     auto begin = std::chrono::high_resolution_clock::now();
#endif
     ios::sync_with_stdio(false);
#ifndef MIPPON_LOCAL
     cin.tie(nullptr);
#endif

     int N, M;
     cin >> N >> M;
     const int nax = 1e5 + 5;
     vector<int> edges[nax];
     vector<int> parents(nax, -1);
     vector<bool> visited(nax);
     for (int i = 0; i < M; i++) {
          int x, y;
          cin >> x >> y;
          edges[x].push_back(y);
          edges[y].push_back(x);
     }
     // why cycle_start = -1, we will recover the path when cycle is detected
     // we will recover the path by iterating until val is -1
     int cycle_start = -1;
     int cycle_end = 0;
     auto dfs = [&](int x, int parent, auto &&dfs) -> bool {
          visited[x] = 1;
          for (auto y : edges[x]) {
               if (!visited[y]) {  // if unvisited, for sure, we need to visit it and then keep dfsing with keep
                    // recording the path in parents
                    parents[y] = x;
                    // we pass 2 vals, first - where we are going to, second previous path
                    if (dfs(y, x, dfs)) return 1;
               } else if (parent != y) {
                    // why else if clause? as long as visited is all visited, it will be here
                    // we need another check if parents(previous node) and y(current node) val is not same, it is cycle
                    cycle_start = y;
                    cycle_end = x;
                    return 1;
               }
          }

          return 0;
     };

     auto is_cycle = [&]() -> bool {
          for (int i = 1; i <= N; i++) {
               if (!visited[i]) {
                    if (dfs(i, -1, dfs)) return 1;
               }
          }
          return 0;
     };
     auto print_paths = [&]() -> void {
          vector<int> cycle;
          cycle.push_back(cycle_start);
          for (int v = cycle_end; v != cycle_start; v = parents[v]) cycle.push_back(v);
          cycle.push_back(cycle_start);
          reverse(cycle.begin(), cycle.end());

          // cout << "Cycle found: ";
          cout << cycle.size() << endl;
          for (int v : cycle) cout << v << " ";
          cout << endl;
     };
     if (is_cycle()) {
          print_paths();
     } else {
          cout << "IMPOSSIBLE" << endl;
     }

#ifdef MIPPON_LOCAL
     auto end = std::chrono::high_resolution_clock::now();
     cerr << setprecision(4) << fixed;
     cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count()
          << " seconds" << endl;
#endif

     return 0;
}