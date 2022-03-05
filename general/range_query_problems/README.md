This folder goes through about Range Query problems.

You are given an array A[1...N]. you have to answer incoming queries of the form (L,R) L and R inclusive.

There are lots of possible approaches and data structures that you can use to solve Range Query problems.

The approaches that allow modifications to the array between answering queries (same as allowing to update as it receives queries)
1.Sqrt-decomposition - answers each query in O(sqrt(N)), preprocessing done in O(N). Pros: a very simple data structure. Cons: worse complexity.
2.Segment tree - answers each query in O(logN), preprocessing done in O(N). Pros: good time complexity. Cons: larger amount of code compared to the other data structures.
3.Fenwick tree - answers each query in O(logN), preprocessing done in O(NlogN). Pros: the shortest code, good time complexity. Cons: Fenwick tree can only be used for queries with L=1, so it is not applicable to many problems.


The approaches that only work on static arrays. It is not possible to change a value in the array without recomputing the complete data structure.
1.Sparse Table - answers each query in O(1), preprocessing done in O(NlogN). Pros: simple data structure, excellent time complexity. (sparse_rmq in binder) 
2.Sqrt Tree - answers queries in O(1), preprocessing done in O(NloglogN). Pros: fast. Cons: Complicated to implement.
3.Disjoint Set Union / Arpa's Trick - answers queries in O(1), preprocessing in O(n). Pros: short, fast. Cons: only works if all queries are known in advance, i.e. only supports off-line processing of the queries.
4.Cartesian Tree and Farach-Colton and Bender algorithm - answers queries in O(1), preprocessing in O(n). Pros: optimal complexity. Cons: large amount of code.

APPROACHES THAT ONLY WORKS ON STATIC ARRAY are the problems like... 
1. RMQ(Range Minimum Query)
2. RSQ(Range Sum Query) 
3. RMQ(Range Maximum Query)
4. RGQ(Range GCD Query)


All the Query problems
https://cp-algorithms.com/data_structures/sparse-table.html

Range Minimum Query - https://www.spoj.com/problems/RMQSQ/ (solved)
Range Maximum Query - https://www.spoj.com/problems/THRBL/ (solved) used neal's RMQ template(maximum), and compare index queries  with Left 

https://codeforces.com/contest/475/problem/D
https://codeforces.com/problemset/problem/514/D
https://codeforces.com/problemset/problem/872/B
https://www.spoj.com/problems/TNVFC1M/
https://codeforces.com/contest/713/problem/D
https://www.spoj.com/problems/RPLN/
https://www.spoj.com/problems/POSTERIN/
https://codeforces.com/contest/675/problem/E	
https://www.codechef.com/problems/SEAD
https://www.codechef.com/problems/MSTICK


