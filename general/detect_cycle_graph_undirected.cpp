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

int n, m;
vector<vector<int>> adj(5);
vector<bool> visited;
vector<int> parent;
int cycle_start, cycle_end;

bool dfs(int v, int par) {  // passing vertex and its parent vertex
     visited[v] = true;
     for (int u : adj[v]) {
          if (u == par) continue;  // skipping edge to parent vertex
          if (visited[u]) {        // when we found out cycle
               cycle_end = v;
               cycle_start = u;
               return true;
          }
          parent[u] = v;
          if (dfs(u, parent[u])) return true;
     }
     return false;
}

void find_cycle() {
     visited.assign(n, false);
     parent.assign(n, -1);
     cycle_start = -1;

     for (int v = 0; v < n; v++) {
          // if it is unvisited && dfs is true, which means we have jut found out the one cycle
          if (!visited[v] && dfs(v, parent[v])) {
               break;
          }
     }

     if (cycle_start == -1) {
          cout << "Acyclic" << endl;
     } else {
          vector<int> cycle;
          cycle.push_back(cycle_start);
          for (int v = cycle_end; v != cycle_start; v = parent[v]) cycle.push_back(v);
          cycle.push_back(cycle_start);
          reverse(cycle.begin(), cycle.end());

          cout << "Cycle found: ";
          for (int v : cycle) cout << v << " ";
          cout << endl;
     }
}
int main() {
#ifdef MIPPON_LOCAL
     auto begin = std::chrono::high_resolution_clock::now();
#endif
     ios::sync_with_stdio(false);
#ifndef MIPPON_LOCAL
     cin.tie(nullptr);
#endif
     // https://cses.fi/problemset/task/1678/ undirected cycle
     n = 5;
     adj[0].push_back(1);
     adj[1].push_back(0);

     adj[1].push_back(2);
     adj[2].push_back(1);

     adj[2].push_back(0);
     adj[0].push_back(2);

     adj[4].push_back(3);
     adj[3].push_back(4);
     find_cycle();

#ifdef MIPPON_LOCAL
     auto end = std::chrono::high_resolution_clock::now();
     cerr << setprecision(4) << fixed;
     cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count()
          << " seconds" << endl;
#endif

     return 0;
}