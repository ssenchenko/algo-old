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
void c1w4_carager_mincut();
size_t const ulcSize4 = 200; // size of the graph from the assignments 4 and 6
// strong connecting components
void c2w1_ssc();
// Dijkstra shortest path
void c2w2_dijkstra_sp();
// Prim's minimum spanning tree algorithm
void c3w1_prim_mst();
// Kruskal's minimum spanning tree algorithm
void c3w2_kruskal_mst();
// Kruskal's clustering algorithm
void c3w2_kruskal_clustering();
// Bellman-Ford single source shortest path and
// test for negative cycles
void c4w1_bellman_ford_sp();
// Floyd-Warshall for all-pairs shortest paths
// and tests for negative cycle
void c4w1_floyd_warshall_sp();




#endif /* tests_h */
