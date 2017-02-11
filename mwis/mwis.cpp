#include "mwis.hpp"
#include "myutil.h"

#include <fstream>
#include <iostream>

using std::vector;
using std::string;
using std::endl;
using std::cerr;

vector<long> read_array(string const &path, bool description) {
	// create a vector for numbers, empty for now
	vector<long> nodes;

	// get the input from file
	std::ifstream file;
	file.open(path);
	if (file.fail()) {
		cerr << "Wrong file name!" << endl;
		file.clear();
	}
	else {
		string s;
		if (description) {
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
			try {
				// read number of jobs
				long size = getLong(s);
				// resize a vector for jobs
				nodes.reserve(size);
			}
			catch (WrongIntInput e) {
				std::cerr << e.what() << std::endl;
				return nodes;
			}
			
		}
		// read other lines
		long v;
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
			try {
				// read number of jobs
				v = getLong(s);
				// resize a vector for jobs
				nodes.emplace_back(v);
			}
			catch (WrongIntInput e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

	return nodes;
}

inline long max(long const &lhs, long const &rhs) {
	return lhs >= rhs ? lhs : rhs;
}

vector<long> calculate_mwis(vector<long> const &path_graph) {
	vector<long> mwis(path_graph.size() + 1, 0l);

	auto j = 1;
	auto end = path_graph.size() + 1;
	mwis.at(j) = path_graph.at(j - 1); ++j;
	for (; j != end; ++j) {
		mwis.at(j) = max(mwis.at(j - 1), mwis.at(j - 2) + path_graph.at(j - 1));
	}

	return mwis;
}

vector<int> reconstruct(vector<long> const &mwis, vector<long> const &path_graph) {
	vector<int> vertices(path_graph.size(), 0);

	size_t j = mwis.size() - 1;
	while(j > 1) {
		if (mwis.at(j - 1) >= mwis.at(j - 2) + path_graph.at(j - 1)) {
			--j;
		}
		else {
			vertices.at(j - 1) = 1;
			j -= 2;
		}
	}
	// last vertex
	if (vertices.at(j) == 0 && vertices.at(j - 1) == 0)
			vertices.at(j - 1) = 1;

	return vertices;
}