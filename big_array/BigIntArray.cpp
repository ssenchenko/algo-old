//
//  BigIntArray.hpp
//  Algorithms
//
//  Created by  Slava Senchenko on 2016-10-31.
//  Copyright © 2016  Slava Senchenko. All rights reserved.
//
//  this code was developed as a part of the assignment of
//  Stanford Algorithm Specialization
//  https://www.coursera.org/specializations/algorithms

#include "BigIntArray.hpp"
#include "myutil.h"

BigIntArray::BigIntArray() {
    bSorted_ = false;
}

BigIntArray::BigIntArray(int* array, int n) : vArray_(array, array + n) {
    bSorted_ = false;
}

BigIntArray::BigIntArray(size_t capacity) {
    vArray_.reserve(capacity);
    bSorted_ = false;
}

bool BigIntArray::sorted() const {
    return bSorted_;
}

void BigIntArray::sorted(bool sorted) {
    bSorted_ = sorted;
}

std::istream& operator>> (std::istream &input, BigIntArray &anArray) {
    
    std::string s;
    int aNumber;
    
    while (true) {
        getline(input, s);
        if (input.eof()) {
            input.clear();
            break;
        }
        if (input.fail()) {
            std::cerr << scGetlineError << std::endl;
            input.clear();
            break;
        }
        try {
            aNumber = getInteger(s);
            anArray.vArray_.push_back(aNumber);
        }
        catch (std::domain_error e) {
            std::cerr << e.what() << std::endl;
        }
    }
    
    return input;
}


std::ostream& operator<< (std::ostream &output, BigIntArray &anArray) {
    output << "Array content:" << std::endl;
    for (const int& e : anArray.vArray_) {
        output << e << " ";
        
    }
    output << std::endl;
    return output;
}



// construct array of the specific capacity
ArrayWithInversions::ArrayWithInversions(size_t capacity) : BigIntArray(capacity) {
    lInversions_ = 0;
}


// constructs BigIntArray from int array
// takese array name and munber of elements in arra
ArrayWithInversions::ArrayWithInversions(int* array, int n) : BigIntArray(array, n) {
    lInversions_ = 0;
}

long int ArrayWithInversions::inversions() const {
    return lInversions_;
}

void ArrayWithInversions::sort() {
    if (!sorted()) {
        merge_sort(vArray_.begin(), vArray_.end() );
        sorted(true);
    }
}

void ArrayWithInversions::merge_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    
    if (begin == end - 1) return;
    
    // calculate a middle point
    auto middle = (end - begin ) / 2;
    // and end of the left Array and beginning of the right Array
    auto leftEnd = begin + middle ;
    auto rightBegin = begin + middle;
    
    // recursive sort an merge
    merge_sort(begin, leftEnd);
    merge_sort(rightBegin, end);
    merge(begin, leftEnd, rightBegin, end);
}

void ArrayWithInversions::merge(std::vector<int>::iterator leftBegin, std::vector<int>::iterator leftEnd,
                        std::vector<int>::iterator rightBegin, std::vector<int>::iterator rightEnd) {
    
    // copy parts of the arrays before merging
    std::vector<int> leftCopy(leftBegin, leftEnd);
    std::vector<int> rightCopy(rightBegin, rightEnd);
    
    // intialize copy iterators
    std::vector<int>::iterator lIt = leftCopy.begin(), rIt = rightCopy.begin();
    // initialized sorted vector iterator
    std::vector<int>::iterator It = leftBegin;
    
    while (lIt < leftCopy.end() &&  rIt < rightCopy.end()) {
        if (*rIt <= *lIt) {
            *It = *rIt;
            // to calculate number of inversions
            // add the number of elements that left in the left part
            lInversions_ += leftCopy.end() - lIt;
            rIt++;
        }
        else {
            *It = *lIt;
            lIt++;
        }
        
        It++;
    }
    
    // add elements that left in the left part
    while (lIt < leftCopy.end()) {
        *It = *lIt;
        lIt++; It++;
    }
    
    // add elements that left in the right part
    while (rIt < rightCopy.end()) {
        *It = *rIt;
        rIt++; It++;
    }
}


