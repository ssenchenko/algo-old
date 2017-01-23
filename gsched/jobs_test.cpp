#include <fstream>
#include <iostream>

#include "jobs_test.hpp"
#include "myutil.h"

using std::vector;
using std::string;
using std::cerr;
using std::endl;

// function to read input file (provided with a task)
// key is 0 by default
vector<jobs_t> read_input(string const &path) {
	// create a vector for jobs, empty for now
	vector<jobs_t> jobs;

	// get the input from file
	std::ifstream file;
	file.open(path);
	if (file.fail()) {
		cerr << "Wrong file name!" << endl;
		file.clear();
	}
	else {
		string s;
		// read first line to get number of vertices and edges
		getline(file, s);
		if (file.fail()) {
			cerr << scGetlineError << endl;
			file.clear();
		}
		else if (file.eof()) {
			cerr << scUnexpectedEOF << endl;
			file.clear();
		}
		else {
			// read number of jobs
			vector<int> v = parse_string(s);
			// resize a vector for jobs
			jobs.reserve(v.front());

			// read other lines
			while (true) {
				getline(file, s);
				if (file.eof()) {
					file.clear();
					break;
				}
				if (file.fail()) {
					cerr << scGetlineError << endl;
					file.clear();
					break;
				}

				v = parse_string(s, " ");
				jobs.emplace_back(0.0, Job(v.at(0), v.at(1)));
				
			}
		}
	}

	return jobs;
}

int calculate_time (std::vector<jobs_t>::iterator begin, std::vector<jobs_t>::iterator curr) {
	if (curr == begin) 
		return curr->second.time;
	else
		return curr->second.time + calculate_time (begin, --curr);
}