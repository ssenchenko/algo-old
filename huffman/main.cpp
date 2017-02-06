#include "huffman.hpp"
#include <iostream>

int main() {
	// read the file
	std::string file = scPath + scFileName;
	std::vector< HuffmanTree<long>* > ht_array = read_array(file, true);
	if (ht_array.empty()) {
		std::cerr << "Nothing has been loaded" << std::endl;
		return 1;
	}
	HuffmanTree<long>* tree = HuffmanTree<long>::build(ht_array);
	tree->encode("");
	std::cout << *tree;
	delete tree;

	return 0;
}