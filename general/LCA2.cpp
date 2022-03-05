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
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }
// clang-format on
const int nax = 1e5 + 5;
vector<int> edges[nax];
vector<int> depth(nax);
vector<bool> seen(nax);
vector<vector<int>> parents;

int N, D;
int largest_bit(int x) { return 31 - __builtin_clz(x); }
int walk(int i, int k) {
     // this walk function is same as Kth Ancestor of a Tree Node
     // https://leetcode.com/problems/kth-ancestor-of-a-tree-node/

     // walk whoever the node is higher depth up to i or j
     for (int d = 0; d <= D && i != -1; d++) {
          if (((1 << d) & k) > 0) {
               i = parents[d][i];
          }
     }
     return i;
}
int lca(int i, int j) {
     // when their depth is different, i is deeper in this case
     // and i walks up to the same depth of j
     if (depth[i] > depth[j]) {
          i = walk(i, depth[i] - depth[j]);
     }

     // when their depth is different, j is deeper in this case
     // and j walks up to the same depth of i
     if (depth[j] > depth[i]) {
          j = walk(j, depth[j] - depth[i]);
     }
     // if depth are same && the node where they are stying at are same
     if (i == j) {
          return i;
     }

     // from here, we assume that depth of i and j are same level
     // we are trying to find the node that is just shy of LCA for both
     for (int d = D; d >= 0; d--) {
          if (parents[d][i] != parents[d][j]) { // only if they are different, we are finding LCA
               i = parents[d][i];
               j = parents[d][j];
          }
     }
     // parents table
     // [-1, 0, 0, 1, 1, 2, 2,] < this line is already done when bfs (who are their parents?)
     // [-1,-1,-1, 0, 0, 0, 0,] < this and below line is getting computed at line 124, there lines meaning
     // [-1,-1,-1,-1,-1,-1,-1,] < who are their grand or grand grand parents?
     //            |     | suppose your parents are different, so we loop over til 0th row from Dth row
     // [0][3] != [0][5] are diff, (1,2), so we are getting that value of [0][1]'s parent and [0][2] which is 0
     // we have found LCA
     return parents[0][i];
}
int dist(int i, int j) { return depth[i] + depth[j] - (2 * depth[lca(i, j)]); }
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     int Q;
     cin >> N >> Q;
     // https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
     // above link is tree picture
     for (int i = 0; i < N - 1; i++) {
          // inserting edges
          int x, y;
          cin >> x >> y;
          --x, --y;
          edges[x].push_back(y);
          edges[y].push_back(x);
     }

     D = largest_bit(N); // the most left bit and counting leading zero

     parents.resize(D + 1, vector<int>(N, -1));

     queue<int> q;
     q.push(0);
     seen[0] = 1;
     while (!q.empty()) {
          int x = q.front();
          q.pop();

          for (auto y : edges[x]) {
               if (!seen[y]) {
                    seen[y] = 1;
                    q.push(y);
                    parents[0][y] = x;       // recording parents of each node only [0][0,,,edges]
                    depth[y] = depth[x] + 1; // getting depth of the each node
               }
          }
     }

     for (int d = 1; d <= D; d++) { // recording parents of each node except [0][0..edges]
          for (int i = 0; i < N; i++) {
               int mid = parents[d - 1][i];
               if (mid != -1) {
                    parents[d][i] = parents[d - 1][mid];
               }
          }
     }

     for (int i = 0; i < Q; i++) {
          int x, y;
          cin >> x >> y;
          --x, --y;
     }
}

// dfs version of finding depth of tree
// void dfs(int x) {
//      if (seen[x]) return;
//      seen[x] = 1;

//      for (auto y : edges[x]) {
//           if (!seen[y]) {
//                depth[y] = depth[x] + 1;
//                parents[0][y] = x;
//                dfs(y);
//           }
//      }
// }
//      for (int i = 0; i < N; i++) {
//           if (!seen[i]) {
//                dfs(i);
//           }
//      }

// #include <bits/stdc++.h>
// using namespace std;
// #include <atcoder/all>
// using namespace atcoder;
// #define rep(i, n) for (int i = 0; i < (n); ++i)
// using ll = long long;
// using P = pair<int, int>;

// vector<int> dep;
// vector<vector<int>> to;

// void dfs(int v, int _dep = 0, int p = -1) {
//      dep[v] = _dep;
//      for (int u : to[v]) {
//           if (u == p) continue;
//           dfs(u, _dep + 1, v);
//      }
// }

// int main() {
//      int n, q;
//      cin >> n >> q;
//      to.resize(n);
//      rep(i, n - 1) {
//           int a, b;
//           cin >> a >> b;
//           --a;
//           --b;
//           to[a].push_back(b);
//           to[b].push_back(a);
//      }
//      dep.resize(n);
//      dfs(0);

//      rep(qi, q) {
//           int c, d;
//           cin >> c >> d;
//           --c;
//           --d;
//           int ans = (dep[c] + dep[d]) % 2;
//           if (ans == 0)
//                cout << "Town" << endl;
//           else
//                cout << "Road" << endl;
//      }
//      return 0;
// }