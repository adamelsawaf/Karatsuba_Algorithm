# Karatsuba Algorithm
Implementation of the Karatsuba algorithm, a fast multiplication algorithm which multiplies two very large n-digit non-negative integers in time T(n) ∈ O(n ^ lg(3)) ≈ O(n ^ 1.585). This program stores the given integers as strings, and so the program is able to calculate products containing up to over four million digits.

Bash command to run this program (substitute non-negative integers for [INPUT1] and [INPUT2]):<br/>
**g++ karatsuba.cpp -o karatsuba && ./karatsuba [INPUT1] [INPUT2]**
which compiles the cpp file, creates an executable file called "karatsuba" in the directory, and runs that exectuable file.
