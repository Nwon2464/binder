#include <iostream>

using namespace std;

int64_t floor_divison(int64_t a, int64_t b) { return a / b - ((a ^ b) < 0 && a % b != 0); }
int64_t ceil_divison(int64_t a, int64_t b) { return a / b + ((a ^ b) > 0 && a % b != 0); }
int main() {
     int a, b;
     cin >> a >> b;
     cout << floor_divison(a, b) << endl;
     cout << ceil_divison(a, b) << endl;

     return 0;
}