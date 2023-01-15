# Karatsuba Algorithm
Implementation of the Karatsuba algorithm, a fast multiplication algorithm which multiplies two very large n-digit non-negative integers in time O(n^lg(3)) ≈ O(n^1.585), asymptotically faster than the naïve algorithm of O(n^2). This program stores the given integers as strings, and so the program is able to calculate products containing up to over four million digits. <br/>

The product and computation time are printed out to the console.

Bash command to run this program (substitute non-negative integers for [INPUT1] and [INPUT2]):<br/>
**g++ karatsuba.cpp -o karatsuba && ./karatsuba [INPUT1] [INPUT2]**<br/>
which compiles the cpp file, creates an executable file called "karatsuba" in this directory, and runs that exectuable file.
