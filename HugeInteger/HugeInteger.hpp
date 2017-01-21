//
//  HugeInteger.hpp
//  Algorithms
//
//  Created by  Slava Senchenko on 2016-10-28.
//  Copyright © 2016  Slava Senchenko. All rights reserved.
//
//  this code was developed as a part of the assignment of
//  Stanford Algorithm Specialization
//  https://www.coursera.org/specializations/algorithms
//
//  course 1: Divide and Conquer, Sorting and Searching, and Randomized Algorithms
//  week 1 assignment: implement an algorithm that
//  multiplies two 64-digit integers
//
//  HugeInteger class represents integers that are too big to be
//  that are too big to be represented by unsigned long long
//  therefore the input and output of those integers uses strings
//
//  for the purpose of the course only three methods are implemented:
//  addition, subtraction and multiplication
//


#ifndef HUGEINT_HUGEINTEGER_H
#define HUGEINT_HUGEINTEGER_H

#include <string>
#include <ostream>

// decemal digits
int const icDigits = 10;

// a type to express sign of the
typedef enum {
    minus = -1,
    plus = 0
} sign_t;


class HugeInteger {
    std::string m_sInteger;
    sign_t m_eSign;

protected:

    // the function implements Karatsuba algorithm to recursively multiply 2 HugeIntegers
    // multiplication is done for absolute values
    friend HugeInteger multiplyAbsKaratsuba(HugeInteger const &left, HugeInteger const &right);

    //swaps the ownership of the internal
    void swap (HugeInteger& anotherInt);

public:
    //default constructor initialize integer to 0
    HugeInteger();

    HugeInteger(std::string const sInteger);

    //copy constructor
    HugeInteger(HugeInteger const &anotherInteger);

    std::string get() const;
    void set(std::string const sInteger);

    // the method returns
    // 1 if left > right
    // -1 if left < right
    // 0 if left == right
    int compare(HugeInteger const &Other) const;

    // this method implements brutal force algorithm to multiply 2 HugeIntegers
    // it may be used to check the correctness of the Karatsuba multiplication
    HugeInteger multiplySimple(HugeInteger const &Other);

    HugeInteger& operator= (HugeInteger const & anotherInteger);

    friend HugeInteger operator- (HugeInteger const &hInt);

    friend HugeInteger operator+ (HugeInteger const &left, HugeInteger const &right);
    friend HugeInteger operator- (HugeInteger const &left, HugeInteger const &right);
    friend HugeInteger operator* (HugeInteger const &left, HugeInteger const &right);

    friend HugeInteger& operator+= (HugeInteger &left, HugeInteger const &right);
    friend HugeInteger& operator-= (HugeInteger &left, HugeInteger const &right);
    friend HugeInteger& operator*= (HugeInteger &left, HugeInteger const &right);

    friend std::ostream& operator<< (std::ostream& os, const HugeInteger & hi);

    friend bool operator> (HugeInteger const &left, HugeInteger const &right);
    friend bool operator< (HugeInteger const &left, HugeInteger const &right);
    friend bool operator== (HugeInteger const &left, HugeInteger const &right);
    friend bool operator<= (HugeInteger const &left, HugeInteger const &right);
    friend bool operator>= (HugeInteger const &left, HugeInteger const &right);
};


#endif //HUGEINT_HUGEINTEGER_H
