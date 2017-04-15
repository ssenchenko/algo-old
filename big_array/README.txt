 This code was developed as a part of the assignment of
 Stanford Algorithm Specialization
 https://www.coursera.org/specializations/algorithms
 course 1: Divide and Conquer, Sorting and Searching, and Randomized Algorithms

 Week 2 assignment:
 to compute the number of inversions in the file given,
 where the i-th row of the file indicates the i-th entry of an array.
 The file contains all of the 100,000 integers between 1 and 100,000 (inclusive)
 in some order, with no integer repeated.
 file to test the class is located in ./Data
 and called c1w2_IntegerArray.txt

 Week 3 assignnment:
 To compute the total number of comparisons used to sort the given input file by QuickSort
 when there is a recursive call on a subarray of length m,
 total of comparisons should be increased by m−1
 computations should be done for three cases:
 1) the first element of array is used as a pivot
 2) the final element of array is used as s pivot
 3) the median of 3 (first, last and middle elements) is used
 file contains all of the integers between 1 and 10,000 (inclusive, with no repeats) in unsorted order.
 The integer in the i-th row of the file gives you the i-th entry of an input array.
 file to test the class is located in ./Data
 and called c1w3_QuickSort.txt

 To unite 2 tasks in one design, inheritence and polymorphys is used
 I picked that design instead of "Strategy" pattern because except for sorting
 both arrays performs different tasks (inversions and comparison computation).
 It means that each case is more than an abstract strategy since implementations
 have to include and provide a client with case-specific data

 BigIntArray class is the abstract class built around the vector<int>
 ArrayWithInversions is an inherited class with merge sort algorithm
 inversions computation
 ArrayWithComparisons is another inherited from BigIntArray class with quick sort algorithm
 and comparisons computation

 ArrayWithComparisons implements "Strategy" design pattern to choose
 the pivot in different ways.
 ChoosePivot is an abstract "Strategy" class
 FirstPivot is an implementation with the first element as a pivot
 LastPivot is an implementation with the last element as a pivot
 MedianPivot is an implementation with median of three (first, last and middle)
