/*******************************************************************************
 *  File name   : karatsuba.cpp
 *  Author      : Adam El-Sawaf
 *  Version     : 1.5
 *  Date        : 11/17/21
 *  Description : Implementation of the Karatsuba algorithm, a fast multiplication algorithm which multiplies
 *                two very large n-digit non-negative integers in time O(n ^ lg(3)) ≈ O(n ^ 1.585), asymptotically
 *                faster than the naïve algorithm of time O(n^2). This program stores the given integers as strings,
 *                and so the program is able to calculate products containing up to over four million digits. The
 *                product and computation time are printed out to the console, for both the naïve and Karatsuba algorithm.
 *                
 *  Bash command to run this program (substitute non-negative integers for [INPUT1] and [INPUT2]):
g++ karatsuba.cpp -o karatsuba && ./karatsuba [INPUT1] [INPUT2] && rm karatsuba
 *  which compiles the cpp file, creates an executable file called "karatsuba" in this directory, runs that executable file, and deletes the executable file.
 ******************************************************************************/

#include <string.h>               //  string type, strcmp()
#include <sstream>                //  stringstream type
#include <iostream>               //  cout output stream
#include <iomanip>                //  setw()
using namespace std;

#include <math.h>                 //  log2(), floor(), ceil(), abs()

#include <chrono>                 //  high_resolution_clock type
using namespace std::chrono;

#include <regex>                  //  regex_match(), regex()


//  Takes the string representation of an integer and returns that integer.
long long stringToNum(const string& str) {
    unsigned long long num;
    stringstream ss;
    ss << str;
    ss >> num;
    return num;
}


//  Takes a non-negative integer and returns the string representation of that integer
//  (just make the argument signed to work for negative numbers).
string numToString(const unsigned long long num) {
    string str;
    stringstream ss;
    ss << num;
    ss >> str;
    return str;
}


//  Returns a given string with a given number of "0"s prepended to it (this doesn't change
//  the value of the string's integer representation). (NOT USED for speed reasons)
string padZeros(const string& s, const unsigned long long zeros) {
    return string(zeros, '0') + s;
}


//  Prepends "0"s to a string so its length is an integer power of 2. (NOT USED for speed purposes)
string padZerosPowerTwo(const string& s) {
    return s.empty() ? "" : string(pow(2, ceil(log2(s.length()))) - s.length(), '0') + s;
}


//  Pads zeros to two strings so they both have the same length.
void padZerosSameLength(string& a, string& b) {
    (a.length() > b.length())   ?   (b = string(a.length() - b.length(), '0') + b)    :   (a = string(b.length() - a.length(), '0') + a);
}


//  Returns a given string without any leading "0"s.
string noLeadingZeros(const string& s) {
    string result = "";
    for(size_t i = 0; i < s.length(); i++) {
        if((s[i] != '0') || (i == s.length() - 1)) {
            result.append(s.substr(i));
            return result;
        }
    }
    return result;
}


//  Returns a given string with a given number of "0"s appended to it (representing an integer).
//  In other words, the "integer" is multiplied by the base that number of times). (NOT USED for speed purposes)
string leftShift(const string& s, const unsigned long long shifts) {
    return s + string(shifts, '0');
}


//  Returns the ith character of a string, as a string. (NOT USED for speed purposes)
string charAt(const string& s, const unsigned long long i) {
    return s.substr(i, 1);
}


//  Sets the ith character of a string to given string. (NOT USED for speed purposes)
void setChar(string& str, const unsigned long long i, const string& c) {
    str = str.substr(0, i) + c + str.substr(i + 1, str.length() - 1 - i);
}


//  Adds two strings representing non-negative integers and returns their sum as a string.
string add(const string& a, const string& b) {
    string result       = "" ,
           carry        = "0",
           currentSum,
           aPadded      = noLeadingZeros(a),
           bPadded      = noLeadingZeros(b);
           
    padZerosSameLength(aPadded, bPadded);
    
    for(size_t i = aPadded.length() - 1; i >= 1; i--) {
        currentSum = numToString(stringToNum(aPadded.substr(i, 1)) + stringToNum(bPadded.substr(i, 1)) + stringToNum(carry));
        currentSum = string(max(0, (int) (2 - currentSum.length())), '0') + currentSum;
        result     = currentSum.substr(1, 1) + result;
        carry      = currentSum.substr(0, 1);
    }
    
    return noLeadingZeros(numToString(stringToNum(aPadded.substr(0, 1)) + stringToNum(bPadded.substr(0, 1)) + stringToNum(carry)) + result);
}


