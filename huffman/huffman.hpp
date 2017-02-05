#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <vector>
#include <string>
#include <queue>
#include <iostream>

using std::string;
using std::vector;

// path to the folder with data
string const scPath = "/Users/slava_senchenko/Documents/Education/Stanford/Algorithms/test_data/";
// data file name
string const scFileName = "c3w3_huffman.txt";

// Huffman tree/node
template <class T>
class HuffmanTree {
	T key_;
	string label_; 
	string code_;
	HuffmanTree *left_ptr_, *right_ptr_;

	HuffmanTree() {};

public:
	HuffmanTree (T key, string label, string code = "", 
		HuffmanTree *p_left = nullptr, HuffmanTree *p_right = nullptr);
	~HuffmanTree();
	HuffmanTree(HuffmanTree const &ht);
	HuffmanTree(HuffmanTree &&ht);
	HuffmanTree operator= (HuffmanTree const &ht);
	HuffmanTree& operator= (HuffmanTree &&ht);

	// nodes comparison
	bool operator> (HuffmanTree<T> const &rhs) const { return key_ > rhs.key_; };
	bool operator< (HuffmanTree<T> const &rhs) const { return key_ < rhs.key_; }; 

	// build the tree together
	static HuffmanTree<T>* build(vector< HuffmanTree<T>* > nodes);
	
	// assign codes
	void encode(string code);

	template <class S>
	friend std::ostream& operator<< (std::ostream& out, HuffmanTree<S> const &ht);
};

// reads txt file with list of huffman tree nodes
// if description = true, the first row contains the number of rows in file
vector< HuffmanTree<long>* > read_array(string const &path, bool description);

// ----------------------------- template implementation -------------------------------

template <class T>
HuffmanTree<T>::HuffmanTree (T key, string label, string code, 
		HuffmanTree *p_left, HuffmanTree *p_right) {
	key_ = key;
	label_ = label;
	code_ = code;
	left_ptr_ = p_left;
	right_ptr_ = p_right;
}

template <class T>
HuffmanTree<T>::~HuffmanTree() {
	if (left_ptr_) delete left_ptr_;
	if (right_ptr_) delete right_ptr_;
}

// copy constructor
template <class T>
HuffmanTree<T>::HuffmanTree(HuffmanTree const &ht) {
    key_ = ht.key;
    label_ = ht.label;
    code_ = ht.code;
    if (ht.left_ptr_)
		left_ptr_ = new HuffmanTree(*ht.left_ptr_);
    if (ht.right_ptr_)
		right_ptr_ = new HuffmanTree(*ht.right_ptr_);
}

// move constructor
template <class T>
HuffmanTree<T>::HuffmanTree(HuffmanTree &&ht) {
	key_ = std::move(ht.key);
	label_ = std::move(ht.label);
	code_ = std::move(ht.code);
	if (left_ptr_) delete left_ptr_;
	left_ptr_ = ht.left_ptr_;
	ht.left_ptr_ = nullptr;
	if (right_ptr_) delete right_ptr_;
	right_ptr_ = ht.right_ptr_;
	ht.right_ptr_ = nullptr;
}

// copy assignment
template <class T>
HuffmanTree<T> HuffmanTree<T>::operator= (HuffmanTree const &ht) {
	if (this != &ht) {
		key_ = ht.key;
		label_ = ht.label;
		code_ = ht.code;
		if (ht.left_ptr_)
			left_ptr_ = new HuffmanTree(*ht.left_ptr_);
		if (ht.right_ptr_)
			right_ptr_ = new HuffmanTree(*ht.right_ptr_);
	}
	return *this;
}

// move assignment
template <class T>
HuffmanTree<T>& HuffmanTree<T>::operator= (HuffmanTree &&ht) {
	if (this != &ht) {
		key_ = std::move(ht.key);
		label_ = std::move(ht.label);
		code_ = std::move(ht.code);
		if (left_ptr_) delete left_ptr_;
		left_ptr_ = ht.left_ptr_;
		ht.left_ptr_ = nullptr;
		if (right_ptr_) delete right_ptr_;
		right_ptr_ = ht.right_ptr_;
		ht.right_ptr_ = nullptr;
	}
	return *this;
}

// output
template <class S>
std::ostream& operator<< (std::ostream& out, HuffmanTree<S> const &ht) {
	if (ht.label_!= "dummy")
		out << ht.code_.size() << std::endl;;
	if (ht.left_ptr_)
		out << *ht.left_ptr_;
	if (ht.right_ptr_)
		out << *ht.right_ptr_;
	return out;
}

// assign codes to the tree
template <class T>
void  HuffmanTree<T>::encode(string code) {
	code_ += code;
	if (left_ptr_)
		left_ptr_->encode(code_ + "0");
	if (right_ptr_)
		right_ptr_->encode(code_ + "1");
}

// build the tree together
template <class T>
HuffmanTree<T>* HuffmanTree<T>::build(vector< HuffmanTree<T>* > nodes) {
	// lambda to compare HuffmanTree pointers
	auto ht_greater = [](HuffmanTree<T> const * const lhs, HuffmanTree<T> const * const rhs) {
		return lhs->key_ > rhs->key_;
	};

	std::priority_queue< HuffmanTree<T>*, vector< HuffmanTree<T>* >, decltype(ht_greater) > 
																				min_heap(ht_greater, nodes);
	HuffmanTree<T> *left, *right, *root;
	
	while (min_heap.size() != 1) { // there is only node inside and it is the root node
		left = min_heap.top();
		min_heap.pop();
		right = min_heap.top();
		min_heap.pop();

		root = new HuffmanTree(left->key_ + right->key_, "dummy", "", left, right);
		min_heap.push(root);
	}
	
	return root;
}

#endif