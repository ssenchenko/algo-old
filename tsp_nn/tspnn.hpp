#ifndef TSPNN_HPP
#define TSPNN_HPP

#include <vector>
#include <list>
#include <string>
#include <exception>
#include <iostream>

#include "debug.h"

typedef double distance;
// typedef size_t index_t;

distance const _INF_ = 999999999.99;

struct Point {
	double x;
	double y;
	Point (double x, double y);
	Point () {};
	Point& operator= (Point const &other);
};
std::ostream& operator<< (std::ostream &o, Point const &p);

class Cities {
	// to store points, 'model'
	std::vector<Point> storage_;
	// to quickly iterate through points 
	// and delete them from the 'view' not affecting storage
	// in this case deleting from cities_ doesn't require time on physical deletion
	std::list<Point*> cities_;
	size_t size_;
public:
	class iterator;
	friend class iterator;
	Cities() : size_(0) {};
	void resize(size_t s);
	void add(double x, double y);
	// negative index is allowed
	// -1 means last
	void remove(Cities::iterator it) throw (std::out_of_range);
	size_t size() const;
	Point* front() const;
	Point* back() const;
	class iterator {
		Cities &container_;
		std::list<Point*>::iterator index_;
	public:
		// iterator pointing to the first Point
		iterator(Cities &container);
		// iterator pointing to the second Point
		iterator(Cities &container, bool end);
		iterator(iterator const &it);
		iterator& operator= (iterator const &it);
		Point* operator*() const;
		iterator operator++(); // prefix form
		iterator operator++(int); //postfix form
		bool operator==(iterator const &it) const;
		bool operator!=(iterator const &it) const;
		friend class Cities;
	};
	iterator begin();
	iterator end();
};

// squared euclidean distance between 2 points
distance get_sq_dist(Point const &u, Point const &v);

// reads city coordinates from file at path and writes it to cities vector
bool read_task(std::string const &path, Cities &cities);

// calculates the distance of the travelling sales man route
// using nearest neighbour hearistics
distance tspnn(Cities &cities);

#endif //TSPNN_HPP