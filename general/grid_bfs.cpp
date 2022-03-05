#include <cassert>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define endl "\n"

// clang-format off
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef MIPPON_LOCAL
#define dbg(...) cerr <<"\e[38;5;214m" << "(" << #__VA_ARGS__ << "):" << "\e[39m", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
// DIR 8
// xxx
// x.x
// xxx


// QUEENDIR 8 - queen attack safe
//  x x
// x...x
// ..Q..
// x...x
//  x x

// const int QueenDIR_R8[8] = {-2, -2, -1, -1, 1, 1, 2,  2};
// const int QueenDIR_C8[8] = {-1,  1, 2, -2, -2, 2, -1, 1};


// DIR 20

// xxx
//xxxxx
//xx.xx   can be (2 x 2) movement for 0,1 bfs
//xxxxx
// xxx


// DIR 25

//xxxxx
//xxxxx
//xx.xx   can be (5 x 5) movement for 0,1 bfs
//xxxxx   i=-2 , i<=2
//xxxxx   j=-2 , j<=2

// clang-format on

const int INF = 1e9 + 5;
const int64_t INF64 = 2e18 + 5;

const int DIR_R4[4] = {-1, 0, 1, 0};
const int DIR_C4[4] = {0, 1, 0, -1};

// const int DIR_R20[20] = {-2, -2, -2, -1, -1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2};
// const int DIR_C20[20] = {-1, 0, 1, -2, -1, 0, 1, 2, -2, -1, 1, 2, -2, -1, 0, 1, 2, -1, 0, 1};
// const int DIR_R8[8] = {-1, -1, -1,  0, 1, 1, 1,  0};
// const int DIR_C8[8] = {-1,  0, 1, 1, 1,  0, -1, -1};

template <typename T_row>
struct bfs_grid {
    int row, col;
    vector<T_row> grid;
    vector<vector<int>> dist;
    vector<vector<pair<int, int>>> parent;
    bfs_grid(const vector<T_row> &_grid = {}) {
        init(_grid);
    }

    void init(const vector<T_row> &_grid = {}) {
        grid = _grid;
        row = int(grid.size());
        col = grid.empty() ? 0 : int(grid[0].size());
    }

    bool valid(int r, int c) {
        return 0 <= r && 0 <= c && r < row && c < col;
    }

    void bfs_check(deque<pair<int, int>> &q, const pair<int, int> &s, const pair<int, int> &from_s, int new_dist, int cost) {
        assert(cost == 0 || cost == 1);

        if (new_dist < dist[s.first][s.second]) {
            dist[s.first][s.second] = new_dist;
            parent[s.first][s.second] = from_s;
            if (cost == 0)
                q.push_front(s);
            else
                q.push_back(s);
        }
    }

    void bfs(const vector<pair<int, int>> &source) {
        if (row == 0 || col == 0)
            return;

        // 0-1 BFS using deque. also possible to inmitate using two queue(more to code)
        // time complexity is same
        deque<pair<int, int>> q;
        dist.assign(row, vector<int>(col, INF));
        parent.assign(row, vector<pair<int, int>>(col, {-1, -1}));
        // the reason we are checking the source is sometimes problems have multiple sources
        // to start with, so it is same as pushing the multiple sources into the queue before bfs
        // if it happens to have only one source to start with, it is fine but make sure it costs 0, dist 0
        for (const pair<int, int> &src : source)
            bfs_check(q, src, {-1, -1}, 0, 0);

        while (!q.empty()) {
            pair<int, int> top = q.front();
            q.pop_front();
            int r = top.first, c = top.second;

            for (int dir = 0; dir < 4; dir++) {
                int nr = r + DIR_R4[dir];
                int nc = c + DIR_C4[dir];

                if (valid(nr, nc) && grid[nr][nc] >= 0) {
                    int cost = 1;
                    bfs_check(q, make_pair(nr, nc), top, dist[r][c] + cost, cost);
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // sometimes, memory size will exceed, then grid.clear();
    // https://codeforces.com/contest/1520/G
    int N, M;
    int64_t W;
    cin >> N >> M >> W;
    vector<vector<int>> grid(N, vector<int>(M));

    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
            cin >> grid[r][c];
    bfs_grid<vector<int>> bfs(grid);
    // grid.clear();

    bfs.bfs(vector<pair<int, int>>(1, {0, 0}));

    // for (auto x : bfs.parent)
    //     for (auto y : x)
    //         cout << y.first << " " << y.second << endl;

    int64_t answer = bfs.dist[N - 1][M - 1] < INF ? bfs.dist[N - 1][M - 1] * W : INF64;
    int64_t source_best = INF64, target_best = INF64;

    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
            if (bfs.grid[r][c] > 0 && bfs.dist[r][c] < INF)
                source_best = min(source_best, bfs.grid[r][c] + W * bfs.dist[r][c]);

    bfs.bfs(vector<pair<int, int>>(1, {N - 1, M - 1}));

    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
            if (bfs.grid[r][c] > 0 && bfs.dist[r][c] < INF)
                target_best = min(target_best, bfs.grid[r][c] + W * bfs.dist[r][c]);

    answer = min(answer, source_best + target_best);
    cout << (answer < INF64 / 2 ? answer : -1) << '\n';

    return 0;
}