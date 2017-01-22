//
//  graph.cpp
//  Algorithms
//
//  Created by  Slava Senchenko on 2016-12-10.
//  Copyright © 2016  Slava Senchenko. All rights reserved.
//

#include "graph.hpp"
#include <iomanip>
#include <algorithm>
#include <unordered_set>

using std::istream;
using std::ostream;
using std::list;
using std::forward_list;

vertex_label VSet::FT_COUNTER = 0l;
int const Vertex::_NO_POS_ = -1;

Vertex::Vertex() {
    label_ = 0l;
    explored_ = false;
	heap_pos_ = _NO_POS_;
}

Vertex::~Vertex() {}

Vertex::Vertex(vertex_label vlabel) {
    label_ = vlabel;
    explored_ = false;
	heap_pos_ = _NO_POS_;
}

Vertex::Vertex(Vertex const &other) {
    label_ = other.label_;
    explored_ = other.explored_;
	heap_pos_ = other.heap_pos_;
}

Vertex::Vertex(Vertex &&other) {
    label_ = std::move(other.label_);
    explored_ = std::move(other.explored_);
	heap_pos_ = std::move(other.heap_pos_);
}

bool Vertex::operator> (Vertex const &other) const {
    return label_ > other.label_;
}
bool Vertex::operator< (Vertex const &other) const {
    return label_ < other.label_;
}
bool Vertex::operator== (Vertex const &other) const {
    return label_ == other.label_;
}

bool Vertex::explored() const { return explored_; }
void Vertex::unexplore() { explored_ = false; }
void Vertex::explore() { explored_ = true; }

vertex_label Vertex::label() const { return label_; }
void Vertex::label(vertex_label vlabel) { label_ = vlabel; }


VSet::VSet() {
    v_num_ = 0;
}

VSet::VSet(size_t capacity) : vertices_(capacity, NULL), finishing_time_(capacity) {
    v_num_ = capacity;
}

VSet::~VSet() {
    if (!finishing_time_.empty())
        finishing_time_.erase(finishing_time_.begin(), finishing_time_.end());
    for (auto &&v : vertices_)
        delete v;
    vertices_.erase(vertices_.begin(), vertices_.end());
}

size_t VSet::v_num() { return v_num_; }
std::vector<Vertex *> * const VSet::vertices_ptr() { return &vertices_; }
std::vector<Vertex *> * const VSet::finishing_time_ptr() { return &finishing_time_; }
//vertex_label VSet::ft_counter() { return ft_counter_; }
//void VSet::ft_counter(vertex_label n) { ft_counter_ = n; }

Vertex* VSet::add_vertex(vertex_label vlabel) throw (add_vertex_error) {
    Vertex * v = NULL;
    
    if (vlabel > v_num_ + 1) {
        std::string w = "Vertex " + std::to_string(vlabel) + " is out of range " + std::to_string(v_num_);
        throw add_vertex_error(w);
    }
    else if (vlabel == v_num_ + 1) {
        v = new Vertex(vlabel);
        vertices_.push_back(v);
        ++v_num_;
    }
    else if (vertices_.at(vlabel - 1) == NULL) {
        v = new Vertex(vlabel);
        vertices_.at(vlabel - 1) = v;
    }
    else
        v = vertices_.at(vlabel - 1);
    
    return v;
}

Graph::Graph(VSet &vertices) : vertices_(&vertices), adjacency_(vertices.v_num()) {
    e_num_ = 0l;
    valid_scc_ = false;
    sorted_scc_ = false;
}

Graph::~Graph() {
    if (!adjacency_.empty()) {
        for (auto &&e : adjacency_)
            if (!e.empty())
                e.clear();
        adjacency_.erase(adjacency_.begin(), adjacency_.end());
    }
    vertices_ = NULL;
}

Edge Graph::add_edge(vertex_label from, vertex_label to, int weight) { // for nondirected graphs
    
    Edge edge = add_edge_di(from, to, weight);
    if (edge.tail_ptr() != NULL && edge.head_ptr() != NULL)
        adjacency_.at(edge.head_ptr()->label() - 1).emplace_front(Edge(true, edge));
    
    return edge;
}

