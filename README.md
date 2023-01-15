# Karatsuba_Algorithm
Implementation of the Karatsuba Algorithm, a fast multiplication algorithm which multiplies two very large n-digit non-negative integers in time T(n) ∈ O(n ^ lg(3)) ≈ O(n ^ 1.585). This program stores the given integers as strings, and so the program is able to calculate products containing up to overfour million digits.

Bash command to run this program (substitute non-negative integers for [INPUT1] and [INPUT2]):

*g++ karatsuba.cpp -o karatsuba && ./karatsuba [INPUT1] [INPUT2]*
