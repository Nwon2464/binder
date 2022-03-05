#include <iostream>
// clang-format off
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename num_t>
using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;
// clang-format on

// ordered_set DOES ALLOW duplicates. less_equal<num_t> makes ordered_set multiset
// BUT! when using less_equal<num_t>, lower_bound and upper_bound work OPPOSITELY. Also, let's say you want to erase x, use s.erase(s.upper_bound(x))
// (as upper bound is considered as lower bound)
// technique to erase the value in multiset. since lower,upper is oppsite, kind of cucumbersome so
// alternatvie way to erase val os.erase(os.find_by_order(os.order_of_key(x)));

// template <typename num_t>
// using ordered_set = tree<num_t, null_type, less_equal<num_t>, rb_tree_tag, tree_order_statistics_node_update>;

// os.find_by_order(x) 0-index k-th smallest element
// find_by_order return iterator for number of items of kth-element counting from 0 -O(logn) time
// os.order_of_key(x)  how many elements that are less than me exists?
// order_of_key returns number of items that are strictly smaller

// https://www.spoj.com/problems/ORDERSET/ tested
// https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/ reference

int main() {

    ordered_set<int> os;

    os.insert(1);
    os.insert(2);
    os.insert(3);
    os.insert(4);
    os.insert(5);
    os.insert(6);
    os.insert(7);
    os.insert(8);

    for (auto x : os) {
        cout << x << " ";
    }

    cout << endl;
    // os[0] = 1, os[1] = 2, os[2] = 3 ...... os[7]=8

    // normal set vs ordeded_set for finding a lower_bound of value and lower_bound-1 of value
    // cout << *os.find_by_order(os.order_of_key(x)) - *os.find_by_order(os.order_of_key(x) - 1) << endl;
    // cout << *st.lower_bound(x) - *prev(st.lower_bound(x)) << endl;

    cout << *os.find_by_order(5) << endl; // answer 6.  0-index k-th smallest element
    cout << os.order_of_key(5) << endl;   // answer 4. how many elements that are less than 5 exists?
    cout << *os.lower_bound(3) << endl;   // return value 3. lower_bound of 3
    // os.lower_bound(3);    // return iterator of position 3
    cout << *os.lower_bound(9) << endl; // return value 0. lower_bound of 9

    os.erase(os.lower_bound(3));

    for (auto x : os) {
        cout << x << " ";
    }

    cout << endl;
    // https://cses.fi/problemset/task/1144/
    // query: change 3rd index to 6 in array A

    // [3 7 2 2 5] = A (1based index) -> [3 7 6 2 5]
    // os = 2 2 3 5 7
    //      |
    // os.erase(os.find_by_order(os.order_of_key(A[x])));

    // A[3] = 2
    // order_of_key(2) how many? less than 2 ?
    // return value of 0 th (same as iterator pointer or can be value)
    // find_by_order(0)
    // return iterator of 0 th element in ordered_set
    // erase it
    return 0;
}
