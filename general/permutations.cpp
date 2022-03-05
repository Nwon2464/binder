// The number of permutations of n objects taken r at a time is given by the formula:
// P(n,r) = n!/(n - r)!

// The number of combinations of n objects taken r at a time is given by the formula:
// C(n,r) = n!/[r!(n - r)!]

// how many permutations are there of two letters from the set {a,b,c}?
// P(3,2) = 3!/(3-2)! = 6
// The list of all of these are: ab, ba, bc, cb, ac and ca.

// Now we will answer the following question: how many combinations are there of two letters from the set {a,b,c}?

// As combinations, ab and ba are regarded as the same. Thus there are only three combinations: ab, ac and bc.
// C(3,2) = 3!/[2!(3 - 2)!]

// https://leetcode.com/problems/combination-sum-iii/discuss/777779/C%2B%2B-Easy-Solution-using-Backtracking.Template-for-all-combination-Sum-problems.
