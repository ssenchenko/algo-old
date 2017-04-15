#include "myutil.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    // get the input from file
    std::ifstream file;
	// full path to Data folder with all data files
	std::string const scPath("/Users/slava_senchenko/Documents/Education/Stanford/Algorithms/test_data/");
	std::string const scFile8("c2w4_2sum.txt"); //file for the 8th assignment
    std::string const scFile8_test = "c2w4_2sum_copy.txt"; // smaller version to debug
    file.open(scPath + scFile8);
    if (file.fail()) {
        std::cerr << "Wrong file name!" << endl;
        file.clear();
    }
    else {
        std::unordered_map<long, long> map; // map for quick lookup
        map.max_load_factor(0.05); // makes search almost 2 times quicker (15.5s against 27-28s) making it higher or lower increases the processing time
        std::string s;
        long num;
        start = std::chrono::system_clock::now();
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
                num = getLong(s);
                map.insert(std::make_pair(num, num));
            }
            catch (std::domain_error e) {
                std::cerr << e.what() << std::endl;
            }
        }
		file.close();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        double input_time = elapsed_seconds.count();
        cout << "Input finished in " << input_time << "s" << endl;

        long x, y;
        int counter = 0;
        int const check = 1000, tmin = -10000, tmax = 10000;
        std::unordered_map<long, long>::iterator search, it_end = map.end();
        for (int t = tmin; t <= tmax; t++) {
            for (auto it = map.begin(); it != it_end; it++) {
                x = it->second;
                if (t != x * 2) {
                    y = t - x;
                    search = map.find(y);
                    if (search != map.end()) {
                        counter++;
                        break;
                    }
                }
            }
            
            if (t % check == 0 && t != tmin) {
                end = std::chrono::system_clock::now();
                elapsed_seconds = end - start;
                cout << "Next " << check << " t values checked, t = " << t;
                cout << ". Time spent " << elapsed_seconds.count() - input_time << endl;
            }
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        
        cout << "Average load " << map.load_factor() << ", max load " << map.max_load_factor() << endl;
        
        cout << "Time spent " << elapsed_seconds.count() << endl;
        cout << counter << endl;
    }

	return 0;
}
