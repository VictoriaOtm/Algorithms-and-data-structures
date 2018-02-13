//
// Created by otm on 07.10.17.
//

#ifndef DZ4_STACK_H
#define DZ4_STACK_H


#include <cstddef>
#include <cstring>
#include <iostream>


template<class T>
class Stack {
public:
    Stack() : _data(0), _size(0), _capacity(16) {
        _data = new T[_capacity]();
    }

    ~Stack() {
        delete[] _data;
    }

    const bool empty() {
        return _size == 0;
    }

    const std::size_t size() {
        return _size;
    }

    void push(const T &value) {
        if (_size == _capacity) {
            resize_data(2);
        }
        _data[_size] = value;
        ++_size;
    }

    const T &top() throw (std::runtime_error){
        if (_size != 0){
            return _data[_size - 1];
        }
        throw std::runtime_error("Stack size = 0");
    }

    T pop() throw(std::runtime_error){
        if (_size != 0) {
            --_size;
            return _data[_size];
        }
        throw std::runtime_error("Stack size = 0");

    }

private:
    T *_data;
    std::size_t _size;
    std::size_t _capacity;

    void resize_data(double capacity_factor) {
        _capacity = static_cast<std::size_t >(_capacity * capacity_factor);

        T *temp = new T[_capacity]();
        std::memcpy(temp, _data, _size * sizeof(T));
        delete[] _data;

        _data = temp;
    }
};


#endif //DZ4_STACK_H
