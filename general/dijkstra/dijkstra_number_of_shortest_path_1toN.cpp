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
const int nax = 10; // 2e5 + 5;
const ll inf = 1e18 + 5;
vector<ll> edges[nax];
vector<ll> dist(nax, inf);
vector<ll> paths(nax, 0);
int main() {
#ifdef MIPPON_LOCAL
    auto begin = std::chrono::high_resolution_clock::now();
#endif
    ios::sync_with_stdio(false);
#ifndef MIPPON_LOCAL
    cin.tie(nullptr);
#endif

    // int tests;
    // cin >> tests;

    // while (tests--) {
    // }
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    auto dijkstra = [&](int source) -> void {
        queue<ll> pq;

        pq.push(source);
        dist[source] = 0;
        paths[source] = 1; // why 1?
        // bc in case when N =1, 1 itself as a source is shortest path, we updates best paths in dist array
        // so later we check to see if there is another shortest path, we simply add it path[v] += path[u]
        while (!pq.empty()) {
            ll u = pq.front();
            pq.pop();

            for (auto v : edges[u]) {
                if (dist[u] + 1 < dist[v]) { // finding shortest path
                    pq.push(v);
                    dist[v] = dist[u] + 1;
                    paths[v] = paths[u];
                } else if (dist[v] == dist[u] + 1) { // finding other shortest path
                    paths[v] += paths[u];            // when mod is given, use mod here
                }
            }
        }
    };
    dijkstra(0);
    dbg(paths);
    cout << paths[N - 1] << endl;

#ifdef MIPPON_LOCAL
    auto end = std::chrono::high_resolution_clock::now();
    cerr << setprecision(4) << fixed;
    cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " seconds" << endl;
#endif

    return 0;
}