//
//  HugeInteger.cpp
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
//  for the purpose of study only three methods are implemented:
//  addition, subtraction and multiplication
//

#include "HugeInteger.hpp"

using std::string;
using std::to_string;

inline int getIntDigit(string::const_reverse_iterator it) {
    // simple use of iterator does not work,
    // because &*li treats the rest of the string as one integer
    // the same problem with at() method
    // substr or copy should work there but with the same effect -- creating new object
    string sDigit(it, it + 1);
    return std::stoi(sDigit);
}


inline void storeDigitSum(int iDigitSum, string& sSum, int& iCarry) {
    iCarry = iDigitSum / icDigits;
    if (iCarry) {
        //iDigitSum = iDigitSum - (icDigits & -(iDigitSum >= icDigits)); // quick modulo devision d %= D
        iDigitSum %= icDigits;
    }

    //store a new digit of the sum in a string, always the most left digit
    sSum.insert(0, to_string(iDigitSum));
}

//default constructor initialize integer to 0
HugeInteger::HugeInteger() : m_sInteger("0"), m_eSign(plus){}

HugeInteger::HugeInteger(std::string const sInteger) {
    set(sInteger);
}


//copy constructor
HugeInteger::HugeInteger(HugeInteger const &anotherInteger) {
    m_sInteger = anotherInteger.m_sInteger;
    m_eSign = anotherInteger.m_eSign;
}


string HugeInteger::get() const{

    string sHugeInteger("");

    if (m_eSign == minus)
        sHugeInteger.append("-");
    sHugeInteger.append(m_sInteger);

    return sHugeInteger;
}


void HugeInteger::set(string const sInteger) {
    if (sInteger.at(0) == '-') {
        m_eSign = minus;
        m_sInteger = sInteger.substr(1);

    }
    else {
        m_eSign = plus;
        m_sInteger = sInteger;
    }

    // supress leading zeros if they are
    // first check if not ALL digits are zero
    if (m_sInteger.find_first_not_of("0") != m_sInteger.npos) {
        string::const_iterator it = m_sInteger.cbegin() + m_sInteger.find_first_not_of("0");
        m_sInteger.erase(m_sInteger.cbegin(), it);
    }
    else {
        m_sInteger = "0";
        if (m_eSign == minus)
            m_eSign = plus;
    }

}


HugeInteger operator+ (HugeInteger const &left, HugeInteger const &right) {

    if (left.m_eSign == plus && right.m_eSign == minus)  return left - (-right);
    if (left.m_eSign == minus && right.m_eSign == plus)  return right - (-left);
    if (left.m_eSign == minus && right.m_eSign == minus)  return -(-left + (-right));

    // reverse iterators as we add numbers starting from the rightest digit
    string::const_reverse_iterator li = left.m_sInteger.crbegin();
    string::const_reverse_iterator ri = right.m_sInteger.crbegin();

    // third grade math
    int iLDigit = 0, iRDigit =0, iDigitSum = 0;
    int iCarry = 0;

    string sSum(""); // sum represented as a string

    while (li != left.m_sInteger.crend() && ri != right.m_sInteger.crend()) {

        iLDigit = getIntDigit(li);
        iRDigit = getIntDigit(ri);

        iDigitSum = iLDigit + iRDigit + iCarry;
        storeDigitSum(iDigitSum, sSum, iCarry);

        li++; ri++;
    }

    // if still there are digits in the left number
    while (li != left.m_sInteger.crend()) {

        iLDigit = getIntDigit(li);

        iDigitSum = iLDigit + iCarry;
        storeDigitSum(iDigitSum, sSum, iCarry);

        li++;
    }

    // if still there are digits in the right number
    while (ri != right.m_sInteger.crend()) {

        iRDigit = getIntDigit(ri);

        iDigitSum = iRDigit + iCarry;
        storeDigitSum(iDigitSum, sSum, iCarry);

        ri++;
    }

    // if there is 1 to carry forward
    if (iCarry) {
        sSum.insert(0, to_string(iCarry));
    }

    return HugeInteger(sSum);
}


