#include <algorithm>

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // general prefix sum tech;
    // let prefix = new Array(H).fill(0).map(_=>new Array(W).fill(0));
    // for(let row = 0 ;row < H; row++){
    //     for(let col = 0; col < W; col++){
    //         prefix[row][col] = mat[row][col] + (row ? prefix[row-1][col]:0);
    //     }
    // }
    // prefix sum is same as builtin c++ partial sum
    // can compute fibonacci as well

    vector<int> A(5);
    for (int i = 0; i < 5; i++) {
        A[i] = i + 1;
    }
    vector<int> ans1(5);

    // A = {1,2,3,4,5}
    // before partial sum
    cout << A << endl;

    // same as prefix sum and move to ans1 vector
    // be ready for to choose size of ans1 like vector<int> ans1(5);
    // explicitly should be given.
    partial_sum(A.begin(), A.end(), ans1.begin());
    cout << ans1 << endl;

    // same as prefix sum but array recylce(no need to use another arrray) so to speak.
    // to A for prefix sum
    partial_sum(A.begin(), A.end(), A.begin());

    // prefix sum but all prefix vals + 1 ( except first one)
    partial_sum(A.begin(), A.end(), A.begin(), [](int x, int y) { return x + y + 1; });

    // fibonacchi series
    // A = {1,2,3,4,5}
    // A = {1,  2*1,  (2*1)*3, ((2*1)*3)*4, ((2*1)*3)*4)*5 }
    // A = {1,   2 ,     6 ,        24    ,        120     }
    partial_sum(A.begin(), A.end(), A.begin(), multiplies<int>());
}
