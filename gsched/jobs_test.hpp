#ifndef JOBS_TEST_HPP
#define JOBS_TEST_HPP

#include <vector>
#include <string>
#include <algorithm>

// description of job
// weigth and time
struct Job {
	int weight;
	int time;
	Job(int w, int t) : weight(w), time(t) {};
	Job(Job const &j) : weight(j.weight), time(j.time) {};
	Job(Job &&j) : weight(std::move(j.weight)), time(std::move(j.time)) {};
	Job operator= (Job const &j) { weight = j.weight; time = j.time; return *this; };
	Job& operator= (Job &&j) { weight = std::move(j.weight); time = std::move(j.time); return *this; };
};

// first: key - defined as deciided by user
// second: struct job
typedef std::pair<float, Job> jobs_t; 

// lambda function to compare jobs_t type
auto compare_jobs = [](jobs_t const &left, jobs_t const &right) { 
	if (left.first == right.first)
		return left.second.weight > right.second.weight;
	else
		return left.first > right.first; 
};

// function to read input file (provided with a task)
// key is 0 by default
std::vector<jobs_t> read_input(std::string const &path);

// path to the folder with data
std::string const scPath = "/Users/slava_senchenko/Documents/Education/Stanford/Algorithms/test_data/";
// data file name
std::string const scFileName = "c3w1_jobs.txt";

// function to calculate timees in 
// ORDERED jobs vector
int calculate_time (std::vector<jobs_t>::iterator begin, std::vector<jobs_t>::iterator curr);

// function to calculate
// sum of weighted completion times
// jobs are passed by value not to mess up the original time
template <typename Lambda>
long summarise (std::vector<jobs_t> jobs, Lambda &&calculate_key) {
	// calculate jobs keys
	for (auto &&key_job : jobs) {
		key_job.first = calculate_key(key_job.second);
	}
	// sort by key
	std::sort(jobs.begin(), jobs.end(), compare_jobs);
	
	// summarise weigthed time
	long sum = 0l;
	for (auto it_begin = jobs.begin(), it_end = jobs.end(), it = it_begin; it != it_end; ++it) {
		sum += calculate_time(it_begin, it) * it->second.weight;
	}

	return sum;
};

#endif // JOBS_TEST_HPP