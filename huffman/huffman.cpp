#include "huffman.hpp"
#include "myutil.h"

#include <iostream>
#include <fstream>

using std::cerr;
using std::endl;
using std::string;
using std::vector;

vector< HuffmanTree<long>* > read_array(string const &path, bool description) {
	// create a vector for numbers, empty for now
	vector< HuffmanTree<long>* > nodes;

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
				nodes.emplace_back(new HuffmanTree<long> (v, std::to_string(v)));
			}
			catch (WrongIntInput e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

	return nodes;
}

