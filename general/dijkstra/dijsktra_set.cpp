#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// --------------------------------
//  Using set dijkstra alogorithms|
//                                |
//  Time complexity : O(n^2+m)    |
// --------------------------------
// Using Set data structure is based on red-black trees

// priority_queue has a drawback compared to Set : it doesn't support the operation of removing an element. Because of this we need to do a "workaround",
//that actually leads to a slightly worse factor log(m) instead of log(n) (although in terms of complexity they are identical).
// codeforces - dijsktra
const int MAX_N = 1e5 + 5;
const long long INF = 1e18L + 5;
vector<pair<int, int>> edges[MAX_N];
long long dist[MAX_N]; // distance from vertex 1
int parent[MAX_N];
bool visited[MAX_N];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edges[a].push_back({ b, w });
        edges[b].push_back({ a, w });
    }
    dist[1] = 0;
    for (int i = 2; i <= n; i++) {
        dist[i] = INF;
    }
    // we could also use priority_queue
    set<pair<long long, int>> s; // pairs (distance, index)
    s.insert({ dist[1], 1 });
    while (!s.empty()) {
        pair<long long, int> best = *s.begin();
        s.erase(s.begin());
        int a = best.second;
        if (visited[a]) {
            continue;
        }
        visited[a] = true;
        for (pair<int, int> edge : edges[a]) {
            int b = edge.first;
            int len = edge.second;
            if (dist[a] + len < dist[b]) {
                parent[b] = a;
                dist[b] = dist[a] + len;
                s.insert({ dist[b], b });
            }
        }
    }
    if (!visited[n]) { // we couldn't reach vertex n
        puts("-1");
        return 0;
    }
    // retrieve the path from the end
    vector<int> path;
    int current = n;
    while (current != 1) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(1);
    reverse(path.begin(), path.end());
    for (int x : path) {
        printf("%d ", x);
    }
    puts("");
}
