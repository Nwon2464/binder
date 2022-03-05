#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> A = {1, 2, 3, 5, 6, 6, 5};
    // array need to be sorted otherwise won't work.
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());

    // if you dont want to sort it
    while (find(A.begin(), A.end(), 5) != A.end()) {
        A.erase(find(A.begin(), A.end(), 5));
    };
}
