//
// Created by otm on 08.10.17.
//

#ifndef DZ5_STRING_H
#define DZ5_STRING_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

namespace vic {
    class String {
    public:
        String() : _size(0), _capacity(8) {
            _data = new char[_capacity]();
        }

        String(const String& another) : _size(another._size),
                                        _capacity(another._capacity) {
            _data = new char[_capacity]();
            memcpy(_data, another._data, _size);
        }

        ~String() {
            delete[] _data;
        }

        String& operator=(const String& another) {
            _size = another._size;
            _capacity = another._capacity;

            delete[] _data;
            _data = new char[_capacity]();
            memcpy(_data, another._data, _size);

            return *this;
        }

        char& operator[](size_t index) {
            if (index < _size)
                return _data[index];
            throw std::runtime_error("index is bigger than size");
        }

        String& operator+=(const char value) {
            if (_size + 2 == _capacity) {
                resize(2);
            }

            _data[_size++] = value;

            return *this;
        }

        friend std::istream& operator>>(std::istream& is, String& str) {

            char c = '\0';
            while (!isgraph(int(c)))
                is.get(c);

            while (is.good()) {
                if (c == ' ' || c == '\n')
                    break;

                if (str._size + 1 == str._capacity - 1) {
                    size_t multiplier = 2;
                    str.resize(multiplier);
                }
                ++str._size;

                str[str._size - 1] = c;
                is.get(c);
            }

            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, const String& str) {
            if (str._size != 0) {
                os << str._data;
            }
            return os;
        }

        const std::size_t length() {
            return _size;
        }

        const bool empty() {
            return (_size == 0);
        }

        void clear() {
            if (_size != 0) {
                _size = 0;
                _capacity = 8;

                delete[] _data;
                _data = new char[_capacity]();
            }
        }

    private:
        char* _data;
        std::size_t _size;
        std::size_t _capacity;

        void resize(const size_t multiplier) {
            char* temp = new char[multiplier * _capacity]();

            memcpy(temp, _data, _capacity);

            delete[] _data;
            _data = temp;
            _capacity *= multiplier;
        }
    };
}


#endif //DZ5_STRING_H
