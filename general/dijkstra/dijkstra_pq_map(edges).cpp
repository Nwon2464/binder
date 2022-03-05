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

const int nax = 5e5 + 5;
const ll inf = 1e18 + 5;
map<int, vector<pair<ll, ll>>> edges;
vector<ll> parents(nax, -1), dis(nax, inf);
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> s;
// using pii = pair<ll, ll>;
// priority_queue<pii, vector<pii>, greater<pii>> s;

int main() {
    ios::sync_with_stdio(false);
#ifndef MIPPON_DEBUG
    cin.tie(nullptr);
#endif
    // https://codeforces.com/contest/20/problem/C
    // https://judge.yosupo.jp/submission/54240 tested 987 ms
    int n, m, source, dest;
    cin >> n >> m >> source >> dest;
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        // edges[v].push_back({u, w});
    }

    s.push({0, source});
    dis[source] = 0;

    while (!s.empty()) {
        ll u = s.top().second;
        ll u_t = s.top().first;
        s.pop();
        if (dis[u] != u_t)
            continue;
        for (int i = 0; i < edges[u].size(); i++) {
            ll v = edges[u][i].first;
            ll w = edges[u][i].second;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                s.push({dis[v], v});
                parents[v] = u;
            }
        }
    }

    if (dis[dest] == inf)
        puts("-1");
    else {
        auto print_shortest_path_2 = [&](int destination) -> void {
            vector<int> path;
            for (int cur = dest; cur != -1; cur = parents[cur])
                path.push_back(cur);
            reverse(path.begin(), path.end());
            printf("%lld %d\n", (long long)dis[dest], (int)path.size() - 1);
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
    // dbg(parents);
    return 0;
}