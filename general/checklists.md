
Time complexity
O(1) << O(log n) << O(sqrt(n)) << O(n) << O(n log n) << O(n^2) << O(n^3) << O(2^n) << O(n!)

input size Expected time complexity
  N       Worst TC(Expected TC)          Algorithms
n ≤ 10    O(n!)                         permutations,subsets
n ≤ 20    O(2^n)			  traveling sales man with DP
n ≤ 22    O(2^n * n)                     DP with bitwise
n ≤ 100   O(n^4)                         4 nested loops
n ≤ 500   O(n^3)                         floyd warshall
n ≤ 2000  O(n^2 * log n) 		  2 nested loops with binary Search
n ≤ 10^3  O(n^2)
n ≤ 10^4  O(n^2 or n(log)n^2)               Bubble sort

if input size more than 10^4, you must use o(n) solutions
n ≤ 10^5  O(n(log)n)
n ≤ 10^6 - 10^7 O(n log n), O(n)            greedy strategy,
n ≤ 10^8  O(log n) O(1)                     linear dp

if input size more than 10^10, you must use o(1) or o(log n) solutions
n ≤ 10^18 O(log n), o(1)                    n^th fibonaci


Constant O(1)
Logarithmic O(logn) Binary search, Searching a tree data structure.
Linear O(n)
Linearithmic O(nlogn) Heap sort, Merge sort, Quick sort
Quadratic O(n^2)
Polynomial O(n^C)
Exponential O(2^n)
Factorial O(n!)


Data Type		Size (in bytes)	Range
short int		2	-32,768 to 32,767
unsigned short int	2	0 to 65,535
unsigned int		4	0 to 4,294,967,295
int			4	-2,147,483,648 to 2,147,483,647   -2*10^9 <= int <= 2*10^9 (32-bit)
long int		8	-2,147,483,648 to 2,147,483,647
unsigned long int	8	0 to 4,294,967,295
long long int(ll,int64_t)8	-(2^63) to (2^63)-1    -9*10^18 <= ll <= 9*10^18 (64-bit)
__int128_t(rarely used)        -2^127 to 2^127-1                 -10^38 <= __int128_t <= 10^38 (128-bit)
unsigned long long int	8	0 to 18,446,744,073,709,551,615
signed char		1	-128 to 127
unsigned char		1	0 to 255
float			4
double			8
long double		12

--------------------------------------------------------------------------------

defines a long long variable:
long long x = 123456789123456789LL;

--------------------------------------------------------------------------------

Modular Arithmetic
Sometimes, the answer to a problem is a very large number,
it suffices to use the types int and long long
(a + b) mod m = (a mod m + b mod m) mod m
(a − b) mod m = (a mod m − b mod m) mod m
(a · b) mod m = (a mod m · b mod m) mod m

what if a remainder is negative?
An easy way to make sure there are no negative remainders is to first calculate the
remainder as usual and then add m if the result is negative:
x = x%m;
if (x < 0) x += m;
However, this is only needed when there are subtractions in the code, and the
remainder may become negative


--------------------------------------------------------------------------------
Floating Point Numbers (dont use float, just use double (precision of 15digits) )
double x = 0.3*3+0.1;
printf("%.20f\n", x); // 0.99999999999999988898
It is risky to compare floating point numbers with the == operator, because it is
possible that the values should be equal but they are not because of precision errors.
A better way to compare floating point numbers is to assume that two numbers are
equal if the difference between them is less than ε, where ε is a small number. For
example, in the following code ε = 10 −9 :

if (abs(a-b) < 1e-9) {
// a and b are equal
}

PRECISION ERROR for float, double type >> as a result, add +0.1
when you cin double
for example
double x;
cin >> x; // you typed 1.11, but IMPORTANT! it is saved as 1.1099999999999999(precision 15 of digits)
so there is precision error.
and when you dump your double x into lets say long long integer like
ll y = x * 100;
what would be the anwser of y?
it is not 111. it will be 110 because of precision error + any data type except decimal data
type (float, double),it always delete decimals.

In order to resolve this issue, or to come up with 111, you need to do +0.5 or +0.1
so ll y = x * 100 + 0.1 (not nesseccarily 0.1, its ok to plus 0.5 also)



---------------------------------------------------------------------------------
set and multiset (c++ standard library )
set is based on a balanced binary search tree and its operations work in O(log n)
time.
unordered_set is based on a hash table and its operations work, on average, 1
in O(1) time.

set structure also provides the functions lower_bound(x) and
upper_bound(x) that return an iterator to the smallest element in a set whose
value is at least or larger than x,

cout << *s.lower_bound(x) << "\n";
cout << *s.upper_bound(x) << "\n";
---------------------------------------------------------------------------------
map
map is based on a balanced binary search tree and accessing elements
takes O(log n) time, while unordered_map uses hashing and accessing elements
takes O(1) time on average.

----------------------------------------------------------------------------------
Priority Queues

A priority queue is a multiset that supports element insertion and, depending on the
type of the queue, retrieval and removal of either the minimum or maximum element.
Insertion and removal take O(log n) time, and retrieval takes O(1) time.
By default, the elements in a C++ priority queue are sorted in decreasing order,



