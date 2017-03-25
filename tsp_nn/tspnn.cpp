#include <fstream>
#include <iostream>
#include <cmath>

#include "tspnn.hpp"
#include "myutil.h"

using std::cerr;
using std::cout;
using std::endl;

Point::Point (double x, double y) {
	this->x = x;
	this->y = y;
}

Point& Point::operator= (Point const &other) {
	x = other.x; 
	y = other.y;
	return *this;
}

std::ostream& operator<< (std::ostream &out, Point const &p) {
	out << "[" << p.x << ", " << p.y << "]";
	return out;
}

void Cities::resize(size_t s) {
	storage_.reserve(s);
	size_ = s;
}

void Cities::add(double x, double y) {
	storage_.emplace_back(x, y);
	cities_.emplace_back(&storage_.back());
}

void Cities::remove(Cities::iterator it) throw (std::out_of_range) {
	cities_.erase(it.index_);
	size_--;
}

size_t Cities::size() const { return size_; }

Point* Cities::front() const { return cities_.front(); }
Point* Cities::back() const { return cities_.back(); }

Cities::iterator::iterator(Cities &c) : container_(c), index_(c.cities_.begin()) {}
Cities::iterator::iterator(Cities &c, bool end) : container_(c), index_(c.cities_.end()) {}
Cities::iterator::iterator(iterator const &it) : container_(it.container_), index_(it.index_) {}
Cities::iterator& Cities::iterator::operator= (iterator const &it) {
	index_ = it.index_;
	return *this;
}

Cities::iterator Cities::begin() { return Cities::iterator(*this); }
Cities::iterator Cities::end() { return Cities::iterator(*this, true); }

Point* Cities::iterator::operator* () const { return *index_; }

Cities::iterator Cities::iterator::operator++ () { 
	++index_;
	return *this; 
}
Cities::iterator Cities::iterator::operator++ (int i) { 
	Cities::iterator it(*this);
	index_++;
	return it; 
}

bool Cities::iterator::operator== (Cities::iterator const &it) const { 
	if (&(this->container_) == &(it.container_) && (this->index_ == it.index_))
		return true;
	else
		return false;
}

bool Cities::iterator::operator!= (Cities::iterator const &it) const { 
	if (&(this->container_) != &(it.container_) || (this->index_ != it.index_))
		return true;
	else
		return false;
}

distance get_sq_dist(Point const &u, Point const &v) {
	return (u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y);
}

bool read_task(std::string const &path, Cities &cities) {
	bool result = true;
	std::ifstream file;
	file.open(path);
	if (file.fail()) {
		file.clear();
		std::cerr << scNoFileName << std::endl;
		result = false;
	}
	else {
		std::string s;
		// first line -- number of cities
		getline(file, s);
		if (file.fail()) {
			file.clear();
			cerr << scGetlineError << endl;
			result = false;
		}
		else if (file.eof()) {
			file.clear();
			cerr << scUnexpectedEOF << endl;
			result = false;
		}
		else {
			try {
				// read number of jobs
				size_t size = getLong(s);
				// resize a vector for cities
				cities.resize(size);
			}
			catch (WrongIntInput e) {
				std::cerr << e.what() << std::endl;
				return false;
			}
			std::vector<double> v;
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
				v = parse_for_double(s, " ");
				cities.add(v.at(1), v.at(2));
			}
		}
	}
	file.close();
	return result;
}

distance tspnn(Cities &cities) {
	distance Distance = 0.0; // overal TS route distance
	distance lmd; // local minimum squared distance to compare
	distance csd; // current squared distance
	// index of the point with local minimum distance to the current one
	// and the point to start next iteration
	Cities::iterator min_index = cities.begin(); 
	// remember starting point
	Point* Start = cities.front();
	// loop through unprocessed cities
	Point* Current = *min_index; // the point we compare to each other to get the distance
	// use the first element as a current and remove it from cities
	cities.remove(min_index);
	while (cities.size() > 0) {
		lmd = _INF_;
		for (Cities::iterator j = cities.begin(); j != cities.end(); ++j) { 
			if ((csd = get_sq_dist(*Current, **j)) < lmd) {
				lmd = csd;
				min_index = j;
			}	
		}
		#if (__TRACE__)
			cout << *Current << "-->" << **min_index << " : " << std::sqrt(lmd) << endl;
		#endif
		Distance += std::sqrt(lmd);
		Current = *min_index;
		cities.remove(min_index);
	}
	// add distance from last point to the beginning
	// now last point is cities[0] and is the only accessable element in cities
	lmd = get_sq_dist(*Start, *Current);
	#if (__TRACE__)
		cout << *Current << "-->" << *Start << " : " << std::sqrt(lmd) << endl;
	#endif
	Distance += std::sqrt(lmd);
	return Distance;
}