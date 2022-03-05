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


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

// implementation of bipartitie_graph
// 1. bfs  when nax = 1e5+5;
// 2. dfs
// 3. bfs  when nax = 200 using adj matrix
const int nax = 1e5 + 5;
vector<int> edges[nax];
vector<int> colors;
bool is_bipartite = 1;
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);

     int N, M;
     cin >> N >> M;
     for (int i = 0; i < M; i++) {
          int x, y;
          cin >> x >> y;
          --x, --y;
          edges[x].push_back(y);
          edges[y].push_back(x);
     }

     colors.resize(N, -1);
     queue<int> q;
     for (int i = 0; i < N; i++) {
          if (colors[i] == -1) {
               q.push(i);
               colors[i] = 0;
               while (!q.empty()) {
                    int x = q.front();
                    q.pop();

                    for (auto y : edges[x]) {
                         if (colors[y] == -1) {
                              colors[y] = colors[x] ^ 1;
                              q.push(y);
                         } else {
                              // this if statement is same as
                              // is_bipartite &= colors[y] != colors[x];
                              if (colors[y] == colors[x]) {
                                   is_bipartite = 0;
                              }
                         }
                    }
               }
          }
     }
     // cout << colors << endl;
     if (is_bipartite) {
          vector<int> cnt(2);
          for (int i = 0; i < N; i++) {
               ++cnt[colors[i]];
          }
          cout << cnt[0] << endl;
          for (int i = 0; i < N; i++) {
               if (colors[i] == 0) {
                    cout << i + 1 << " ";
               }
          }
          cout << endl;
          cout << cnt[1] << endl;
          for (int i = 0; i < N; i++) {
               if (colors[i] == 1) {
                    cout << i + 1 << " ";
               }
          }
          cout << endl;
     } else {
          cout << -1 << endl;
     }
}

// dfs
// const int nax = 1e5 + 5;
// vector<int> edges[nax];
// vector<bool> seen(nax);
// vector<bool> colors(nax);
// bool possible = 1;
// void dfs(int x, bool c) {
//      if (seen[x] == true) return;
//      seen[x] = 1;
//      // dfs only update seen or visted boolean right here. not inside of for loop
//      colors[x] = c;
//      for (auto y : edges[x]) {
//           if (!seen[y]) {
//                dfs(y, c ^ 1);
//           } else {
//                if (colors[y] == c) {
//                     possible = 0;
//                }
//           }
//      }
// }
// int main() {
//      ios::sync_with_stdio(0);
//      cin.tie(0);

//      int N, M;
//      cin >> N >> M;
//      for (int i = 0; i < M; i++) {
//           int x, y;
//           cin >> x >> y;
//           --x, --y;
//           edges[x].push_back(y);
//           edges[y].push_back(x);
//      }
//      for (int i = 0; i < N; i++) {
//           if (!seen[i]) {
//                dfs(i, 0);
//           }
//      }
// }

// bfs adj 2-d matrix
// const int nax = 205;
// vector<int> colors;
// vector<vector<bool>> edges(nax, vector<bool>(nax));
// int main() {
//      ios::sync_with_stdio(0);
//      cin.tie(0);
//      int N;
//      string S;
//      cin >> N >> S;
//      int M = S.length();
//      for (int i = 0; i < M; i++) {
//           for (int j = i + 1; j < M; j++) {
//                if (S[i] > S[j]) {
//                     edges[i][j] = edges[j][i] = 1;
//                }
//           }
//      }
//      colors.resize(N, -1);
//      queue<int> q;
//      bool possible = 1;
//      for (int i = 0; i < N; i++) {
//           if (colors[i] == -1) {
//                q.push(i);
//                colors[i] = 0;
//                while (!q.empty()) {
//                     int x = q.front();
//                     q.pop();
//                     for (int y = 0; y < N; y++) {
//                          if (edges[x][y]) {
//                               if (colors[y] == -1) {
//                                    colors[y] = colors[x] ^ 1;
//                                    q.push(y);
//                               } else {
//                                    if (colors[y] == colors[x]) {
//                                         possible = 0;
//                                    }
//                               }
//                          }
//                     }
//                }
//           }
//      }
//      if (possible) {
//           cout << "YES" << endl;
//           for (int i = 0; i < N; i++) {
//                cout << colors[i];
//           }
//           cout << endl;
//      } else {
//           cout << "NO" << endl;
//      }
// }