ArrayWithComparisons::ArrayWithComparisons() :
    BigIntArray(), lComparisons_(0), pPivotStrategy_(nullptr) {}

ArrayWithComparisons::~ArrayWithComparisons() {
    if (pPivotStrategy_)
        delete pPivotStrategy_;
}

ArrayWithComparisons::ArrayWithComparisons(size_t capacity, pivot_t ePivot) :
    BigIntArray(capacity), lComparisons_(0), pPivotStrategy_(nullptr) {
    changePivot(ePivot);
}

ArrayWithComparisons::ArrayWithComparisons(int* array, int n, pivot_t ePivot) :
    BigIntArray(array, n), lComparisons_(0), pPivotStrategy_(nullptr) {
    changePivot(ePivot);
}

void ArrayWithComparisons::changePivot(pivot_t ePivot) {
    if (pPivotStrategy_)
        delete pPivotStrategy_;
    
    switch (ePivot) {
        case first:
            pPivotStrategy_ = new FirstPivot();
            break;
        case last:
            pPivotStrategy_ = new LastPivot();
            break;
        case median:
            pPivotStrategy_ = new MiddlePivot();
            break;
        default:
            break;
    }
}

long int ArrayWithComparisons::comparisons() const {
    return lComparisons_;
}

void ArrayWithComparisons::sort() {
    if (!sorted()) {
        if (!pPivotStrategy_) {
            std::cerr << "Before sorting, choose the method of pivot selection" << std::endl;
            return;
        }
        
        quick_sort(vArray_.begin(), vArray_.end());
        sorted(true);
    }
}

std::vector<int>::iterator FirstPivot::choose(std::vector<int>::iterator begin,
                                              std::vector<int>::iterator end) {
    return begin;
}

void ArrayWithComparisons::quick_sort(std::vector<int>::iterator begin,
                                      std::vector<int>::iterator end) {
    if (begin >= end - 1) return; // >= is important because in some cases begin == end
    
    // increase a number of comparisons
    lComparisons_ += end - begin - 1; // m - 1 comparisons
    
    // pick pivot
    std::vector<int>::iterator pPivot = pPivotStrategy_->choose(begin, end);
#ifdef DEBUG
    std::cout << *this;
#endif
    
    // set pointers
    std::vector<int>::iterator j = pPivot + 1; // part of the array that has not been checked
    std::vector<int>::iterator i = pPivot + 1; // part of the array that is bigger than pivot
    
    for (; j != end; j++) {
        if (*j < *pPivot) {
            swap(*i, *j);
            i++;
        }
    }
    // put pivot where it belongs
    swap(*pPivot, *(i - 1));
    
#ifdef DEBUG
    std::cout << *this;
    std::cout << *begin << "-" << *(i - 1) << " and " << *i << "-" << *end << std::endl;
#endif
    //iterative calls for the part which is less than pivot and bigger than pivot
    quick_sort(begin, i - 1);
    quick_sort(i, end);
}

std::vector<int>::iterator LastPivot::choose(std::vector<int>::iterator begin,
                                              std::vector<int>::iterator end) {
    swap(*begin, *(end - 1)); // imposed by the assignment that pivot always must be in the beginning
    return begin;
}

std::vector<int>::iterator MiddlePivot::choose(std::vector<int>::iterator begin,
                                             std::vector<int>::iterator end) {
    std::vector<int>::iterator me = begin + (end - begin) / 2;
    if ((end - begin) % 2 == 0) me--; // imposed by the assignment
    me = middle(begin, end - 1, me);
    swap(*begin, *me);
    return begin;
}


void swap(int& left, int& right) {
    
    int temp = left;
    left = right;
    right = temp;
}

std::vector<int>::iterator middle(std::vector<int>::iterator a,
                                  std::vector<int>::iterator b,
                                  std::vector<int>::iterator c) {
    if ((*a <= *b && *b <= *c) || (*c <= *b && *b <= *a)) return b;
    else if ((*b <= *a && *a <= *c) || (*c <= *a && *a <= *b)) return a;
    else return c;
}
