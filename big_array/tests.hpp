#ifndef TESTS_HPP
#define TESTS_HPP

#include <string>

// message for user interaction part
std::string const scNVO("Not a valid option. Please try again");

// full path to Data folder with all data files
std::string const scPath("/Users/slava_senchenko/Documents/Education/Stanford/Algorithms/test_data/");

// week 2
// assignment: calculate the number of inversions
// for the array of 100,000 distinct integres
size_t const ulcSize2 = 100000; // size of the array from the assignment 2

// that is stored in the file c1w2_IntegerArray.txt
std::string const scFile2("c1w2_IntegerArray.txt"); //file for the 2nd assignment

//  ask user to input array or to choose the file with the input
//  sorts array
//  output the result
//  prints the number of inversions
//  if array was input by user - prints array
void c1w2_inversions ();

// week 3
// assignment: implement quick sort
// choosing pivot as
// first, last and median or median (of first, last and middle) elements
// array is of size 10,000
size_t const ulcSize3 = 10000; // size of the array from the assignment 3

// stored in file c1w3_QuickSort.txt
std::string const scFile3("c1w3_QuickSort.txt"); //file for the 3rd assignment

//  ask user to input array or to choose the file with the input
//  sorts array
//  output the result
//  prints the number of comparison made
//  if array was input by user - prints array
void c1w3_quickSort ();

#endif // TESTS_HPP