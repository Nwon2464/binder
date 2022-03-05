#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sfl(a) scanf("%lld", &a)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define mp make_pair
#define f first
#define s second
#define pb push_back
const int mod = 1e9 + 7;
template <typename T>
istream& operator>>(istream& is, vector<T>& vec)
{
    for (auto& v : vec)
        is >> v;
    return is;
}
template <typename A, typename B>
istream& operator>>(istream& cin, pair<A, B>& p)
{
    cin >> p.first;
    return cin >> p.second;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
    os << "[";
    for (auto v : vec)
        os << v << ",";
    os << "]";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const deque<T>& vec)
{
    os << "deq[";
    for (auto v : vec)
        os << v << ",";
    os << "]";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const set<T>& vec)
{
    os << "{";
    for (auto v : vec)
        os << v << ",";
    os << "}";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const unordered_set<T>& vec)
{
    os << "{";
    for (auto v : vec)
        os << v << ",";
    os << "}";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const multiset<T>& vec)
{
    os << "{";
    for (auto v : vec)
        os << v << ",";
    os << "}";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const unordered_multiset<T>& vec)
{
    os << "{";
    for (auto v : vec)
        os << v << ",";
    os << "}";
    return os;
}
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& pa)
{
    os << "(" << pa.first << "," << pa.second << ")";
    return os;
}
template <typename TK, typename TV>
ostream& operator<<(ostream& os, const map<TK, TV>& mp)
{
    os << "{";
    for (auto v : mp)
        os << "(" << v.first << ":" << v.second << ")"
           << ",";
    os << "}";
    return os;
}
template <typename TK, typename TV>
ostream& operator<<(ostream& os, const unordered_map<TK, TV>& mp)
{
    os << "{";
    for (auto v : mp)
        os << v.first << "=>" << v.second << ",";
    os << "}";
    return os;
}
template <typename T>
void ndarray(vector<T>& vec, int len, T init) { vec.assign(len, init); }
template <typename T, typename... Args>
void ndarray(vector<T>& vec, int len, Args... args)
{
    vec.resize(len);
    for (auto& v : vec)
        ndarray(v, args...);
}
template <typename T>
bool bmax_self(T& m, const T q)
{
    if (m < q) {
        m = q;
        return true;
    } else
        return false;
}
template <typename T>
bool bmin_self(T& m, const T q)
{
    if (m > q) {
        m = q;
        return true;
    } else
        return false;
}
template <typename T1, typename T2>
pair<T1, T2> operator+(const pair<T1, T2>& l, const pair<T1, T2>& r) { return make_pair(l.first + r.first, l.second + r.second); }
template <typename T1, typename T2>
pair<T1, T2> operator-(const pair<T1, T2>& l, const pair<T1, T2>& r) { return make_pair(l.first - r.first, l.second - r.second); }
template <typename T>
void add_self(T& a, const T b)
{
    a += b;
    if (a >= mod) {
        a -= mod;
    }
}
template <typename T>
void sub_self(T& a, const T b)
{
    a -= b;
    if (a < 0) {
        a += mod;
    }
}
template <typename T>
void max_self(T& a, const T b) { a = max(a, b); }
template <typename T>
void min_self(T& a, const T b) { a = min(a, b); }
priority_queue<int> max_pq;
priority_queue<int, vector<int>, greater<int>> min_pq;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int arr[] = { 10, 20, 5, 23, 42, 15, 20, 20 };
    int n = sizeof(arr) / sizeof(arr[0]);

    vector<int> a(arr, arr + n);

    //1.sort
    //sort(a.begin(),a.end());

    //2.reverse
    //reverse(a.begin(),a.end());

    //3.max_element (use *)
    //cout << *max_element(a.begin(),a.end());

    //4.min_element (use *)
    //cout << *min_element(a.begin(),a.end());

    //5.accumulate
    //cout << accumulate(a.begin(),a.end(),0);

    //7.count
    //cout << count(a.begin(), a.end(), 20); // 2

    //8.find
    //auto it = find(a.begin(),a.end(), 2) != a.end(); //return 1 or 0
    //cout << it;

    //9.lower_bound
    //Sort!!!!!!!!! the array to make sure that lower_bound() and upper_bound() work.
    //sort(a.begin(),a.end());
    //vector<int>::iterator it;   OR auto it
    //it = lower_bound(a.begin(),a.end(),20); // explicitly saying iterator
    //auto it = lower_bound(a.begin(),a.end(),20); // using auto
    //output in 2ways
    //cout << it-a.begin(); //first
    //cout << distance(a.begin(),it); //second
    //MORE POWER WAY
    //using normal array: int a[] = {1,2,3,3}; int idx = lower_bound(a,a+n,t) - a;
    //using vector : vector<int> a = {1,2,3,3} int idx = lower_bound(a.begin(),a.end(),t) - a.begin();
    // condition check if(idx < n && a[idx] == target)

    //10.upper_bound (should be sorted)
    //sort(a.begin(),a.end());
    //vector<int>::iterator it;
    //it = upper_bound(a.begin(),a.end(),20);
    //cout << it-a.begin();
    //cout << distance(a.begin(),it);
    // MORE POWERWAY
    //using normal array: int a[] = {1,2,3,3}; int idx = upper_bound(a,a+n,t) - a;
    //using vector : vector<int> a = {1,2,3,3} int idx = upper_bound(a.begin(),a.end(),t) - a.begin();
    // condition check if(idx >= 0 && a[idx] == target)

    //11.erase  This erases selected element in vector and shifts and resizes the vector elements accordingly.
    //cout << a;
    //a.erase(a.begin()+1);
    //cout << a;

    //12.NOT RECOMMENDED erase This removes duplicate occurrences (should be SORTED and only deletes one duplicate and one occurrences) INEFFICIENT
    //sort(a.begin(),a.end());
    //cout << a;
    //a.erase(unique(a.begin(),a.end()),a.end()); // delete only 1
    //cout << a;

    //13.next_permutations
    //vector<int> permutation;
    //vector<vector<int>> ans;
    //for (int i = 0; i < 3; i++) {
    //permutation.push_back(i);
    //}
    //do {
    //ans.push_back(permutation);
    //} while (next_permutation(permutation.begin(),permutation.end()));
    //cout << ans;

    //14.distance is very useful finding the index.
    //cout << distance(a.begin(),max_element(a.begin(),a.end()));// find the distance btw index 0 and max
    //cout << a;

    return 0;
}
