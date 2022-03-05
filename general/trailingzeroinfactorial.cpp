#include <iostream>
#include <limits.h>
using namespace std;
int64_t countTrailingZeros3(int64_t n) {
    // verified at CSES
    int64_t res = 0;
    for (int64_t i = 5; n / i >= 1; i = i * 5) {
        res = res + (n / i);
    }
    return res;
}
int64_t countTrailingZeros1(int64_t n) {
    int64_t res = 0;
    for (int64_t i = 5; i <= n; i = i * 5) {
        res = res + (n / i);
    }
    return res;
}
int64_t countTrailingZeros2(int64_t n) {
    int64_t res = 0;
    for (int64_t i = 2; i <= n; i = i * 2) {
        res = res + (n / i);
    }
    return res;
}
// trailing zero, 2 or 5
int main() {
    int64_t number = 251;
    cout << countTrailingZeros(number);
    return 0;
}