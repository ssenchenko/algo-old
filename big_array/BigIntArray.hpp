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

#ifndef BigIntArray_hpp
#define BigIntArray_hpp

#include <vector>
#include <iterator>
#include <iostream>

class BigIntArray {
private:
    bool bSorted_;

protected:
    std::vector<int> vArray_;
    
public:
    BigIntArray();
    virtual ~BigIntArray() {};
    
    // construct array of the specific capacity
    BigIntArray(size_t capacity);
    
    // constructs array from int array
    // takese array name and munber of elements in array
    BigIntArray(int* array, int n);
    
    virtual void sort() = 0;
    
    bool sorted() const;
    void sorted(bool sorted);
    
    friend std::istream& operator>> (std::istream &input, BigIntArray &anArray);
    friend std::ostream& operator<< (std::ostream &output, BigIntArray &anArray);
};


class ArrayWithInversions : public BigIntArray {
private:
    long int lInversions_; // number of invertions in the array
    
protected:
    void merge_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    void merge(std::vector<int>::iterator leftBegin, std::vector<int>::iterator leftEnd,
               std::vector<int>::iterator rightBegin, std::vector<int>::iterator rightEnd);
    
public:
    ArrayWithInversions();
    
    // construct array of the specific capacity
    ArrayWithInversions(size_t capacity);
    
    // constructs array from int array
    // takese array name and munber of elements in array
    ArrayWithInversions(int* array, int n);
    
    long int inversions() const;
    
    virtual void sort();
};


// possible choises to select pivot
typedef enum {
    none = 0,
    first,
    last,
    median
} pivot_t;

class ChoosePivot {
public:
    virtual ~ChoosePivot() {};
    virtual std::vector<int>::iterator choose(std::vector<int>::iterator begin,
                                              std::vector<int>::iterator end) = 0;
};

class ArrayWithComparisons : public BigIntArray {
private:
    long int lComparisons_; // number of comparisons made during the quick sort
    ChoosePivot* pPivotStrategy_; // a strategy to choose pivot
    
protected:
    void quick_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    
public:
    ArrayWithComparisons();
    ~ArrayWithComparisons();
    
    // construct array of the specific capacity
    ArrayWithComparisons(size_t capacity, pivot_t ePivot);
    
    // constructs array from int array
    // takese array name and munber of elements in array
    ArrayWithComparisons(int* array, int n, pivot_t ePivot);
    
    void changePivot(pivot_t ePivot);
    
    long int comparisons() const;
    
    virtual void sort();
    
};

class FirstPivot : public ChoosePivot {
public:
    virtual std::vector<int>::iterator choose(std::vector<int>::iterator begin,
                                              std::vector<int>::iterator end);
};

class LastPivot : public ChoosePivot {
public:
    virtual std::vector<int>::iterator choose(std::vector<int>::iterator begin,
                                              std::vector<int>::iterator end);
};

class MiddlePivot : public ChoosePivot {
public:
    virtual std::vector<int>::iterator choose(std::vector<int>::iterator begin,
                                              std::vector<int>::iterator end);
};



void swap(int& left, int& right);

std::vector<int>::iterator middle(std::vector<int>::iterator a,
                               std::vector<int>::iterator b,
                               std::vector<int>::iterator c);


#endif /* BigIntArray_hpp */
