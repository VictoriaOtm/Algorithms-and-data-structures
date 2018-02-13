//
// Created by otm on 07.10.17.
//

#ifndef DZ4_QUEUE_H
#define DZ4_QUEUE_H

#include "Stack.hpp"


template <class T>
class Queue {
public:
    Queue() = default;
    ~Queue() = default;

    const bool empty(){
        return (_size == 0);
    }

    const size_t size(){
        return _size;
    }

    void push_back(const T& value){
        left_stack.push(value);
        ++_size;
    }

    T& pop_front() throw(std::runtime_error){
        if (_size != 0){
            --_size;

            if (!right_stack.empty()){
                return right_stack.pop();
            }
            else{
                while (!left_stack.empty()){
                    right_stack.push(left_stack.pop());
                }
                return right_stack.pop();
            }
        }
        else{
            throw std::runtime_error("Queue size = 0");
        }
    }

private:
    Stack<T> left_stack;
    Stack<T> right_stack;

    size_t _size = 0;
};


#endif //DZ4_QUEUE_H
