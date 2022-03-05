#include <algorithm>
#include <array>
#include <bitset>
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
#define rep(i, a, b) for (ll i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define f first
#define s second
#define pb push_back

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

// const ll template_array_size = 1e6 + 4265;
// ll a[template_array_size];
// ll b[template_array_size];
// ll c[template_array_size];

const int mod = 1e9 + 7;

struct modint {
     ll n;
     modint()
         : n(0) { ; }
     modint(ll m)
         : n(m) {
          if (n >= mod)
               n %= mod;
          else if (n < 0)
               n = (n % mod + mod) % mod;
     }
     operator int() { return n; }
};
bool operator==(modint a, modint b) { return a.n == b.n; }
modint operator+=(modint& a, modint b) {
     a.n += b.n;
     if (a.n >= mod) a.n -= mod;
     return a;
}
modint operator-=(modint& a, modint b) {
     a.n -= b.n;
     if (a.n < 0) a.n += mod;
     return a;
}
modint operator*=(modint& a, modint b) {
     a.n = ((ll)a.n * b.n) % mod;
     return a;
}
modint operator+(modint a, modint b) { return a += b; }
modint operator-(modint a, modint b) { return a -= b; }
modint operator*(modint a, modint b) { return a *= b; }
modint operator^(modint a, ll n) {
     if (n == 0) return modint(1);
     modint res = (a * a) ^ (n / 2);
     if (n % 2) res = res * a;
     return res;
}

ll inv(ll a, ll p) {
     return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p);
}
modint operator/(modint a, modint b) { return a * modint(inv(b, mod)); }
modint operator/=(modint& a, modint b) {
     a = a / b;
     return a;
}
const int max_n = 1 << 20;
modint fact[max_n], factinv[max_n];
void init_f() {
     fact[0] = modint(1);
     for (int i = 0; i < max_n - 1; i++) {
          fact[i + 1] = fact[i] * modint(i + 1);
     }
     factinv[max_n - 1] = modint(1) / fact[max_n - 1];
     for (int i = max_n - 2; i >= 0; i--) {
          factinv[i] = factinv[i + 1] * modint(i + 1);
     }
}
modint comb(int a, int b) {
     if (a < 0 || b < 0 || a < b) return 0;
     return fact[a] * factinv[b] * factinv[a - b];
}
modint combP(int a, int b) {
     if (a < 0 || b < 0 || a < b) return 0;
     return fact[a] * factinv[a - b];
}
ll C2(ll n, ll r) { // up until
     // int n, r;
     // cin >> n >> r;
     __int128 ans = 1;

     for (int i = 1; i <= r; ++i) {
          ans *= n - i + 1;
          ans /= i;
     }

     return ll(ans);
}
int d(int n) {
     // find dearrangement exhaustive search.
     // very slow when n is greater than 10, recommended when n <=10
     // since next_permutation builtin function is used.
     // when n = 0, it is wrong answer; so better to use n>0 && n <=10
     vector<int> perm;
     for (int i = 0; i < n; i++) {
          perm.pb(i);
     }
     vector<int> ans;
     int cnt = 0;
     do {
          bool ok = 1;
          for (int i = 0; i < n; i++) {
               ok &= (i != perm[i]);
          }
          cnt += ok;

     } while (next_permutation(perm.begin(), perm.end()));

     return cnt;
}

int dearrangement(int n) {
     // dearrangement is any permutation of an array  no two elements in A and its permutation occur at same position.
     //{1 ,2 ,3 }
     //Derangements are (2, 3, 1), (3, 1, 2). i != p[i]
     if (n == 1 || n == 2) {
          cout << "Number of dearrangement in length " << n << " permutation\n";

          return n - 1;
     }
     int a = 0, b = 1;
     int c = 0;
     for (int i = 3; i <= n; i++) {
          c = (i - 1) * (a + b);
          a = b;
          b = c;
     }
     cout << "Number of dearrangement in length " << n << " permutation\n";
     return c;
}
// int main() {
//      // codeforces - almost identity permutation
//      ll n, k;

//      cin >> n >> k;

//      ll ans = 0;
//      if (k >= 2) ans += C2(n, 2);
//      if (k >= 3) ans += 2 * C2(n, 3);
//      if (k >= 4) ans += 9 * C2(n, 4);
//      cout << 1 + ans << '\n';
//      return 0;
// }

//smallest dearrangement sequence 1 to N
void least_generate_derangement(int N) {
     // Generate Sequence and insert into a
     // priority queue.
     int S[N + 1];
     priority_queue<int, vector<int>, greater<int>> PQ;
     for (int i = 1; i <= N; i++) {
          S[i] = i;
          PQ.push(S[i]);
     }

     // Generate Least Derangement
     int D[N + 1];
     for (int i = 1; i <= N; i++) {
          int d = PQ.top();
          PQ.pop();
          if (d != S[i] || i == N) {
               D[i] = d;
          } else {
               D[i] = PQ.top();
               PQ.pop();
               PQ.push(d);
          }
     }

     if (D[N] == S[N])
          swap(D[N - 1], D[N]);

     // Print Derangement
     printf("\nSmallest Derangement \n");

     for (int i = 1; i <= N; i++)
          printf("%d ", D[i]);
     printf("\n");
}
void largest_dearrangement(vector<int>& seq, int N) {
     int res[N]; // Stores result

     // Insert all elements into a priority queue
     std::priority_queue<int> pq;
     for (int i = 0; i < N; i++)
          pq.push(seq[i]);

     // Fill Up res[] from left to right
     for (int i = 0; i < N; i++) {
          int d = pq.top();
          pq.pop();
          if (d != seq[i] || i == N - 1) {
               res[i] = d;
          } else {

               // New Element poped equals the element
               // in original sequence. Get the next
               // largest element
               res[i] = pq.top();
               pq.pop();
               pq.push(d);
          }
     }

     // If given sequence is in descending order then
     // we need to swap last two elements again
     if (res[N - 1] == seq[N - 1]) {
          res[N - 1] = res[N - 2];
          res[N - 2] = seq[N - 1];
     }

     printf("\nLargest Derangement \n");
     for (int i = 0; i < N; i++)
          printf("%d ", res[i]);
}
modint dearrangement_inclusion_exclusion(int n) {

     modint ans = 0;
     //how many dearrangement? when n is large and mod is used.
     // answer may vary because factorial used mod
     for (int i = 0; i <= n; i++) {
          modint now = comb(n, i);
          now *= fact[n - i];
          if (i & 1) {
               now = -now;
          }
          ans += now;
     }
}

// Driver code
int main() {
     int n;
     cin >> n;
     cout << d(n) << endl; //find dearrangement exhaustive search using next_permutation
     cout << dearrangement(n) << endl; //n = 12 is max, n>=13 need to use ll.
     cout << dearrangement_inclusion_exclusion(n) << endl; // mod is used
     least_generate_derangement(4);
     vector<int> seq = { 1, 2, 3, 4 };
     largest_dearrangement(seq, (int)seq.size());
     return 0;
}