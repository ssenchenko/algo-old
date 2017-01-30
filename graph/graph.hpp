//
//  graph.hpp
//  Algorithms
//
//  Created by  Slava Senchenko on 2016-12-10.
//  Copyright © 2016  Slava Senchenko. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <vector>
#include <forward_list>
#include <list>
#include <iostream>
#include <string>
#include <stdexcept>

typedef unsigned long vertex_label;
typedef int weight_t;

class Vertex;

typedef std::pair<weight_t, Vertex*> distance_t;
auto distComp = [](distance_t const &e1, distance_t const &e2) { return e1.first > e2.first; };

// INF const to describe that there is no way from vertex A to vertex B
unsigned long const _INF_ = 1000000;

class Vertex {
	vertex_label label_;
	bool explored_;
	int heap_pos_;

protected:
	static int const _NO_POS_; // no position specified

public:
	Vertex();
	~Vertex();
	Vertex(vertex_label label);
	Vertex(Vertex const &other);
	Vertex(Vertex &&other);

	bool operator> (Vertex const &other) const;
	bool operator< (Vertex const &other) const;
	bool operator== (Vertex const &other) const;
	bool operator!= (Vertex const &other) const;

	friend std::ostream& operator<< (std::ostream &out, Vertex const &v);

	bool explored() const;
	void unexplore();
	void explore();

	vertex_label label() const;
	void label(vertex_label vlabel);
};

class add_vertex_error : public std::out_of_range {
public:
	add_vertex_error(std::string& w) : out_of_range(w) {};
};

// set of vertices that can be shared by many graphs
class VSet {
	std::vector<Vertex *> vertices_; // array of vertices
	size_t v_num_; // number of vertices
	std::vector<Vertex *> finishing_time_; // array of vertices ordered from biggest to smallest finishing time
public:
	static vertex_label FT_COUNTER; // finishing time counter

public:
	VSet();
	VSet(size_t capacity);
	~VSet();

	size_t v_num();
	std::vector<Vertex *> * const vertices_ptr();
	std::vector<Vertex *> * const finishing_time_ptr();
//    vertex_label ft_counter();
//    void ft_counter(vertex_label n);

	Vertex* add_vertex(vertex_label vlabel) throw (add_vertex_error);

};

class Edge {
	Vertex *p_tail_;
	Vertex *p_head_;
	weight_t weight_;

	Edge();

public:
	Edge(Vertex *p_tail, Vertex *p_head, int weight = 0);
	Edge(bool reverse, Edge const &other); // if (reverse) swap(p_head_, p_tail_)
	Edge(Edge const &other);
	Edge(Edge &&other);
	~Edge();

	Edge operator= (Edge const &other);
	Edge operator= (Edge &&other);

	Vertex* tail_ptr() const;
	Vertex* head_ptr() const;
	int weight() const;

	bool operator< (Edge const &other) const;
	bool operator== (Edge const &other) const;
	friend std::ostream& operator<< (std::ostream &out, Edge const &e);
};

class Graph {
	size_t e_num_; // number of edges
	bool valid_scc_;
	bool sorted_scc_;

	VSet *vertices_;
	std::vector< std::list<Edge> > adjacency_; // list of adjacent vertices
	// an array of edge pointers it is not mandatory, however for some algorithms it is necessary
	std::vector<Edge*> edges_; // references are not possible here


	std::vector<vertex_label> scc_; // array with number of vertices in each strongly connected component (SCC)

	Graph() {};

protected:
	// methods to operate an array of edges, not for public use
	void init_edges();

public:
	Graph(VSet &vertices);
	~Graph();

	Edge add_edge(vertex_label from, vertex_label to, int weight = 0); // for nondirected graphs
	Edge add_edge_di(vertex_label from, vertex_label to, int weight = 0); // for directed graphs

	void unexplore_all(); // set all vertices unexplored

	friend std::ostream& operator<< (std::ostream& out, Graph& G);

	size_t scc() const; // number of SCC
	std::string scc_numbers(size_t n = 0); // number of elements in first n SSC

	void compute_ft(); // computes finising time
	void compute_scc(); // computes number of SCC

	// Dijkstra algorithm from src vertex to every other vertex
	std::vector<weight_t> shortest_path(vertex_label src);

	// Prim's minimum spanning tree algorithm
	std::vector<weight_t> mst_prim(vertex_label src);

	// Kruskal's minimum spanning tree algorithm
	std::vector<Edge*> mst_kruskal();

	// clustering using Kruskal mst algorithm
	// returns maximum spacing
	long clusters_kruskal(int clusters);

	// DELETE IT!!!!!!
	friend void test_inner(Graph &g);

};


void DFS_loop(std::vector<Vertex*> &vertices, std::vector<std::list<Edge>> &adjacency,
			  std::vector<Vertex*> *finishing_time = nullptr, std::vector<vertex_label> *scc = nullptr);
void DFS(std::vector<std::list<Edge>> &adjacency, Vertex* vertex,
		 std::vector<Vertex*> *finishing_time = nullptr, std::vector<vertex_label> *scc = nullptr);



#endif /* graph_hpp */