Edge Graph::add_edge_di(vertex_label from, vertex_label to, int weight) { // for directed graphs
    
    Vertex *from_ptr = NULL, *to_ptr = NULL;
    
    try {
        from_ptr = vertices_->add_vertex(from);
        to_ptr = vertices_->add_vertex(to);
        for (size_t i = vertices_->v_num() - adjacency_.size(); i > 0; i--) {
            list<Edge> l;
            adjacency_.push_back(l);
        }
        adjacency_.at(from - 1).emplace_front(Edge(from_ptr, to_ptr, weight));
            
        ++e_num_;
        valid_scc_ = false;
        sorted_scc_ = false;
    }
    catch (add_vertex_error e) {
        std::cerr << e.what() << std::endl;
    }
    return adjacency_.at(from - 1).front();
}

void Graph::unexplore_all() {
    for (auto &&v : *vertices_->vertices_ptr()) {
        v->unexplore();
    }
}

ostream& operator<< (ostream& out, Graph &g) {
    
    for (auto&& v : *g.vertices_->vertices_ptr()) {
        out << std::setw(6) << v->label() << " |";
        for (auto&& e : g.adjacency_.at(v->label() - 1)) {
            out << " " << e.head_ptr()->label() << "," << e.weight();
        }
        out << std::endl;
    }
    
    return out;
}

size_t Graph::scc() const {
    if (valid_scc_)
        return scc_.size();
    else
        return 0;
}

std::string Graph::scc_numbers(size_t n) {
    
    if (valid_scc_)
        if (!sorted_scc_) 
            std::sort(scc_.begin(), scc_.end(), std::greater<vertex_label>());
    std::string s = "";
    std::vector<vertex_label>::iterator it_end, it = scc_.begin();
    if (n == 0 || n > scc_.size())
        it_end = scc_.end();
    else
        it_end = it + n;
    for (; it != it_end; it++) {
        s += std::to_string(*it);
        s += ",";
    }
    if (n > scc_.size())
        for (vertex_label i = n - scc_.size(); i > 0; i--)
            s += "0,";
    s.pop_back();
    
    return s;
}

void Graph::compute_ft() {
    VSet::FT_COUNTER = 0l;
    DFS_loop(*vertices_->vertices_ptr(), adjacency_, vertices_->finishing_time_ptr(), NULL);
}

void Graph::compute_scc() {
    unexplore_all();
    DFS_loop(*vertices_->finishing_time_ptr(), adjacency_, NULL, &scc_);
    valid_scc_ = true;
}

void DFS_loop(std::vector<Vertex*> &vertices, std::vector<std::list<Edge>> &adjacency,
              std::vector<Vertex*> *finishing_time, std::vector<vertex_label> *scc) {
    
    for (auto rit = vertices.rbegin(), rit_end = vertices.rend(); rit != rit_end; ++rit)
        if (!(*rit)->explored()) {
            if (scc)
                scc->push_back(1); // add 1 scc
            DFS(adjacency, *rit, finishing_time, scc);
        }
        
}

void DFS(std::vector<std::list<Edge>> &adjacency, Vertex* p_vertex,
         std::vector<Vertex*> *finishing_time, std::vector<vertex_label> *scc) {
    
    std::forward_list<Vertex*> DFS_stack; // stack to progress with DFS
    std::forward_list<Vertex*> time_stack; // stack to compute finishing time
    
    p_vertex->explore();
    DFS_stack.push_front(p_vertex);
    if (finishing_time)
        time_stack.push_front(p_vertex);
    
    Vertex* p_curr_vert = NULL;
    
    while (!DFS_stack.empty()) {
        p_curr_vert = DFS_stack.front();
        DFS_stack.pop_front();
        bool has_out = false;
        for (auto &&adj : adjacency.at(p_curr_vert->label() - 1))
            if (!(adj.head_ptr()->explored())) {
                adj.head_ptr()->explore();
                DFS_stack.push_front(adj.head_ptr());
                if (finishing_time)
                    time_stack.push_front(adj.head_ptr());
                if (scc) {
                    auto it = scc->end();
                    (*(it - 1))++;
                }
                has_out = true;
            }
        if (!has_out && finishing_time) {
            if (!DFS_stack.empty())
                while (time_stack.front() != DFS_stack.front()) {
                    p_curr_vert = time_stack.front();
                    time_stack.pop_front();
                    finishing_time->at(VSet::FT_COUNTER++) = p_curr_vert;
                }
            else
                while (!time_stack.empty()) {
                    p_curr_vert = time_stack.front();
                    time_stack.pop_front();
                    finishing_time->at(VSet::FT_COUNTER++) = p_curr_vert;
                }
        }
    }
}