HugeInteger operator- (HugeInteger const &left, HugeInteger const &right) {

    if (left.m_eSign == plus && right.m_eSign == minus)  return left + (-right);
    if (left.m_eSign == minus && right.m_eSign == plus)  return -(-left + right);
    if (left.m_eSign == minus && right.m_eSign == minus)  return -right - (-left);
    if (left < right) return -(right - left);
    if (left == right) return HugeInteger();

    // reverse iterators as we add numbers starting from the rightest digit
    string::const_reverse_iterator li = left.m_sInteger.crbegin();
    string::const_reverse_iterator ri = right.m_sInteger.crbegin();

    // third grade math
    int iLDigit = 0, iRDigit = 0, iDigitDiff = 0;
    int iCarry = 0;
    sign_t eSign = plus;

    string sDiff(""); // difference represented as a string

    while (li != left.m_sInteger.crend() && ri != right.m_sInteger.crend()) {

        iLDigit = getIntDigit(li);
        iRDigit = getIntDigit(ri);

        if (iLDigit >= iRDigit + iCarry) {
            iDigitDiff = iLDigit - iRDigit - iCarry;
            iCarry = 0;
        }
        else if (li + 1 != left.m_sInteger.crend()) {
            // it will be ' + 10' for  any system (ie decemal, binary etc)
            iDigitDiff = iLDigit + 10 - iRDigit - iCarry;
            iCarry = 1;
        }
        else {
            iDigitDiff =  iRDigit + iCarry - iLDigit;
            iCarry = 0;
            eSign = minus;
        }

        //store a new digit of the sum in a string, always the most left digit
        sDiff.insert(0, to_string(iDigitDiff));

        li++; ri++;
    }

    while (li != left.m_sInteger.crend()) {

        iLDigit = getIntDigit(li);

        if (iLDigit >= iCarry) {
            iDigitDiff = iLDigit - iCarry;
            iCarry = 0;
        }
        else {
            iDigitDiff = iLDigit + 10 - iCarry;
            iCarry = 1;
        }


        sDiff.insert(0, to_string(iDigitDiff));

        li++;
    }

    if (eSign)
        sDiff.insert(0, "-");


    return HugeInteger(sDiff);
}


HugeInteger multiplyAbsKaratsuba(HugeInteger const &left, HugeInteger const &right) {
    auto lLength = left.m_sInteger.length();
    auto rLength = right.m_sInteger.length();

    // basic cases
    if (lLength == 1 || rLength == 1 ) {
        int iLDigit = stoi(left.m_sInteger);
        int iRDigit = stoi(right.m_sInteger);

        return HugeInteger(to_string(iLDigit * iRDigit));
    }

    // 1. devide integers by a, b, c, d
    auto maxLength = rLength ^ ((lLength ^ rLength) & - (lLength >= rLength));
    // if the numbers have different length, complement the shorter one to the maximum length
    string sLeft(""), sRight("");
    if (lLength < maxLength) {
        sLeft = string(maxLength - lLength, '0') + left.m_sInteger;
        sRight = right.m_sInteger;
    }
    else if (rLength < maxLength) {
        sLeft = left.m_sInteger;
        sRight = string(maxLength - rLength, '0') + right.m_sInteger;
    }
    else {
        sLeft = left.m_sInteger;
        sRight = right.m_sInteger;
    }
    auto newLength = maxLength / 2;
    HugeInteger A(sLeft.substr(0, newLength)), B(sLeft.substr(newLength));
    HugeInteger C(sRight.substr(0, newLength)), D(sRight.substr(newLength));

    //2. compute ac, bd, (a + b)(c + d), (ab + cd)
    HugeInteger AC = multiplyAbsKaratsuba(A,C); // ac
    HugeInteger BD = multiplyAbsKaratsuba(B,D); // bd
    HugeInteger ABCD = multiplyAbsKaratsuba(A + B, C + D); // (a + b)(c + d)
    ABCD = ABCD - AC - BD; // ab + cd

    //3. gather the product 10^n * AC + 10^(n/2) * (AB + CD) + BD, where n is number of digits
    string n(2 * (maxLength - newLength), '0'), halfn(maxLength - newLength, '0');
    AC.m_sInteger.append(n);
    ABCD.m_sInteger.append(halfn);
    HugeInteger Product = AC + ABCD + BD;

    return Product;
}


HugeInteger operator* (HugeInteger const &left, HugeInteger const &right) {

    HugeInteger hInt = multiplyAbsKaratsuba(left, right);
    hInt.m_eSign = static_cast<sign_t>(left.m_eSign ^ right.m_eSign);

    return hInt;
}


