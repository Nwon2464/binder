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

// clang-format on
//------------------------------------------------------------
// searching in a map using map.find()
// int main() {
//      // declaring map
//      // of char and int
//      map<char, int> mp;

//      // declaring iterators

//      // inserting values
//      mp['a'] = 5;
//      mp['b'] = 10;
//      mp['c'] = 15;
//      mp['d'] = 20;
//      mp['e'] = 30;

//      // using find() to search for 'b'
//      // key found
//      // "it" has address of key value pair.
//      // auto == map<char, int>::iterator it
//      auto it = mp.find('b');

//      if (it == mp.end())
//           cout << "Key-value pair not present in map";
//      else
//           cout << "Key-value pair present : "
//                << it->first << "->" << it->second;

//      cout << endl;

//      // using find() to search for 'm'
//      // key not found

//      // "it1" has address of end of map.
//      // auto == map<char, int>::iterator it1
//      auto it1 = mp.find('m');

//      if (it1 == mp.end())
//           cout << "Key-value pair not present in map";
//      else
//           cout << "Key-value pair present : "
//                << it1->first << "->" << it1->second;
// }
//----------------------------------------------------------------
// usage of lower bound or upperbound for map
// int main() {
//      ios::sync_with_stdio(0);
//      cin.tie(0);
//      map<char, int> mp;
//      mp['a'] = 1;
//      mp['b'] = 2;
//      mp['c'] = 3;
//      mp['d'] = 4;
//      mp['e'] = 5;
//      mp['f'] = 6;
//      auto low = mp.lower_bound('b');
//      auto up = mp.upper_bound('e'); //points to 'f'
//      mp.erase(low, up); // erase[low,up) // til 'e'
//      // [ means inclusive , ) means less than = not inclusive
//      for (auto [a, b] : mp) {
//           cout << a << " " << b << endl;
//      }
// }
//-------------------------------------------------------------------
// sorting a map by value
// method 1 - move map to vector (copying all to vec pairs) and sort
// value descending order
// int comp(pair<int, int> a, pair<int, int> b) {
//      return a.second > b.second;
// }
// // value asecnding order
// int comp2(pair<int, int> a, pair<int, int> b) {
//      return a.second < b.second;
// }
// int main() {
//      ios::sync_with_stdio(0);
//      cin.tie(0);
//      map<int, int> mp;
//      rep(i, 1, 6) {
//           mp[i * 100]++;
//      }
//      mp[500]++;
//      mp[200]++;
//      mp[200]++;
//      mp[200]++;
//      // cout << mp;
//      vector<pair<int, int>> v(mp.begin(), mp.end());
//      cout << v;
//      sort(v.begin(), v.end(), comp2);
//      // sorting values (not keys)

//      cout << v;
// }

//Method 2 – using the set of pairs The idea is to insert all
// the (key-value) pairs from the map into a set of pairs
//that can be constructed using a comparator function
//that orders the pairs according to the second value.

// Comparison function for sorting the
// set by increasing order of its pair's
// second value
struct comp {
     template <typename T>

     // Comparator function
     // you can adjust it based on your implementation.
     // i.e (100,1) (300,1) (400,1) (500,2) (200,4)
     // l.second > r.second  gives values descending
     // l.second < r.second && l.first > r.first gives
     // values asceding, key desecnding if values are same
     bool operator()(const T& l,
         const T& r) const {
          if (l.second != r.second) {
               return l.second < r.second; // values
          }
          return l.first > r.first; // key
     }
};
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);

     map<int, int> mp;
     rep(i, 1, 6) {
          mp[i * 100]++;
     }
     mp[500]++;
     mp[200]++;
     mp[200]++;
     mp[200]++;
     set<pair<int, int>, comp> st(mp.begin(), mp.end());

     for (auto d : st) {
          cout << d << " ";
     }
}
