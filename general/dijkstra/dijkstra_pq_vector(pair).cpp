#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdint>
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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef MIPPON_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
// clang-format on

const int nax = 5e+5;
const int64_t inf = 1e18 + 5;
vector<vector<pair<int64_t, int64_t>>> G(nax);
vector<int64_t> dist(nax, inf), parents(nax, -1);
vector<bool> seen(nax);

int main() {
    ios::sync_with_stdio(false);
#ifndef MIPPON_DEBUG
    cin.tie(nullptr);
#endif

    // when you have multiple sources look at neal's dijkstra, sources save in array
    // dijkstra never process negative weights

    // https://judge.yosupo.jp/submission/54232 tested : 335 ms
    // https://codeforces.com/contest/20/problem/C
    int64_t N, M, source, dest;
    cin >> N >> M >> source >> dest;
    // G = vector<vector<pair<int64_t, int64_t>>>(N + 1);
    for (int i = 0; i < M; i++) {
        int64_t a, b, w;
        cin >> a >> b >> w;
        // tip!!!!! when weight is not given, you can make it, make it w = 1 for all
        // do not make it w = 0, bc cost is important in dijkstra
        G[a].push_back({b, w});
        // G[b].push_back({a, w});
    }
    auto dijkstra = [&](int64_t source) -> void {
        // dist.assign(N + 1, inf);
        // parents.assign(N + 1, -1);

        dist[source] = 0;
        parents[source] = -1;
        using pii = pair<int64_t, int64_t>;
        priority_queue<pii, vector<pii>, greater<pii>> q;
        q.push({0, source});
        while (!q.empty()) {
            int64_t v = q.top().second;
            int64_t d_v = q.top().first;
            q.pop();

            if (d_v != dist[v])
                continue;

            for (auto edge : G[v]) {
                int64_t to = edge.first;
                int64_t len = edge.second;

                if (dist[v] + len < dist[to]) {
                    dist[to] = dist[v] + len;
                    parents[to] = v;
                    q.push({dist[to], to});
                }
            }
        }
    };
    dijkstra(source);

    if (dist[dest] == inf)
        puts("-1");
    else {
        auto print_shortest_path_2 = [&](int destination) -> void {
            vector<int> path;
            for (int cur = dest; cur != -1; cur = parents[cur])
                path.push_back(cur);
            reverse(path.begin(), path.end());
            printf("%lld %d\n", (long long)dist[dest], (int)path.size() - 1);
            for (int i = 0; i + 1 < (int)path.size(); i++)
                printf("%d %d\n", path[i], path[i + 1]);
        };

        auto print_shortest_path_1 = [&](int destination) -> void {
            vector<ll> path;
            for (ll i = destination; i != -1; i = parents[i])
                path.push_back(i);
            reverse(path.begin(), path.end());
            // cout << path << P << endl;
            for (auto i : path)
                cout << i << " ";
        };
        print_shortest_path_1(dest);
        print_shortest_path_2(dest);
    }
    dbg(parents);

    return 0;
}