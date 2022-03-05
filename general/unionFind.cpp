#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < (b); ++i)

using namespace std;
struct union_find {
    vector<int> r;
    union_find(int N) {
        r = vector<int>(N, -1);
    }
    int root(int x) {
        if (r[x] < 0)
            return x;
        return r[x] = root(r[x]);
    }
    // unite means .. im going to connect x and y,but  if x and y is already connected return false
    // if x and y is not connected, return true for success connectivity
    // if(!unite(x,y)) means, if x and y is already conencted, there 's nothing i can do. return false.
    // if(unite(x,y)) means, if x and y have not been connected before but now will connect it return true
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y)
            return false;
        if (r[x] > r[y])
            swap(x, y);
        r[x] += r[y];
        r[y] = x;
        return true;
    }
    int size(int x) {
        return -r[root(x)];
    }

    bool find_if_roots_are_same(int x, int y) {
        return root(x) == root(y);
    }
};

int main() {
    // 5 3   n, m

    // 1 2
    // 3 4
    // 5 1

    int n, m;
    cin >> n >> m;
    union_find uf(n);
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        uf.unite(a, b);
    }

    int ans = 0;
    rep(i, 0, n) ans = max(ans, uf.size(i));
    cout << ans << endl;
    return 0;
}

// clang-format off


// union find problem 1
// https://codeforces.com/contest/25/problem/D  difficulty 1900
// short explanation of the problem
// suppose you have array, and some of values are connected to each other
// 1. how do you find a cycle in graphs?
// 2. how do you connect two seperate graphs to one graph (like merging or
// uniting)?

// answer 1
// to detect a cycle, it is safe to say that we can check if root between two
// values is same or not when we cin. so root is same, then it has a cycle,
// otherwise no cycle. like this vector<pair<int,int>> cycle; rep(i,0,Query){
//    int x , y;
//    cin >> x >> y;
//    --x, --y;   (0 indexing)
//    if(uf.find_if_roots_are_same(x,y)){  (if root are same between two values)
//         cycle.push_back(x,y);
//         continue;
//    }
//    uf.unite(x,y);
//    }
// then, we can easily find a cycle coordinates and push back to other vector

// answer 2
// to connect or bridge between two seperate graphs to one graph, we need to know how to iterate pairs where i != j
// we need 2 for loop where iterating over all the points (i,j) do you remember ? how to loop
// through all the pairs where i != j

// 2 ways to loop through all the pairs
// 1 way                                             2 way
// for (int i = 0; i < n; i++) {                     for(int i = 0 ; i < n ; i++){
//      for (int j = i + 1; j < n; j++) {                 for(int j = 0; j < i ; j ++){
//           cout << i + 1 << " " << j + 1 << endl;           cout << i + 1 << " " << j + 1 << endl;
//      }                                                 }
// }                                                 }

// now we figured out how to iterate over all the pairs
// then, how do you connect between two seperate graphs?
// same as problem 1, we first need to find out if root A and B are same or not
// unlike the above condition where we need to find out if root are same
// at this time, we need to find if root is different because we are targeting disjoint bridges or unconnected lines
// to connect each other. lastly, important ! we need to unite those pairs when we find out the roots are different

// vector<pair<int, int>> connect;
//      for (int i = 0; i < n; i++) {
//           for (int j = i + 1; j < n; j++) {
//                if (!uf.find_if_roots_are_same(i, j)) {
//                     connect.push_back({i, j});
//                     uf.unite(i, j);    <--- where i messed up, be sure to unite when you find out unconnected graph
//                     continue;
//                }
//           }
//      }

// that's the solution for union find
// clang-format on