#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <vector>

using namespace std;

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

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef MIPPON_LOCAL
#define dbg(...) cerr <<"\e[38;5;214m" << "(" << #__VA_ARGS__ << "):" << "\e[39m", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
// clang-format on
vector<int64_t> edges[10];
int64_t indegree[10];
vector<int64_t> topological_order;
void solve() {
    // topological sorting - can have multiples
    // less or no indegree til largest  would be inserted in order
    // this algo works only when it is dag
    // and when you just need to detect if graph has cycle or not
    // and not needing for recovering paths, then this is the algorithms
    // kahn's algorithms
    // main purpose of this algo is to find topological sort

    // topogical sort means linear ascending verticies that forms edge u and v
    // such that u appears always before v. in a graph, there can be lots of topological sort in a graph

    // what is toplogoical sort beside detecting cycle in a graph?
    // toplocial sort should be in dag and directed graph
    // this version is ONLY for directed graph

    // if you are looking for detecting cycle of undirected graph,
    // type "detect cycle graph undirected"
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        edges[x].push_back(y);
        ++indegree[y];
    }

    queue<int64_t> q;

    // if no indegree equals to 0, it has cycles
    // if( cnt < n ) it means cycle
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    int cnt = 0;
    while (!q.empty()) {
        ++cnt;
        int64_t x = q.front();
        topological_order.push_back(x);
        q.pop();
        for (auto y : edges[x]) {
            --indegree[y];
            if (indegree[y] == 0) {
                q.push(y);
            }
        }
    }
    cout << topological_order << endl;

    if (cnt < N)
        cout << "CYCLE" << endl;
    else {
        cout << topological_order << endl; // topological sort
        cout << cnt << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // int tests;
    // cin >> tests;
    // while (tests-- > 0)
    solve();
}