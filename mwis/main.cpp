#include "mwis.hpp"
#include <iostream>
#include <array>

int main() {
	// read the file
	std::string file = scPath + scFileName;
	std::vector<long> path_graph = read_array(file, true);
	if (path_graph.empty()) {
		std::cerr << "Nothing has been loaded" << std::endl;
		return 1;
	}
	
	std::vector<long> mwis = calculate_mwis(path_graph);
	std::cout << "done 1" << std::endl;
	std::vector<int> vertices = reconstruct(mwis, path_graph);
	std::cout << "done 2" << std::endl;

	std::array<int, 8> vv { {1, 2, 3, 4, 17, 117, 517, 997} };
	std::string answer = "";
	for (auto &&e : vv) {
		answer += std::to_string(vertices.at(e - 1));
	}
	std::cout << answer << std::endl;

	return 0;
}