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

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on
string mex(string &S) {
     vector<string> strings = {""};
     while (1) {
          vector<string> mexstrings;
          for (auto x : strings) {
               for (int i = 0; i < 26; i++) {
                    string str = x + char('a' + i);
                    mexstrings.push_back(str);
                    int a = S.find(str);
                    if (S.find(str) ==
                        S.npos) {  // npos used to indicate no matches.
                         return str;
                    }
               }
          }
          swap(strings, mexstrings);
     }
}

void run_case() {
     int N;
     string S;
     cin >> N >> S;
     cout << mex(S) << '\n';
}

int main() {
     int tests;
     cin >> tests;

     string S = "qaabzwsxedcrfvtgbyhnujmiklop";
     int a = S.find("a");  // index of first char occurrence // 1
     string str = "aa";
     if (S.find(str) == S.npos) {
     }  // npos used to indicate no matches.
     if (S.find(str) == string::npos) {
     }  // npos alternatives without using S.

     // generating character lexicalgraphically
     vector<string> strings = {""};
     for (int i = 0; i < 26; i++) {
          char nstr = char('a' + i);
          cout << nstr << endl;  // a b c d ... z
     }

     // generating character lexicalgraphically until find target string
     // https://codeforces.com/contest/1536/problem/B
     // a,b,c,...z, aa,ab,ac,ad,ae,zz
     // string mex(string& S) {
     //      vector<string> strings = { "" };

     //      while (true) {
     //           vector<string> nstrings;

     //           for (auto& str : strings)
     //                for (int c = 0; c < 26; c++) {
     //                     string nstr = str + char('a' + c);
     //                     nstrings.push_back(nstr);

     //                     if (S.find(nstr) == string::npos)
     //                          return nstr;
     //                }

     //           strings.swap(nstrings);
     //      }
     // }
     return 0;
}