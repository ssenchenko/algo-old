#include "tests.hpp"
#include "BigIntArray.hpp"
#include "myutil.h"
#include <fstream>

using std::cout;
using std::endl;
using std::cerr;
using std::string;

//  run test for the week 2 assignment
void c1w2_inversions () {
    
    // our array class variable
    // pointer is used to call different constructors
    // depending on user choice
    BigIntArray* p_Array = nullptr;
    
    int iInputType = 0;
    int array[] = {3, 1, 5, 2, 7, 6, 4};
    int const icMaxElements = 7;
    
    // interactive input
    while (!iInputType) {
        cout << "Choose one of 2 options:" << endl <<
            "1 - Choose a small predefined array of integers to test the program (press \'1\')" << endl <<
            "2 - Choose an array from the assignment file (press \'2\')" << endl;
        
        iInputType = getInteger();
        
        if (iInputType == 1) {
            p_Array = new ArrayWithInversions(array, icMaxElements);
            cout << "Predefined array for the test. ";
            cout << *p_Array;
        }
        else if (iInputType == 2) {
            // get the input from file
            std::ifstream file;
            file.open(scPath + scFile2);
            if (file.fail()) {
                cerr << "Wrong file name!" << endl;
                file.clear();
            }
            else {
                p_Array = new ArrayWithInversions(ulcSize2);
                file >> *p_Array;
            }
			file.close();
        }
        else {
            cerr << scNVO << endl;
            iInputType = 0;
        }
        
    }
    
    if (p_Array) {
        
        p_Array->sort();
        
        if (ArrayWithInversions* pInversions = dynamic_cast<ArrayWithInversions*>(p_Array))
            cout << "Number of inversions: " << pInversions->inversions() << endl;
        
        if (iInputType == 1) {
            cout << "Sorted array. ";
            cout << *p_Array;
        }
        
        delete p_Array;
    }
}

//  run test for the week 3 assignment
void c1w3_quickSort () {
    
    // our array class variable
    // pointer is used to call different constructors
    // depending on user choice
    BigIntArray* p_Array = NULL;
    
    int iInputType = 0;
    int array[] = {3, 1, 5, 2, 6, 4};
    int const icMaxElements = 6;
    
    // interactive input
    while (!iInputType) {
        cout << "Choose one of 2 options:" << endl <<
        "1 - Choose a small predefined array of integers to test the program (press \'1\')" << endl <<
        "2 - Choose an array from the assignment file (press \'2\')" << endl;
        
        iInputType = getInteger();
        
        if (iInputType != 1 && iInputType != 2) {
            cerr << scNVO << endl;
            iInputType = 0;
        }
        
    }
    
    pivot_t pivot = none;
    while (!pivot) {
        cout << "Choose type of pivot: " << first << " - first, " <<
                last << " - last, " << median << " - median" << endl;
        int p = getInteger();
        if (p < first || p > median) {
            cerr << scNVO << endl;
            continue;
        }
        pivot = static_cast<pivot_t>(p);
    }
    
    if (iInputType == 1) {
        p_Array = new ArrayWithComparisons(array, icMaxElements, pivot);
        cout << "Predefined array for the test. ";
        cout << *p_Array;
    }
    else /*iInputType == 2*/ {
        // get the input from file
        std::ifstream file;
        file.open(scPath + scFile3);
        if (file.fail()) {
            cerr << "Wrong file name!" << endl;
            file.clear();
        }
        else {
            p_Array = new ArrayWithComparisons(ulcSize3, pivot);
            file >> *p_Array;
        }
		file.close();
    }
    
    if (p_Array) {
        
        p_Array->sort();
        
        if (ArrayWithComparisons* pComparisons = dynamic_cast<ArrayWithComparisons*>(p_Array))
            cout << "Number of comparisons: " << pComparisons->comparisons() << endl;
        
        if (iInputType == 1) {
            cout << "Sorted array. ";
            cout << *p_Array;
        }
        
        delete p_Array;
    }
}