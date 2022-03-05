#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define rep(i, a, b) for (ll i = a; i < (b); ++i)
#define sfl(a) scanf("%lld", &a)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define mp make_pair
#define f first
#define s second
#define pb push_back
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, u, q;
    cin >> n >> m >> u >> q;
    vector<vector<ll>> a(n, vector<ll>(m));
    vector<vector<ll>> prefix(n, vector<ll>(m));
    vector<vector<ll>> sl(n, vector<ll>(m + 1, 0));

    rep(i, 0, n) rep(j, 0, m) cin >> a[i][j];

    while (u--) {
        ll k, r1, c1, r2, c2;
        cin >> k >> r1 >> c1 >> r2 >> c2;
        for (ll i = r1; i <= r2; i++) { // 10^3
            sl[i][c1] += k;
            sl[i][c2 + 1] -= k;
        }
    }

    for (ll i = 0; i < n; i++) { // 10^3
        ll sum = 0;
        for (ll j = 0; j < m + 1; j++) {
            sum += sl[i][j];
            a[i][j] += sum;
        }
    }

    rep(i, 0, n) rep(j, 0, m) prefix[i][j] = a[i][j] + (j ? prefix[i][j - 1] : 0);
    rep(i, 0, n) rep(j, 0, m) prefix[i][j] = prefix[i][j] + (i ? prefix[i - 1][j] : 0);

    while (q--) { // 10^5
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ll ans = 0;
        ans = prefix[x2][y2] + (x1 && y1 ? prefix[x1 - 1][y1 - 1] : 0) - (x1 ? prefix[x1 - 1][y2] : 0) - (y1 ? prefix[x2][y1 - 1] : 0);

        cout << ans << "\n";
    }
    return 0;
}
