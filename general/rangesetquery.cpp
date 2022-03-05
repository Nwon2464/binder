#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
const int N = 2e6 + 1;

int c[N];
int p[N];
int f[N];
int ans[N];
int lz[N];
vector<pair<int, int>> qr[N];
void push(int id) {
     lz[id * 2] += lz[id];
     lz[id * 2 + 1] += lz[id];
     lz[id] = 0;
}
void upd(int id, int l, int r, int ql, int qr, int v) {
     if (l > qr || r < ql) return;
     if (ql <= l && r <= qr) {
          lz[id] += v;
          return;
     }
     push(id);
     int mid = (l + r) / 2;
     upd(id * 2, l, mid, ql, qr, v);
     upd(id * 2 + 1, mid + 1, r, ql, qr, v);
}
int qry(int id, int l, int r, int p) {
     if (l == r) return lz[id];
     push(id);
     int mid = (l + r) / 2;
     if (p <= mid)
          return qry(id * 2, l, mid, p);
     else
          return qry(id * 2 + 1, mid + 1, r, p);
}
int main() {
     ios::sync_with_stdio(false);
     int n, q;
     cin >> n >> q;
     for (int i = 1; i <= n; i++) {
          cin >> c[i];
          p[i] = f[c[i]];
          f[c[i]] = i;
     }
     for (int i = 1; i <= q; i++) {
          int l, r;
          cin >> l >> r;
          qr[r].push_back({ l, i });
     }
     for (int i = 1; i <= n; i++) {
          upd(1, 1, n, p[i] + 1, i, 1);
          for (auto c : qr[i]) {
               ans[c.se] = qry(1, 1, n, c.fi);
          }
     }
     for (int i = 1; i <= q; i++) {
          cout << ans[i] << '\n';
     }
}