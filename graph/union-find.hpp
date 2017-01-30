//
// Created by  Slava Senchenko on 2017-01-28.
//

#ifndef GRAPH_UNION_FIND_HPP
#define GRAPH_UNION_FIND_HPP

#include <vector>
#include <list>
#include <iostream>

namespace graph {

	template <typename T>
	class Node;

	template <typename T>
	class UnionFind {
	public:
		typedef unsigned long index_t;
	protected:
		std::vector< Node<T>* > forest_;

		// finds parent node
		Node<T>* find_parent_ptr(index_t index);
		Node<T>* find_parent_ptr(Node<T>* node_ptr);

	public:
		UnionFind() {};
		virtual ~UnionFind();
		template <class InputIterator>
		UnionFind(InputIterator first, InputIterator last, size_t capacity = 0);

		// constructs new node inside the forest
		void emplace(T value);

		// finds element's subset by index value
		T find(index_t index);

		// unions two trees by setting the same parent for them
		void union_them(index_t lhs, index_t rhs);

		// print mostly for test purposes
		template <typename U>
		friend std::ostream& operator<< (std::ostream &out, UnionFind<U> &uf);
	};

	template <typename T>
	class Node {
		T value_;
		Node* parent_ptr_;
		size_t rank_;

		Node () {};
	public:
		explicit Node (T value, Node<T> *parent_ptr = nullptr, size_t rank = 0);
		Node (Node const &other) : value_(other.value_), parent_ptr_(other.parent_ptr_), rank_(other.rank_) {};
		Node (Node &&other) : value_(std::move(other.value_)), parent_ptr_(std::move(other.parent_ptr_)),
							  rank_(std::move(other.rank_)) {};

		Node operator= (Node const &other);
		Node operator= (Node &&other);

		T value() { return value_; };
		Node* parent_ptr() { return parent_ptr_; };
		size_t rank() { return rank_; };

		void parent_ptr(Node *node_ptr) { parent_ptr_ = node_ptr; };
		void rank(size_t new_rank) { rank_ = new_rank; };
	};

// ----------------------------------------------implementation--------------------------------------------

	template <typename T>
	Node<T>::Node (T value, Node<T> *parent_ptr, size_t rank) :
			value_(value), parent_ptr_(parent_ptr), rank_(rank) {
		if (parent_ptr_ == nullptr)
			parent_ptr_ = this;
	}

	template <typename T>
	Node<T> Node<T>::operator= (Node<T> const &other) {
		if (this != &other) {
			value_ = other.value_;
			parent_ptr_ = other.parent_ptr_;
			rank_ = other.rank_;
		}
		return *this;
	}

	template <typename T>
	Node<T> Node<T>::operator= (Node<T> &&other) {
		if (this != &other) {
			value_ = std::move(other.value_);
			parent_ptr_ = std::move(other.parent_ptr_);
			rank_ = std::move(other.rank_);
		}
		return *this;
	};

	template <typename T>
	UnionFind<T>::~UnionFind() {
		for (auto &&node : forest_)
			delete node;
	}

	template <typename T>
	template <class InputIterator>
	UnionFind<T>::UnionFind(InputIterator first, InputIterator last, size_t capacity) {
		if (capacity != 0)
			forest_.reserve(capacity);

		for (; first != last; ++first) {
			emplace(*first);
		}
	}

	template <typename T>
	void UnionFind<T>::emplace(T value) {
		forest_.emplace_back(new Node<T>(value));
	}

	template <typename T>
	T UnionFind<T>::find(index_t index) {
		return find_parent_ptr(index)->value();
	}

	template <typename T>
	Node<T>* UnionFind<T>::find_parent_ptr(Node<T>* node_ptr) {
		if (node_ptr != node_ptr->parent_ptr())
			node_ptr->parent_ptr(find_parent_ptr(node_ptr->parent_ptr()));
		return node_ptr->parent_ptr();
	}

	template <typename T>
	Node<T>* UnionFind<T>::find_parent_ptr(index_t index) {
		Node<T>* tmp = forest_.at(index);
		return find_parent_ptr(tmp);
	}

	template <typename T>
	void UnionFind<T>::union_them(index_t lhs, index_t rhs) {
		Node<T>* lhs_parent_ptr = find_parent_ptr(lhs);
		Node<T>* rhs_parent_ptr = find_parent_ptr(rhs);
		if (lhs_parent_ptr == rhs_parent_ptr) return;

		if (lhs_parent_ptr->rank() > rhs_parent_ptr->rank())
			rhs_parent_ptr->parent_ptr(lhs_parent_ptr);
		else {
			lhs_parent_ptr->parent_ptr(rhs_parent_ptr);
			if (lhs_parent_ptr->rank() == rhs_parent_ptr->rank())
				rhs_parent_ptr->rank(rhs_parent_ptr->rank() + 1);
		}
	}

	template <typename T>
	std::ostream& operator<< (std::ostream &out, UnionFind<T> &uf) {
		for (auto &&e : uf.forest_) {
			out << "Value = " << e->value() << "; rank = " << e->rank()
				<< "; parent = " << e->parent_ptr()->value() << std::endl;
		}
		return out;
	}
}


#endif //GRAPH_UNION_FIND_HPP
