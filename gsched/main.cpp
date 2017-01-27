#include <iostream>

#include "jobs_test.hpp"

using std::cout;
using std::endl;
using std::vector;

int main() {
	// read the file
	std::string file = scPath + scFileName;
	vector<jobs_t> jobs = read_input(file);

	// run summarise with differences as a key
	long sum = summarise(jobs, [](Job j) { return j.weight - j.time; } );
	// print it out
	cout << "With a difference: " << sum << endl;

	// run summarise with a ratio as a key
	sum = summarise(jobs, [](Job j) { return static_cast<float>(j.weight) / j.time; } );
	// print it out
	cout << "With a ratio: " << sum << endl;

	return EXIT_SUCCESS;
}