std::ostream& operator<< (std::ostream& os, const HugeInteger & hi) {
    os << hi.get();
    return os;
}


HugeInteger operator- (HugeInteger const &hInt) {

    HugeInteger hIntCopy(hInt);
    hIntCopy.m_eSign = static_cast<sign_t>(~hInt.m_eSign);

    return hIntCopy;
}


int HugeInteger::compare(HugeInteger const &Other) const {

    // method compare returns
    // 1 if *this > other
    // -1 if *this < other
    // 0 if *this == other

    if (m_eSign == plus && Other.m_eSign == minus) return 1;
    if (m_eSign == minus && Other.m_eSign == plus) return -1;

    // so we have both integers of the same sign
    int result = 0;
    // compare their length
    // but BEFORE that supress any possible leading zeros
    if (m_sInteger.length() > Other.m_sInteger.length())
        result = 1;
    else if (m_sInteger.length() < Other.m_sInteger.length())
        result = -1;
    else // so we have integers with the same number of digits
        result = m_sInteger.compare(Other.m_sInteger);

    // string::compare can return number that are bigger than one
    if (result > 1 || result < -1)
        result /= abs(result);

    // if both digits are not equal and are negative - invert the result
    if (result & (m_eSign & Other.m_eSign)) result = -result;

    return result;
}


bool operator> (HugeInteger const &left, HugeInteger const &right) {
    if (left.compare(right) == 1) return true;
    else return false;
}


bool operator< (HugeInteger const &left, HugeInteger const &right) {
    if (left.compare(right) == -1) return true;
    else return false;
}

bool operator== (HugeInteger const &left, HugeInteger const &right) {
    if (left.compare(right) == 0) return true;
    else return false;
}


bool operator>= (HugeInteger const &left, HugeInteger const &right) {
    if (left.compare(right) != -1) return true;
    else return false;
}


bool operator<= (HugeInteger const &left, HugeInteger const &right) {
    if (left.compare(right) != 1) return true;
    else return false;
}

HugeInteger HugeInteger::multiplySimple(HugeInteger const &Other) {
    string::const_reverse_iterator lIt;
    string::const_reverse_iterator rIt;
    int iLDigit = 0, iRDigit =0, iDigitSum = 0;
    int iCarry = 0, power = 0;

    string sSum("");

    HugeInteger Product("0");

    for (lIt = m_sInteger.crbegin(); lIt != m_sInteger.crend(); lIt++) {
        iLDigit = getIntDigit(lIt);
        for (rIt = Other.m_sInteger.crbegin(); rIt != Other.m_sInteger.crend(); rIt++) {
            iRDigit = getIntDigit(rIt);

            iDigitSum = iLDigit * iRDigit + iCarry;
            storeDigitSum(iDigitSum, sSum, iCarry);
        }

        // if there is 1 to carry forward
        if (iCarry) {
            sSum.insert(0, to_string(iCarry));
        }

        // add zeros to the right
        if (power)
            sSum.append(power, '0');

        Product += HugeInteger(sSum);
        sSum.clear();
        iCarry = 0;
        power++;
    }

    Product.m_eSign = static_cast<sign_t>(m_eSign ^ Other.m_eSign);

    return Product;
}


HugeInteger& HugeInteger::operator= (HugeInteger const & anotherInteger) {
    if (this == &anotherInteger) return *this;

    HugeInteger Temp(anotherInteger);
    swap(Temp);
    return *this;
}


HugeInteger& operator+= (HugeInteger &left, HugeInteger const &right) {

    left = left + right;
    return left;
}


HugeInteger& operator-= (HugeInteger &left, HugeInteger const &right) {

    left = left - right;
    return left;
}


HugeInteger& operator*= (HugeInteger &left, HugeInteger const &right){

    left = left * right;
    return left;
}

void HugeInteger::swap (HugeInteger& anotherInt) {
    string sTempInt = m_sInteger;
    sign_t eTempSign = m_eSign;

    m_sInteger = anotherInt.m_sInteger;
    m_eSign = anotherInt.m_eSign;

    anotherInt.m_sInteger = sTempInt;
    anotherInt.m_eSign = eTempSign;
}