Edge::Edge() : p_tail_(NULL), weight_(0), p_head_(NULL) {}
Edge::Edge(Vertex *p_tail, Vertex *p_head, int weight) : p_tail_(p_tail), weight_(weight), p_head_(p_head){}
Edge::Edge(bool reverse, Edge const &other) : p_tail_(NULL), weight_(0), p_head_(NULL) {
    if (reverse) {
        p_head_ = other.p_tail_;
        p_tail_ = other.p_head_;
        weight_ = other.weight_;
    }
}
Edge::Edge(Edge const &other) : p_tail_(NULL), weight_(0), p_head_(NULL) {
    if (this != &other) {
        p_head_ = other.p_head_;
        weight_ = other.weight_;
        p_tail_ = other.p_tail_;
    }
}
Edge::Edge(Edge &&other) : p_tail_(std::move(other.p_tail_)),
                        weight_(std::move(other.weight_)),
                        p_head_(std::move(other.p_head_)) {}

Edge::~Edge() {
    p_tail_ = NULL;
    p_head_ = NULL;
}

Edge Edge::operator= (Edge const &other) {
    if (this != &other) {
        p_head_ = other.p_head_;
        weight_ = other.weight_;
        p_tail_ = other.p_tail_;
    }
    return *this;
}
Edge Edge::operator= (Edge &&other) {
    if (this != &other) {
        p_tail_ = std::move(other.p_tail_);
        weight_ = std::move(other.weight_);
        p_head_ = std::move(other.p_head_);
    }
    return *this;
}

Vertex* Edge::tail_ptr() const { return p_tail_; }
Vertex* Edge::head_ptr() const { return p_head_; }
int Edge::weight() const { return weight_; }

bool Edge::operator< (Edge const &other) const {
    return this->weight_ < other.weight_;
}

std::vector<weight_t> Graph::shortest_path(vertex_label src) {
    
    // a container to storage edges to process
    std::vector<distance_t> djk;

	// shortest path from src vertex to every other vertex
    std::vector<weight_t> dist (vertices_->vertices_ptr()->size(), _INF_);
    
    // intialize with source distance and make a heap
    djk.emplace_back(std::make_pair(0, vertices_->vertices_ptr()->at(src - 1)));
	std::make_heap(djk.begin(), djk.end(), distComp);
    
    dist.at(src - 1) = 0ul;
    
    while (!djk.empty()) {
        
        // get a min distance vertex from the heap
        std::pop_heap(djk.begin(), djk.end(), distComp);
        Vertex* tmp = djk.back().second;
        djk.pop_back();
        
        weight_t v_dist = 0ul, *w_dist;
        // get all edges with tail at vertex tmp
        for (auto &&e : adjacency_.at(tmp->label() - 1)) {
            w_dist = &dist.at(e.head_ptr()->label() - 1);
            v_dist = dist.at(tmp->label() - 1) + e.weight();
            if (*w_dist > v_dist) {
				// update distance and add vertex to the heap
                *w_dist = v_dist;
                djk.emplace_back(std::make_pair(*w_dist, e.head_ptr()));
                std::push_heap(djk.begin(), djk.end(), distComp);
			}
        }
    }
    
    return dist;
}

std::vector<weight_t> Graph::mst_prim(vertex_label src) {

	// a container to storage vertices and distance to them to process
	std::vector<distance_t> prim;

	// number of vertices in the graph
	size_t const vert_num = vertices_->vertices_ptr()->size();

	// min distance (cost) from any vertex in the tree an unexplored vertex
	std::vector<weight_t> dist (vert_num, _INF_);

	// already explored vertices
	std::unordered_set<vertex_label> explored_vertices;

	// intialize with source distance and make a heap
	prim.emplace_back(std::make_pair(0, vertices_->vertices_ptr()->at(src - 1)));
	std::make_heap(prim.begin(), prim.end(), distComp);

	vertex_label processed = 0;
	while (processed < vert_num) {

		// get a min distance vertex from the heap
		std::pop_heap(prim.begin(), prim.end(), distComp);
		Vertex* tmp = prim.back().second;
		// update distance
		if (dist.at(tmp->label() - 1) > prim.back().first) {
			dist.at(tmp->label() - 1) = prim.back().first;
			processed++;
		}

		// add vertex to the set of explored
		explored_vertices.emplace(tmp->label());
		// remove from the heap
		prim.pop_back();

		// get all edges with tail at vertex tmp
		for (auto &&e : adjacency_.at(tmp->label() - 1)) {
			if (explored_vertices.find(e.head_ptr()->label()) == explored_vertices.end()) {
				prim.emplace_back(std::make_pair(e.weight(), e.head_ptr()));
				std::push_heap(prim.begin(), prim.end(), distComp);
			}
		}
	}

	return dist;

}

