#include <iostream>
#include "HugeInteger.hpp"
#include "myutil.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

//  course 1:
//  Divide and Conquer, Sorting and Searching, and Randomized Algorithms

//  week 1
//  assignment: implement an algorithm that
//  multiplies these 2 64-digit integers
string const csMultiplierA("3141592653589793238462643383279502884197169399375105820974944592");
string const csMultiplierB("2718281828459045235360287471352662497757247093699959574966967627");

int main() {

    //  ask user to input 2 integers or to choose the numbers from the assignment

    int iInputType = 0;
    string sMultiplierA(""), sMultiplierB("");
    int iMultiplierA(0), iMultiplierB(0);

    while (!iInputType) {
        cout << "Choose one of 2 options:" << endl <<
             "1 - Input 2 small integers to check the correctness (press \'1\')" << endl <<
             "2 - Choose 2 integers from the assignment (press \'2\')" << endl;

        iInputType = getInteger();

        if (iInputType == 1) {
            cout << "First integer:" << endl;
            iMultiplierA = getInteger();
            sMultiplierA = std::to_string(iMultiplierA);

            cout << "Second integer:" << endl;
            iMultiplierB = getInteger();
            sMultiplierB = std::to_string(iMultiplierB);
        }
        else if (iInputType == 2) {
            sMultiplierA = csMultiplierA;

            sMultiplierB = csMultiplierB;
        }
        else {
            cerr << "Not a valid option. Please try again" << endl;
            iInputType = 0;
        }

    }
    //  create 2 HugeIntegers, multiply them
    HugeInteger MultiplierA(sMultiplierA);
    HugeInteger MultiplierB(sMultiplierB);
    HugeInteger Product = MultiplierA * MultiplierB;

    //  if the input was represented with int - check the product
    if (iInputType == 1) {
        // do also addition and subtraction
        HugeInteger Sum = MultiplierA + MultiplierB;
        HugeInteger Diff = MultiplierA - MultiplierB;

        int iProduct = iMultiplierA * iMultiplierB;
        int iDiff = iMultiplierA - iMultiplierB;
        int iSum = iMultiplierA + iMultiplierB;

        cout << "Simple integer multiplication result: " << iProduct << endl <<
             "Simple integer subtraction result: " << iDiff << endl <<
             "Simple integer addition result: " << iSum << endl;
    }
    else if (iInputType == 2) {
        HugeInteger SimpleProduct = MultiplierA.multiplySimple(MultiplierB);
        //  output the product
        cout << (Product == SimpleProduct ? "It works! :)" : "Still isn't working :(") << endl << endl <<
             "HugeInteger Karatsuba multiplication result: " << Product << endl << endl <<
             "HugeInteger 3rd grade algorithm result: " << SimpleProduct << endl << endl;
    }

    return 0;
}