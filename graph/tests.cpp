//
//  tests.cpp
//  Algorithms
//
//  Created by  Slava Senchenko on 2016-10-28.
//  Copyright © 2016  Slava Senchenko. All rights reserved.
//
//  this file contains constants and additional functions
//  to run tests on following classes
//      - HugeInteger
//


#include "tests.h"
#include "myutil.h"
#include "graph.hpp"

#include <fstream>
#include <iomanip>
#include <array>
#include <unordered_map>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;

// strong components detection
void runTest_c2w1 () {

    std::chrono::time_point<std::chrono::system_clock> start, end;
    // get the input from file
    std::ifstream file;
    file.open(scPath + scFile5);
    if (file.fail()) {
        cerr << "Wrong file name!" << endl;
        file.clear();
    }
    else {
        string s;
        std::vector<int> v;
        // get last line
        int j = -2;
        file.seekg(j--, std::ios_base::end); // eof - 2
        while (true) {
            char ch;
            file.get(ch);
            if (ch == '\n')
                break;
            file.seekg(j--, std::ios_base::end);
        }
        getline(file, s);
        v = parse_string(s, " ");
        
        //v[0] - maximum vertex number
        VSet nodes(v.at(0));
        Graph G(nodes), Grev(nodes);
        // now parse file and form the graph
        start = std::chrono::system_clock::now();
        file.seekg(std::ios_base::beg);
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
            v = parse_string(s, " ");
            G.add_edge_di(v.at(0), v.at(1));
            Grev.add_edge_di(v.at(1), v.at(0));
        }
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        cout << "Loading " << elapsed_seconds.count() << "s" << endl;
//        cout << G << endl;
//        cout << Grev << endl;
        start = std::chrono::system_clock::now();
        Grev.compute_ft();
        G.compute_scc();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        cout << "SCC computed " << elapsed_seconds.count() << "s" << endl;
        cout << "Number of SCC " << G.scc() << endl;
        cout << "5 biggest SCC " << G.scc_numbers(5) << endl;
    }
}


// Dijkstra shortest path
void runTest_c2w2 () {
    std::array<vertex_label, 10> answers = {7,37,59,82,99,115,133,165,188,197};
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    // get the input from file
    std::ifstream file;
    string const scFile6_test = "dijkstraData.txt";
    file.open(scPath + scFile6);
    if (file.fail()) {
        cerr << "Wrong file name!" << endl;
        file.clear();
    }
    else {
        start = std::chrono::system_clock::now();
        
        string s;
        std::vector<string> tuples;
        VSet nodes(ulcSize4);
//        VSet nodes(4);
        Graph G(nodes);
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
            tuples = preparse_string(s);
            try {
                vertex_label from = getInteger(tuples.front());
                
                for (auto it = tuples.begin() + 1, it_end = tuples.end(); it != it_end; it++) {
                    std::vector<int> v = parse_string(*it, ",");
                    G.add_edge_di(from, v.at(0), v.at(1));
                }
            }
            catch (std::domain_error e) {
                std::cerr << e.what() << std::endl;
            }
        }
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        cout << "Loading " << elapsed_seconds.count() << "s" << endl;
        
//        cout << G << endl;
        
        start = std::chrono::system_clock::now();
        
        std::vector<weight_t> path = G.shortest_path(1);
        
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        
        cout << "Shortest path computed " << elapsed_seconds.count() << "s" << endl;
//        for (auto &&n : *nodes.vertices_ptr()) {
//            cout << n->label() << " | " << path[n->label() - 1] << endl;
//        }
        string out;
        for (auto &&i : answers) {
            out += std::to_string(path[i - 1]) + ",";
        }
        out.pop_back();
        cout << out << endl;
    }
}

void runTest_c3w1 () {

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
	// get the input from file
	std::ifstream file;
	file.open(scPath + scFile9);
	if (file.fail()) {
		cerr << "Wrong file name!" << endl;
		file.clear();
	}
	else {
		start = std::chrono::system_clock::now();

		string s;
		std::vector<string> tuples;
		// read first line to get number of vertices and edges
		getline(file, s);
		if (file.fail()) {
			std::cerr << scGetlineError << std::endl;
			file.clear();
		}
		else if (file.eof()) {
			std::cerr << scUnexpectedEOF << std::endl;
			file.clear();
		}
		else {
			size_t v_num;
			std::vector<int> v = parse_string(s, " ");
			v_num = v.front();
			VSet nodes(v_num);
//			VSet nodes(4);
			Graph G(nodes);
			// read other lines
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

				v = parse_string(s, " ");
				G.add_edge(v.at(0), v.at(1), v.at(2));

			}

			end = std::chrono::system_clock::now();
			elapsed_seconds = end - start;
			cout << "Loading " << elapsed_seconds.count() << "s" << endl;

        	// cout << G << endl;

			start = std::chrono::system_clock::now();

			std::vector<weight_t> tree = G.mst_prim(1);

			end = std::chrono::system_clock::now();
			elapsed_seconds = end - start;

			cout << "MST prim computed " << elapsed_seconds.count() << "s" << endl;
//			for (auto &&n : *nodes.vertices_ptr()) {
//				cout << n->label() << " | " << path[n->label() - 1] << endl;
//			}
			int sum = 0, counter = 0;
			for (auto &&leaf : tree) {
				// cout << std::setw(3) << ++counter << ": " << std::setw(7) << leaf << endl;
				sum += leaf;
			}

			cout << sum << endl;
		}
	}
}

/*void runTest_c1w4 () {
    AdjacencyList graph;

    // get the input from file
    std::ifstream file;
    file.open(scPath + scFile4);
    if (file.fail()) {
        cerr << "Wrong file name!" << endl;
        file.clear();
    }
    else {
        file >> graph;
        cout << "Vertices = " << graph.verticesNum() <<
            " Edges = " << graph.edgesNum() << endl;

        if (DEBUG)
            cout << graph;

        size_t c, mc = graph.edgesNum(), i = 0;
        unsigned int counter = 0;
        // Seed with a real random value, if available
        std::random_device rd;
        // initialize (start) th engine
        std::mt19937_64 engine(rd());
        for (; i < 100 *//*graph.verticesNum() * graph.verticesNum() * log(graph.verticesNum())*//*; i++) {
            auto gcopy = graph;
            c = gcopy.minCut(&engine);
            if (c == mc) counter++;
            else if (c < mc) {
                mc = c;
                counter = 1;
            }
            //graph.reset();
        }
        cout << endl << "Minimum cut: " << mc << endl;
        cout << "Probability: " << counter << " / " << i << " = ";
        cout << std::setprecision(2) << std::fixed;
        cout << static_cast<double>(counter) / static_cast<double>(i) << endl << endl;
    }

}*/