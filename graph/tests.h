//
//  tests.h
//  Algorithms
//
//  Created by  Slava Senchenko on 2016-10-28.
//  Copyright © 2016  Slava Senchenko. All rights reserved.
//
//  this file contains constants and additional functions
//  to run tests on graph classes


#ifndef tests_h
#define tests_h

#include <iostream>

// message for user interaction part
std::string const scNVO("Not a valid option. Please try again");

// full path to Data folder with all data files
std::string const scPath("/Users/slava_senchenko/Documents/Education/Stanford/Algorithms/test_data/");

// graph algorithms
std::string const scFile4("c1w4_kargerMinCut.txt"); //file for the 4th assignment
std::string const scFile5("c2w1_StrongComponents.txt"); //file for the 5th assignment
std::string const scFile6("c2w2_dijkstraData.txt"); //file for the 6th assignment
std::string const scFile9("c3w1_edges.txt"); //file for prim's mst algorithm
// Carager min-cut
void runTest_c1w4 ();
size_t const ulcSize4 = 200; // size of the graph from the assignments 4 and 6
// strong components
void runTest_c2w1 ();
// Dijkstra shortest path
void runTest_c2w2 ();
// Prim's minimum spanning tree algorithm
void runTest_c3w1 ();





#endif /* tests_h */
