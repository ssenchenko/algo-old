#include "myutil.h"
#include "intstream.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

using std::cerr;
using std::cout;
using std::endl;

// week 7
// assignment: median maintenance
// for a stream of integers (one integer in a time)
// calculate a median after each new integer added
// there are 10,000 integers
// stored in the file

int main(int argc, char* argv[]) {
	size_t const ulcSize3 = 10000; // use the same constant as in the assignment 3

	// full path to Data folder with all data files
	std::string const scPath("/Users/slava_senchenko/Documents/Education/Stanford/Algorithms/test_data/");

	std::string const scFile7("c2w3_Median.txt"); //file for the 7th assignment

	// ask user to input an array or to choose the file with the input
	// runs median maintenance after adding each number
	// sums of these 10000 medians, modulo 10000 (i.e., only the last 4 digits)
	// and prints that result
	// computes time spent

	std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    // get the input from file
    std::ifstream file;
    file.open(scPath + scFile7);
    if (file.fail()) {
        cerr << "Wrong file name!" << endl;
        file.clear();
    }
    else {
        start = std::chrono::system_clock::now();
        std::string s;
        int num;
        unsigned long sum = 0;
        int_stream sequence(heap, ulcSize3);
        while (true) {
            getline(file, s);
            if (file.eof()) {
                file.clear();
                break;
            }
            if (file.fail()) {
                std::cerr << scGetlineError << std::endl;
                file.clear();
                break;
            }
            try {
                num = getInteger(s);
                sum += sequence.median(num);
            }
            catch (std::domain_error e) {
                cerr << e.what() << std::endl;
            }
            catch (no_model e) {
                cerr << e.what() << std::endl;
                break;
            }
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        cout << "Time to process with heap model " << elapsed_seconds.count() << endl;
        cout << sum % 10000 << endl;
    }
	file.close();
	return 0;
}