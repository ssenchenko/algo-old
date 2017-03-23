#include <iostream>
#include <ios>
#include <iomanip>

#include "tspnn.hpp"

int main (int argsc, char* argv[]) {
	// path to the file with data
	std::string const path = "/Users/slava_senchenko/Documents/Education/Stanford/Algorithms/test_data/c4w3_tspnn.txt";

	// create a new vector for cities, you'll resize it later
	Cities *cities = new Cities();

	// read the file, resize the vector and write a city's coordinates to a vector
	bool read = read_task(path, *cities);

	// calculate travelling salesman distance
	if (read) {
		distance d = tspnn(*cities);

		std::cout << std::fixed << std::setprecision(0) << d << std::endl;
	}
	
	delete cities;

	return 0;
}