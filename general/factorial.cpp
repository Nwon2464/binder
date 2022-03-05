#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e6 + 7;
ll fact[N], mod = 1e9 + 7;

// precomputes all factorial [1!,2!,3!,....N]
// O(N)  time
void precal_factmod(ll n) {
     fact[0] = 1;
     for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % mod;
}

// find one n! based on precalculated factorials
ll getone_factmod(ll n) {
     fact[0] = 1;
     for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % mod;

     ll res = 1;
     while (n > 1) {
          if ((n / mod) % 2) res = mod - res;
          res = res * fact[n % mod] % mod;
          n /= mod;
     }
     return res;
}

int main() {
     precal_factmod(5);          //  [1! , 2!, 3!, 4! ,5!]
     cout << getone_factmod(5);  //   5!
     return 0;
}
