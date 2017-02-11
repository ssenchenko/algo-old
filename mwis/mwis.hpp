#ifndef MWIS_HPP
#define MWIS_HPP

#include <string>
#include <vector>

// path to the folder with data
std::string const scPath = "/Users/slava_senchenko/Documents/Education/Stanford/Algorithms/test_data/";
// data file name
std::string const scFileName = "c3w3_mwis.txt";

// reads txt file with list of numbers of long type
// if description = true, the first row contains the number of rows in file
std::vector<long> read_array(std::string const &path, bool description);

// calculates the weights of maximum weight independent subset
// input: array of weights for vertices from 1 to n (in that very order)
// in the form {0, 4, 4, 7 ... 189} with the size that number of vertices
// output: array of weights for maximum weight independent verticecs
// the LAST element is going to be the sum of MWIS
std::vector<long> calculate_mwis(std::vector<long> const &path_graph);

// reconstructs the labels (numbers) of vertices which were included to MWIS
// input: array of weights for maximum weight independent vertices
// in the form {0, 4, 4, 7 ... 189} with the size that number of vertices
// output: array of vertex labels (numbers/positions) from the path graph
std::vector<int> reconstruct(std::vector<long> const &mwis, std::vector<long> const &path_graph);

// maximum of two long numbers
inline long max(long const &lhs, long const &rhs);

#endif // MWIS_HPP