//  Subtracts two strings representing non-negative integers and returns their difference as a string. This function
//  assumes that the difference is non-negative, and will abort and throw an std::out_of_range exception otherwise.
string subtract(const string& a, const string& b) {
    string result  = "",
           aPadded = noLeadingZeros(a),
           bPadded = noLeadingZeros(b);
    
    padZerosSameLength(aPadded, bPadded);

    int currentDigit_a, currentDigit_b, currentDifference, carrier;
    
    for(int i = aPadded.length() - 1; i >= 0; i--) {
        currentDigit_a = stringToNum(aPadded.substr(i, 1));
        currentDigit_b = stringToNum(bPadded.substr(i, 1));
        currentDifference = currentDigit_a - currentDigit_b;
        
        if(currentDifference < 0) {
            currentDifference += 10;
            carrier = i - 1;

            while(aPadded[carrier] == '0')
                aPadded[carrier--] = '9';
            
            aPadded[carrier] = numToString(stringToNum(aPadded.substr(carrier, 1)) - 1)[0];
        }
        
        result = numToString(currentDifference) + result;
    }
    
    return noLeadingZeros(result);
}


/*
    Subtracts two strings representing non-negative integers and returns their difference as a string. This
    function also works when the difference is negative, but is very slightly slower due to a few extra branches.
    (NOT USED for speed purposes)
*/
string subtractNegative(const string& a, const string& b) {
    string result = "",
           aPadded = noLeadingZeros(a),
           bPadded = noLeadingZeros(b);

    padZerosSameLength(aPadded, bPadded);
    
    int currentDigit_a, currentDigit_b, currentDifference, carrier;
    
    for(int i = aPadded.length() - 1; i >= 0; i--) {
        currentDigit_a = stringToNum(aPadded.substr(i, 1));
        currentDigit_b = stringToNum(bPadded.substr(i, 1));
        currentDifference = currentDigit_a - currentDigit_b;
        
        if(currentDifference < 0) {
            if(i == 0)
                return "-" + subtract(bPadded, aPadded);    //  no more digits to carry from, so result is negative
            else {
                currentDifference += 10;
                carrier = i - 1;

                while(aPadded[carrier] == '0') {
                    aPadded[carrier--] = '9';
                    if(carrier == -1)
                        return "-" + subtract(bPadded, aPadded);    //  no more digits to carry from, so result is negative
                }
                
                aPadded[carrier] = numToString(stringToNum(aPadded.substr(carrier, 1)) - 1)[0];
            }
        }
        
        result = numToString(currentDifference) + result;
    }
    
    return noLeadingZeros(result);
}


//  Multiplies two strings representing integers and returns their product as a string, using repeated addition.
//  (NOT USED for speed purposes)
string multiply_repeatedAdditions(const string& a, const string& b) {
    const string aNLZ = noLeadingZeros(a);
    string result = "0";
    for(unsigned long long i = 0; i < stringToNum(b); i++)
        result = add(result, aNLZ);
    return result;
}


//  Multiplies two strings representing integers and returns their product as a string, using the naive
//  multiplication algorithm.
string multiply_naive(const string& a, const string& b) {
    string result          = "0",
           carry           = "0",
           ith_product     = "" ,
           jth_product,
           aPadded         = a,
           bPadded         = b;

    padZerosSameLength(aPadded, bPadded);

    for(long long i = bPadded.length() - 1; i >= 0; i--) {
        for(long long j = aPadded.length() - 1; j >= 1; j--) {
            jth_product = numToString((stringToNum(aPadded.substr(j, 1)) * stringToNum(bPadded.substr(i, 1)))   +   stringToNum(carry));
            jth_product = string(max(0, (int) (2 - jth_product.length())), '0') + jth_product;
            ith_product = jth_product[1] + ith_product;
            carry       = jth_product[0];
        }

        result = add(result,
                     (numToString((stringToNum(aPadded.substr(0, 1)) * stringToNum(bPadded.substr(i, 1)))   +   stringToNum(carry))   +   ith_product)
                     + string(aPadded.length() - 1 - i, '0'));
        ith_product = "";
        carry       = "0";
    }

    return noLeadingZeros(result);
}



