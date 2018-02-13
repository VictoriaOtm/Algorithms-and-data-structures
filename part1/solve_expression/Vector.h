//
// Created by otm on 09.10.17.
//

#ifndef DZ5VER2_VECTOR_H
#define DZ5VER2_VECTOR_H

#include <cstddef>
#include <cstring>
#include <iostream>

namespace vic{
    template <class T>
    class Vector{
    public:
        Vector() : _size(0), _capacity(16) {
            _data = new T[_capacity]();
        }
        ~Vector() {
            delete[] _data;
        }

        const bool empty() {
            return (_size == 0);
        }

        const std::size_t size(){
            return _size;
        }

        void push(const T &value) {
            if (_size == _capacity) {
                resize_data(2);
            }
            _data[_size] = value;
            ++_size;
        }

        T& operator[](size_t index) {
            if (index < _size)
                return _data[index];
            throw std::runtime_error("index is bigger than vector's size");
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
}


#endif //DZ5VER2_VECTOR_H
