# Karatsuba Algorithm
Implementation of the Karatsuba algorithm, a fast multiplication algorithm which multiplies two very large n-digit non-negative integers in time O(n^lg(3)) ≈ O(n^1.585), asymptotically faster than the naïve algorithm of time O(n^2). This program stores and performs calculations on the given integers as strings, and so the program is able to calculate products containing up to over four million digits. <br/>

The product and computation time are printed out to the console, for both the naïve and Karatsuba multiplications.

Bash command to run this program (substitute non-negative integers for [INPUT1] and [INPUT2]):<br/>
**g++ karatsuba.cpp -o karatsuba && ./karatsuba [INPUT1] [INPUT2] && rm karatsuba**<br/>
which compiles the cpp file, creates an executable file called "karatsuba" in this directory, runs that executable file, and deletes the executable file when it's finished.

Run the test script **karatsuba_test.sh** by running the following Bash command:<br>
**bash karatsuba_test.sh**<br>
This test case multiplies a 13500-digit integer with itself, and so the multiplication is likely large enough
(the maximum of the number of digits of the two numbers being multiplied) for the Karatsuba algorithm to
calculate the result faster than the naïve algorithm. This is because Karatsuba is asymptotically faster than
the naïve algorithm, so Karatsuba is not usually faster for smaller multiplications, but for larger
multiplications after some threshold, Karatsuba will become always faster than the naïve algorithm. Note that
the following command may take some time to complete running, depending on the hardware of your device. 
Plugging in your device and maximizing its performance settings while this command is running is highly
recommended to speed up the multiplication.