/*
    This is the Karatsuba multiplication algorithm, which utilizes all of the helper functions in
    this program (above) to return the product of two non-negative integers a and b (all stored as
    strings, since strings can store representations of numbers greater than any numerical data type
    in C++ can). a and b are first padded with zeros to have the same length of a power of 2, then
    recursively split in half such that only single-digit integers are "normally" multiplied, a
    trade-off of multiplications to many more additions, which are generally faster.
*/
string karatsuba(const string& a, const string& b) {
    if(a.length() == 1 && b.length() == 1)
        return numToString(stringToNum(a) * stringToNum(b));      //  this is the base case (naive two single-digits multiplication)
    else {
        string aPadded = a,
               bPadded = b;
        padZerosSameLength(aPadded, bPadded);
        if(aPadded.length() % 2 != 0) {     //  pad a zero if they are odd length
            aPadded = '0' + aPadded;
            bPadded = '0' + bPadded;
        }

        const unsigned long long n = aPadded.length();
        const string a1 = aPadded.substr(0, n/2),  //  left  half of aPadded
                     a0 = aPadded.substr(n/2),     //  right half of aPadded
                     b1 = bPadded.substr(0, n/2),  //  left  half of bPadded
                     b0 = bPadded.substr(n/2),     //  right half of bPadded
                     c0 = karatsuba(a0, b0),
                //   c1 = (a1 + a0)(b1 + b0),      (is only referenced once)
                     c2 = karatsuba(a1, b1);
        
        //  a * b = (c2 * B^n) + ((c1 - c2 - c0) * B^(n / 2)) + c0.
        return add(
                    add(
                        c2 + string(n, '0'),
                        subtract(
                            subtract(
                                karatsuba(
                                    add(a1, a0),
                                    add(b1, b0)
                                ),
                                c2
                            ),
                            c0
                        ) + string(n/2, '0')
                    ),
                    c0
               );
    }
}


//  The main program, which runs the Karatsuba Algorithm based on inputs from the
//  console, and prints out its result of the mulitplication back to the console.
int main(const int argc, const char *argv[]) {
    if(argc != 3) {
        cerr << "Usage:\n" << argv[0] << " [INPUT1] [INPUT2]\n\nwhich calculates the product of the non-negative integers [INPUT1] and [INPUT2]." << endl;
        return 1;
    }
    //  error checking is very slow
    // else if(!regex_match(argv[1], regex("^[0-9]+$"))) {
    //     cerr << "\"" << argv[1] << "\" must only contain digits 0-9." << endl;
    //     return 1;
    // }
    // else if(!regex_match(argv[2], regex("^[0-9]+$"))) {
    //     cerr << "\"" << argv[2] << "\" must only contain digits 0-9." << endl;
    //     return 1;
    // }
    else {
        const string input1 = argv[1],
                     input2 = argv[2];
            
        auto start = high_resolution_clock::now();
        const string karatsuba_result = karatsuba(input1, input2);
        auto stop = high_resolution_clock::now();
        const auto karatsuba_time = duration_cast<microseconds>(stop - start).count();

        start = high_resolution_clock::now();
        multiply_naive(input1, input2);
        stop = high_resolution_clock::now();
        const auto naive_time = duration_cast<microseconds>(stop - start).count();
        
        const int displayWidth = max(numToString(karatsuba_time).length(), numToString(naive_time).length());
            
        cout << input1 + " * " + input2 + " =\n" + karatsuba_result
             << "\n\nKaratsuba computation time: " << setw(displayWidth) << karatsuba_time << " microsecond" << ((karatsuba_time != 1) ? "s" : "")
             << ".\nNaive     computation time: " << setw(displayWidth) << naive_time << " microsecond" << ((naive_time != 1) ? "s" : "") << "." << endl;
        
        return 0;
    }
}
