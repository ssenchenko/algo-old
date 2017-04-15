//
//  intstream.cpp
//  Algorithms
//
//  Created by  Slava Senchenko on 2016-12-24.
//  Copyright © 2016  Slava Senchenko. All rights reserved.
//

#include "intstream.hpp"

int_stream::int_stream(models_t model_id, size_t size) : model_ptr_(nullptr) {
    switch (model_id) {
        case binary_tree: // this option may be added later
//            break;
        case heap:
            if (size) model_ptr_ = new heap_model<int>(size);
            else model_ptr_ = new heap_model<int>();
            break;
    }
}

int_stream::int_stream() : model_ptr_(nullptr){
}

int_stream::~int_stream() {
    if (model_ptr_)
        delete model_ptr_;
}

void int_stream::model(models_t model_id, size_t size) { 
    
    if (model_ptr_)
        delete model_ptr_;
    
    switch (model_id) {
        case binary_tree: // this option may be added later
//            break;
        case heap:
            if (size) model_ptr_ = new heap_model<int>(size);
            else model_ptr_ = new heap_model<int>();
            break;
    }
}

int int_stream::median(int another_in) throw (no_model) {
    
    if (!model_ptr_) throw no_model();
    
    model_ptr_->push(another_in);
    return model_ptr_->median();
}
