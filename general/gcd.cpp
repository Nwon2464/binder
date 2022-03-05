#include <bits/stdc++.h>

using namespace std;
using ll = long long;
// gcd, lcm, extgcd, binarygcd

ll gcd(ll a, ll b);

// Least common multiple

ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

/*Euclidean algorithm for computing the greatest common divisor
GCD (2,0) or (0,2) is always actual number, which is 2 (in theory, it is 0)
*/

// recursive
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

// iterative
ll gcd_iterative(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

/*
-----------------
Time Complexity |
O(logmin(a,b))  |
-----------------
*/
// -------------------------------------------------------------------

/*Binary GCD
The Binary GCD algorithm is an optimization to the normal Eulidean algorithm.
The slow part of above algorithm are the modulo operations. so Binary GCD would work faster.
*/
int bsf(uint64_t x) { return __builtin_ctzll(x); }

int gcd(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b); // << ll or int?
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}

// ---------------------------------------------------------------------
/*Extended Euclidean algorithm

While the Euclidean algorithm calculates only the greatest common divisor (GCD) of two integers a and b, the extended
version also finds a way to represent GCD in terms of a and b, i.e. coefficients x and y for which:

a⋅x+b⋅y=gcd(a,b)
Interesting point: even if coefficient of x and y are random number,
you can stil get right GCD of a and b
*/
int extendedgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extendedgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
