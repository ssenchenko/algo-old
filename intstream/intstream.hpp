//
//  intstream.hpp
//  Algorithms
//
//  Created by  Slava Senchenko on 2016-12-24.
//  Copyright © 2016  Slava Senchenko. All rights reserved.
//
//  this code was developed as a part of the assignment of
//  Stanford Algorithm Specialization
//  https://www.coursera.org/specializations/algorithms


#ifndef intstream_hpp
#define intstream_hpp

#include <queue>
#include <string>

// list of available models
typedef enum {
    heap = 0,
    binary_tree
} models_t ;

// abstract class for model interface
template <class T>
class abstract_model {
public:
    virtual ~abstract_model() = 0;
    virtual void push(T element) = 0;
    virtual T median() = 0;
};

template <class T>
abstract_model<T>::~abstract_model() {}

//  class vector_heeap extends functionality of priority_queue
//  based on a vector's container implementation
//  adds
//      -- a method to reserve space
template <class T, class Compare>
class vector_heap : public std::priority_queue<T, std::vector<T>, Compare> {
public:
    void reserve(size_t heap_size) { this->c.reserve(heap_size); };
};

// heap implementation of abstract model
template <class T>
class heap_model : public abstract_model<T> {
    vector_heap<T, std::less<T>> low_part_;
    vector_heap<T, std::greater<T>> high_part_;
    
    size_t reserved_;
    
public:
    heap_model() {reserved_ = 0;};
    explicit heap_model(size_t heap_size);
    ~heap_model() {};
    
    void balance();
    size_t size() { return low_part_.size() + high_part_.size(); };
    
    virtual void push(T element);
    virtual T median();
};

// exception class if client uses int_stream without model set
class no_model : public std::logic_error {
public:
    no_model() : std::logic_error("No model set for this integer stream") {};
};

// client interface for the model
class int_stream {
    abstract_model<int> *model_ptr_;
    
public:
    int_stream();
    int_stream(models_t model_id, size_t size = 0);
    ~int_stream();
    
    void model(models_t model_id, size_t size = 0);
    
    int median(int another_in) throw (no_model);
};


//----------- heap_model implementation ------------------

template <class T>
heap_model<T>::heap_model(size_t heap_size) {
    reserved_ = heap_size;
    size_t half = reserved_ / 2; // floor
    low_part_.reserve(half);
    // if size_ is odd put one more number into high_part_
    if (heap_size % 2 == 0)
        high_part_.reserve(half);
    else
        high_part_.reserve(half + 1);
    
}

template <class T>
void heap_model<T>::push(T element) {
    
    if (low_part_.empty() && high_part_.empty())
        high_part_.push(element);
    else if (high_part_.empty()) {
        if (element >= low_part_.top())
            high_part_.push(element);
        else
            low_part_.push(element);
    }
    else if (low_part_.empty()) {
        if (element <= high_part_.top())
            low_part_.push(element);
        else
            high_part_.push(element);
    }
    else if (element < low_part_.top())
        low_part_.push(element);
    else if (element > high_part_.top())
        high_part_.push(element);
    else // (element >= low_part_.top() && element <= high_part_.top())
        if (low_part_.size() < high_part_.size())
            low_part_.push(element);
        else
            high_part_.push(element);
    balance();
}

template <class T>
void heap_model<T>::balance() {
    
    T temp;
    while (low_part_.size() > high_part_.size() + 1) {
        temp = low_part_.top();
        low_part_.pop();
        high_part_.push(temp);
    }
    while (high_part_.size() > low_part_.size() + 1) {
        temp = high_part_.top();
        high_part_.pop();
        low_part_.push(temp);
    }

}

template <class T>
T heap_model<T>::median() {
    if (low_part_.size() >= high_part_.size())
        return low_part_.top();
    else
        return high_part_.top();
}



#endif /* intstream_hpp */
