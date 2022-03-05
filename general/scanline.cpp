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

// 1s 10^8
// 2s 2*10^8
// 3s 3*10^8
// 100s 10^10
int main() {
    // 5
    // 3 2 3 1 2
    // 4
    // 1 3 1
    // 2 4 2
    // 0 2 3
    // 1 4 1

    // post -processing O(2*10^5)
    // scanline (need n+1 arr)
    // scan[l] += n;
    // scan[r+1] -= n;
    // int scan = 0;
    int N;
    cin >> N;
    vector<int> a(N);
    rep(i, 0, N) cin >> a[i];
    int q;
    cin >> q;
    vector<int> sl(N + 1);
    while (q--) { // O(q) + O(n);
        int L, R, n;
        cin >> L >> R >> n;
        sl[L] += n;
        sl[R + 1] -= n;
    }
    int scan = 0;
    for (int i = 0; i < N; i++) {
        scan += sl[i];
        a[i] += scan;
    }

    output_vector(sl);
    output_vector(a);

    return 0;
}
